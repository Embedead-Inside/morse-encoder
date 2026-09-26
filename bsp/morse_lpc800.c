/**
 * @file morse_lpc800.c
 * @brief NXP LPC800 シリーズ (Cortex-M0+) 用 BSP 実装
 * @details LPCOpen ソフトウェアドライバの GPIO モジュールおよび SysTick 経過時間を使用します。
 *
 * @copyright Copyright (c) 2026 Embedead-Inside
 * @license SPDX-License-Identifier: MIT-0
 */

#include "morse-encoder.h"
#include "chip.h"

#define MORSE_GPIO_PORT 0
#define MORSE_GPIO_PIN  12

extern volatile uint32_t g_systick_ms; /**< SysTick割り込み等で更新されるグローバルミリ秒カウンタ */

/**
 * @brief LPC800 用 GPIO 出力制御関数
 */
void morse_set_signal(uint8_t active)
{
    Chip_GPIO_SetPinState(LPC_GPIO_PORT, MORSE_GPIO_PORT, MORSE_GPIO_PIN, (active != 0U));
}

/**
 * @brief LPC800 用 システム経過時間（ミリ秒）取得関数
 */
uint32_t morse_get_time_ms(void)
{
    return g_systick_ms;
}
