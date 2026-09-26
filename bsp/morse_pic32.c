/**
 * @file morse_pic32.c
 * @brief Microchip PIC32MX / PIC32MZ 用 BSP 実装
 * @details PLIB / Harmony の GPIO API または LAT レジスタ直接制御と Core Timer による時間計測を提供します。
 *
 * @copyright Copyright (c) 2026 Embedead-Inside
 * @license SPDX-License-Identifier: MIT-0
 */

#include "morse-encoder.h"
#include <xc.h>

extern volatile uint32_t g_pic32_ms_ticks;

/**
 * @brief PIC32 用 GPIO 出力制御関数
 */
void morse_set_signal(uint8_t active)
{
    LATBbits.LATB0 = (active != 0U) ? 1U : 0U;
}

/**
 * @brief PIC32 用 システム経過時間（ミリ秒）取得関数
 */
uint32_t morse_get_time_ms(void)
{
    return g_pic32_ms_ticks;
}
