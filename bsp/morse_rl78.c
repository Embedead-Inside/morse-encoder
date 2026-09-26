/**
 * @file morse_rl78.c
 * @brief Renesas RL78 (RL78/G13, G23等) CC-RL / LLVM 用 BSP 実装
 * @details PORT レジスタ (P4.1等) の直接アクセスおよび TAU (タイマ・アレイ・ユニット) ミリ秒間隔制御を行います。
 *
 * @copyright Copyright (c) 2026 Embedead-Inside
 * @license SPDX-License-Identifier: MIT-0
 */

#include "morse-encoder.h"
#include "iodefine.h"

extern volatile uint32_t g_rl78_ms_counter;

/**
 * @brief Renesas RL78 用 GPIO 出力制御関数
 */
void morse_set_signal(uint8_t active)
{
    if (active != 0U) {
        P4_bit.no1 = 1U;
    } else {
        P4_bit.no1 = 0U;
    }
}

/**
 * @brief Renesas RL78 用 システム経過時間（ミリ秒）取得関数
 */
uint32_t morse_get_time_ms(void)
{
    return g_rl78_ms_counter;
}
