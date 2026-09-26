/**
 * @file morse_alt.c
 * @brief Intel / Altera Nios II / Nios V HAL 用 BSP 実装
 * @details Nios HAL の `IOWR_ALTERA_AVALON_PIO_DATA` および `alt_nticks()` を使用します。
 *
 * @copyright Copyright (c) 2026 Embedead-Inside
 * @license SPDX-License-Identifier: MIT-0
 */

#include "morse-encoder.h"
#include "altera_avalon_pio_regs.h"
#include "sys/alt_alarm.h"

#define MORSE_PIO_BASE 0x10000000U

/**
 * @brief Altera Nios 用 GPIO 出力制御関数
 */
void morse_set_signal(uint8_t active)
{
    IOWR_ALTERA_AVALON_PIO_DATA(MORSE_PIO_BASE, (active != 0U) ? 1U : 0U);
}

/**
 * @brief Altera Nios 用 システム経過時間（ミリ秒）取得関数
 */
uint32_t morse_get_time_ms(void)
{
    return (uint32_t)((alt_nticks() * 1000U) / alt_ticks_per_second());
}
