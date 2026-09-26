/**
 * @file morse_c51.c
 * @brief 8051 汎用アーキテクチャ (STC等) Keil C51 / SDCC 用 BSP 実装
 * @details P1_0 ビットポート制御および タイマー0 割り込みカウントを使用します。
 *
 * @copyright Copyright (c) 2026 Embedead-Inside
 * @license SPDX-License-Identifier: MIT-0
 */

#include "morse-encoder.h"

#if defined(__SDCC)
    #include <8051.h>
    #define PIN_LED P1_0
#else
    #include <reg51.h>
    sbit PIN_LED = P1^0;
#endif

extern volatile uint32_t g_c51_ms_ticks;

/**
 * @brief 8051 用 GPIO 出力制御関数
 */
void morse_set_signal(uint8_t active)
{
    PIN_LED = (active != 0U) ? 1 : 0;
}

/**
 * @brief 8051 用 システム経過時間（ミリ秒）取得関数
 */
uint32_t morse_get_time_ms(void)
{
    return g_c51_ms_ticks;
}
