/**
 * @file morse_ra.c
 * @brief Renesas RA シリーズ (RA4M1等) FSP 用 BSP 実装
 * @details Flexible Software Package (FSP) の IOPORT アピアランスおよび SysTick を介して制御します。
 *
 * @copyright Copyright (c) 2026 Embedead-Inside
 * @license SPDX-License-Identifier: MIT-0
 */

#include "morse-encoder.h"
#include "hal_data.h"

#define MORSE_IOPORT_PIN BSP_IO_PORT_01_PIN_00

extern volatile uint32_t g_fsp_systick_ms;

/**
 * @brief Renesas RA 用 GPIO 出力制御関数
 */
void morse_set_signal(uint8_t active)
{
    R_IOPORT_PinWrite(&g_ioport_ctrl, MORSE_IOPORT_PIN, (active != 0U) ? BSP_IO_LEVEL_HIGH : BSP_IO_LEVEL_LOW);
}

/**
 * @brief Renesas RA 用 システム経過時間（ミリ秒）取得関数
 */
uint32_t morse_get_time_ms(void)
{
    return g_fsp_systick_ms;
}
