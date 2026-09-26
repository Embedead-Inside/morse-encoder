/**
 * @file morse_ch32v.c
 * @brief WCH CH32V シリーズ (QingKe RISC-V) MounRiver Studio / EVT 用 BSP 実装
 * @details CH32V 周辺ライブラリの GPIO_WriteBit および SysTick (Systick_Handler) を使用します。
 *
 * @copyright Copyright (c) 2026 Embedead-Inside
 * @license SPDX-License-Identifier: MIT-0
 */

#include "morse-encoder.h"
#include "ch32v00x.h"

extern volatile uint32_t g_ch32v_ticks_ms;

/**
 * @brief CH32V 用 GPIO 出力制御関数
 */
void morse_set_signal(uint8_t active)
{
    GPIO_WriteBit(GPIOD, GPIO_Pin_4, (active != 0U) ? Bit_SET : Bit_RESET);
}

/**
 * @brief CH32V 用 システム経過時間（ミリ秒）取得関数
 */
uint32_t morse_get_time_ms(void)
{
    return g_ch32v_ticks_ms;
}
