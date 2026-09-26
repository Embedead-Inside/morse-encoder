/**
 * @file morse-encoder.c
 * @brief 超軽量・ポータブル モールス符号エンコーダーモジュールの内部実装
 * @details 国際モールス規格に基づいた英数字および記号の変換テーブルを保持し、
 *          入力されたテキストから符号ストリームへの展開処理を実装します。
 *          組み込み環境での使用を想定し、動的メモリ確保（malloc等）を排除した
 *          決定論的（省メモリ・高速）なエンコード処理を行います。
 *
 * @copyright Copyright (c) 2026 Embedead-Inside
 * @license SPDX-License-Identifier: MIT-0
 *
 * @note 本モジュールは純粋な符号変換（状態遷移）のみを担当し、
 *       GPIOやタイマー等のハードウェア制御、および時間待ち（Delay）処理は含みません。
 */

#include "morse-encoder.h"
#include <ctype.h>
#include <stddef.h>

/* ========================================================================
 * Flash/ROM 配置マクロ定義
 * ======================================================================== */
#if defined(__AVR__)
    #include <avr/pgmspace.h>
    #define RO_DATA PROGMEM
    #define READ_PTR(ptr) ((const char *)pgm_read_ptr(&(ptr)))
#else
    /** @brief 32bit系マイコン(RX/MicroBlaze/Nios II/ARM等)用のROM配置指示子 */
    #define RO_DATA
    /** @brief ポインタ読み出しマクロ */
    #define READ_PTR(ptr) (ptr)
#endif

/* ========================================================================
 * モールス変換マップ定義
 * ======================================================================== */

/**
 * @brief ASCIIコードをモールス符号文字列へ紐付ける検索テーブル (O(1)参照)
 */
static const char *const MORSE_MAP[128] RO_DATA = {
    ['!'] = "-.-.--", ['"'] = ".-..-.", ['$'] = "...-..-",
    ['&'] = ".-...",  ['\''] = ".----.",['('] = "-.--.",  [')'] = "-.--.-",
    ['+'] = ".-.-.",  [','] = "--..--", ['-'] = "-....-", ['.'] = ".-.-.-",
    ['/'] = "-..-.",  [':'] = "---...", [';'] = "-.-.-.", ['='] = "-...-",
    ['?'] = "..--..", ['@'] = ".--.-.", ['_'] = "..--.-",
    ['0'] = "-----",  ['1'] = ".----",  ['2'] = "..---",  ['3'] = "...--",
    ['4'] = "....-",  ['5'] = ".....",  ['6'] = "-....",  ['7'] = "--...",
    ['8'] = "---..",  ['9'] = "----.",
    ['A'] = ".-",     ['B'] = "-...",   ['C'] = "-.-.",   ['D'] = "-..",
    ['E'] = ".",      ['F'] = "..-.",   ['G'] = "--.",    ['H'] = "....",
    ['I'] = "..",     ['J'] = ".---",   ['K'] = "-.-",    ['L'] = ".-..",
    ['M'] = "--",     ['N'] = "-.",     ['O'] = "---",    ['P'] = ".--.",
    ['Q'] = "--.-",   ['R'] = ".-.",    ['S'] = "...",    ['T'] = "-",
    ['U'] = "..-",    ['V'] = "...-",   ['W'] = ".--",    ['X'] = "-..-",
    ['Y'] = "-.--",   ['Z'] = "--.."
};

/* ========================================================================
 * モジュール内静的（内部）変数
 * ======================================================================== */

/** @brief 送信対象の ASCII 文字列における現在参照位置ポインタ */
static const char *s_src = NULL;

/** @brief 現在出力中である文字のモールス符号（".-"等）内の現在参照位置ポインタ */
static const char *s_code = NULL;

/** @brief 次のアクション（ON/OFF切り替え）を起こすシステム目標時刻（ミリ秒） */
static uint32_t s_target = 0U;

/** @brief 現在の出力状態フラグ (1: マーク/信号ON中, 0: スペース/信号OFF・待機中) */
static uint8_t  s_state = 0U;

/** @brief 次の文字出力前に文字間スペース（全3ユニット）を挿入する必要があるかを示すフラグ (1: 必要, 0: 不要) */
static uint8_t  s_need_char_space = 0U;

/* ========================================================================
 * API 関数実装
 * ======================================================================== */

/**
 * @brief モールス送信モジュールの初期化関数
 * @details すべての内部状態変数およびフラグを完全にクリアし、ハードウェア出力を非アクティブ状態にします。
 * @return なし
 */
void morse_init(void)
{
    s_src = NULL;
    s_code = NULL;
    s_target = 0U;
    s_state = 0U;
    s_need_char_space = 0U;
    morse_set_signal(0U);
}

/**
 * @brief モールス信号送信開始関数
 * @details 指定された ASCII 文字列の送信シーケンスを開始します。開始時点では直前に文字が出力されていないため、
 *          文字間スペースフラグ (`s_need_char_space`) は 0 に初期化されます。
 * @param[in] ascii_str 送信対象の ASCII 文字列（ヌル終端）
 * @return なし
 */
void morse_start(const char *ascii_str)
{
    s_src = ascii_str;
    s_code = NULL;
    s_target = 0U;
    s_state = 0U;
    s_need_char_space = 0U;
    morse_set_signal(0U);
}

/**
 * @brief 送信状態（ビジー状態）確認関数
 * @details 送信バッファ、出力中の符号、または ON 出力状態のいずれかがアクティブであるか判定します。
 * @return uint8_t 送信状態 (1: 送信処理実行中, 0: 完全停止/待機中)
 */
uint8_t morse_is_busy(void)
{
    return (s_src != NULL || s_code != NULL || s_state != 0U) ? 1U : 0U;
}

/**
 * @brief モールス送信状態更新関数（ノンブロッキング処理）
 * @details システムタイマーと連携して時間到達を判定し、マーク（ON）制御、符号内要素間スペース（1ユニット）、
 *          文字間スペース（3ユニット）、単語間スペース（7ユニット）をシームレスに切り替えます。
 * @return なし
 */
void morse_update(void)
{
    if (morse_is_busy() == 0U) return;

    uint32_t now = morse_get_time_ms();

    /* ミリ秒タイマーのオーバーフロー（桁あふれ）安全比較 */
    if ((int32_t)(now - s_target) < 0) return;

    /* マーク(ON)出力終了後のスペース（OFF）処理 */
    if (s_state != 0U) {
        morse_set_signal(0U);
        s_state = 0U;
        s_target = now + MORSE_UNIT_TIME_MS; /* 符号内要素（短点・長点）間のギャップ: 1ユニット */
        if (s_code != NULL) {
            s_code++;
        }
        return;
    }

    /* 次の符号のロード / 文字・単語スペース切り替え処理 */
    while (s_code == NULL || *s_code == '\0') {
        if (s_src == NULL || *s_src == '\0') {
            s_src = NULL;
            s_code = NULL; /* 全送信完了 */
            return;
        }

        uint8_t c = (uint8_t)*s_src++;

        /* 単語間スペース（全7ユニット）の処理 */
        if (c == ' ') {
            s_target = now + (6U * MORSE_UNIT_TIME_MS); /* 直前の1 + 6 = 7ユニット */
            s_need_char_space = 0U; /* 単語スペースを消化したため、次の文字での文字間スペースは不要 */
            return; /* 待機時間をセットして次回周期へ */
        }

        /* 文字コードの変換（安全なキャスト） */
        uint8_t uc = (uint8_t)toupper((unsigned char)c);
        s_code = (uc < 128U) ? READ_PTR(MORSE_MAP[uc]) : NULL;

        /* 有効なモールス符号がロードできた場合の文字間スペース処理 */
        if (s_code != NULL) {
            if (s_need_char_space != 0U) {
                s_target = now + (2U * MORSE_UNIT_TIME_MS); /* 直前の1 + 2 = 3ユニット */
                s_need_char_space = 0U; /* スペースを消化したためフラグクリア */
                return; /* 待機時間をセットして次回周期へ */
            }
            break; /* スペース不要（初回や単語直後）なら即座にマーク出力へ */
        }
    }

    /* マーク(ON)の信号出力処理 */
    if (s_code != NULL) {
        char sign = *s_code;
        if (sign == '.' || sign == '-') {
            morse_set_signal(1U);
            s_state = 1U;
            s_need_char_space = 1U; /* 文字内の符号を出力したため、次の文字へ移る際は文字間スペースが必要 */
            
            /* 短点 '.' = 1ユニット, 長点 '-' = 3ユニット */
            s_target = now + ((sign == '.') ? 1U : 3U) * MORSE_UNIT_TIME_MS;
        } else {
            s_code++; /* 想定外文字（バグマップ対策等）のスキップ */
        }
    }
}
