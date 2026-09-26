/**
 * @file morse_msp430.c
 * @brief Texas Instruments MSP430 超低消費電力マイコン用 BSP 実装
 * @details P1OUT レジスタ直接制御と Timer_A 割り込みベースのミリ秒時間制御を行います。
 *
 * @copyright Copyright (c) 2026 Embedead-Inside
 * @license SPDX-License-Identifier: MIT-0
 */

#include "morse-encoder.h"
#include <msp430.h>

extern volatile uint32_t g_msp430_ms;

/**
 * @brief MSP430 用 GPIO 出力制御関数
 */
void morse_set_signal(uint8_t active)
{
    if (active != 0U) {
        P1OUT |= BIT0;
    } else {
        P1OUT &= ~BIT0;
    }
}

/**
 * @brief MSP430 用 システム経過時間（ミリ秒）取得関数
 */
uint32_t morse_get_time_ms(void)
{
    return g_msp430_ms;
}
