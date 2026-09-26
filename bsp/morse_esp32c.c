/**
 * @file morse_esp32c.c
 * @brief Espressif ESP32-C シリーズ (RISC-V コア) ESP-IDF 用 BSP 実装
 * @details ESP-IDF の gpio_set_level および esp_timer_get_time を使用します。
 *
 * @copyright Copyright (c) 2026 Embedead-Inside
 * @license SPDX-License-Identifier: MIT-0
 */

#include "morse-encoder.h"
#include "driver/gpio.h"
#include "esp_timer.h"

#define MORSE_ESP_GPIO_NUM  GPIO_NUM_8

/**
 * @brief ESP32-C シリーズ用 GPIO 出力制御関数
 */
void morse_set_signal(uint8_t active)
{
    gpio_set_level(MORSE_ESP_GPIO_NUM, (uint32_t)active);
}

/**
 * @brief ESP32-C シリーズ用 システム経過時間（ミリ秒）取得関数
 */
uint32_t morse_get_time_ms(void)
{
    return (uint32_t)(esp_timer_get_time() / 1000ULL);
}
