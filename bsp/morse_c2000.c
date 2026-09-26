/**
 * @file morse_c2000.c
 * @brief TI C2000 (C28x コア) リアルタイム制御マイコン用 BSP 実装
 * @details DriverLib の `GPIO_writePin` および CpuTimer0 経過時間を使用します。
 *
 * @copyright Copyright (c) 2026 Embedead-Inside
 * @license SPDX-License-Identifier: MIT-0
 */

#include "morse-encoder.h"
#include "driverlib.h"

#define MORSE_C2000_GPIO 31U

extern volatile uint32_t g_c2000_ms_counter;

/**
 * @brief C2000 用 GPIO 出力制御関数
 */
void morse_set_signal(uint8_t active)
{
    GPIO_writePin(MORSE_C2000_GPIO, (uint32_t)active);
}

/**
 * @brief C2000 用 システム経過時間（ミリ秒）取得関数
 */
uint32_t morse_get_time_ms(void)
{
    return g_c2000_ms_counter;
}
