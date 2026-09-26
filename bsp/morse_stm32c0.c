/**
 * @file morse_stm32c0.c
 * @brief ST STM32C0 シリーズ用 BSP 実装
 * @details STM32 HAL ライブラリの GPIO 操作および HAL_GetTick() を使用します。
 *
 * @copyright Copyright (c) 2026 Embedead-Inside
 * @license SPDX-License-Identifier: MIT-0
 */

#include "morse-encoder.h"
#include "stm32c0xx_hal.h"

/** @brief 出力 GPIO ポート */
#define MORSE_GPIO_PORT GPIOA
/** @brief 出力 GPIO ピン */
#define MORSE_GPIO_PIN  GPIO_PIN_5

/**
 * @brief STM32C0 用 GPIO 出力制御関数
 */
void morse_set_signal(uint8_t active)
{
    HAL_GPIO_WritePin(MORSE_GPIO_PORT, MORSE_GPIO_PIN, (active != 0U) ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

/**
 * @brief STM32C0 用 システム経過時間（ミリ秒）取得関数
 */
uint32_t morse_get_time_ms(void)
{
    return HAL_GetTick();
}
