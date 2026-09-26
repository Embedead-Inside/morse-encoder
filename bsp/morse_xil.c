/**
 * @file morse_xil.c
 * @brief AMD / Xilinx (MicroBlaze, Zynq, Versal) Standalone OS 用 BSP 実装
 * @details Xilinx GPIO (XGpio) および XTmrCtr / Sleep ドライバとの連携です。
 *
 * @copyright Copyright (c) 2026 Embedead-Inside
 * @license SPDX-License-Identifier: MIT-0
 */

#include "morse-encoder.h"
#include "xgpio.h"
#include "xtime_l.h"

extern XGpio g_xil_morse_gpio;
#define MORSE_XIL_CHANNEL 1

/**
 * @brief Xilinx プラットフォーム用 GPIO 出力制御関数
 */
void morse_set_signal(uint8_t active)
{
    XGpio_DiscreteWrite(&g_xil_morse_gpio, MORSE_XIL_CHANNEL, (active != 0U) ? 1U : 0U);
}

/**
 * @brief Xilinx プラットフォーム用 システム経過時間（ミリ秒）取得関数
 */
uint32_t morse_get_time_ms(void)
{
    XTime t;
    XTime_GetTime(&t);
    return (uint32_t)(t / (COUNTS_PER_SECOND / 1000));
}
