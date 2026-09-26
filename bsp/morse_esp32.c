/**
 * @file morse_esp32.c
 * @brief Espressif ESP32 / ESP32-S (Xtensa デュアル/シングルコア) ESP-IDF 用 BSP 実装
 * @details FreeRTOS タイマー tick または esp_timer を直接参照します。
 *
 * @copyright Copyright (c) 2026 Embedead-Inside
 * @license SPDX-License-Identifier: MIT-0
 */

#include "morse-encoder.h"
#include "driver/gpio.h"
#include "esp_timer.h"

#define MORSE_ESP_XTENSA_GPIO GPIO_NUM_2

/**
 * @brief ESP32 Xtensa 用 GPIO 出力制御関数
 */
void morse_set_signal(uint8_t active)
{
    gpio_set_level(MORSE_ESP_XTENSA_GPIO, (uint32_t)active);
}

/**
 * @brief ESP32 Xtensa 用 システム経過時間（ミリ秒）取得関数
 */
uint32_t morse_get_time_ms(void)
{
    return (uint32_t)(esp_timer_get_time() / 1000ULL);
}
