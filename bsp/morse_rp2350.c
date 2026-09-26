/**
 * @file morse_rp2350.c
 * @brief Raspberry Pi Pico / Pico 2 (RP2040/RP2350) 用 BSP 実装
 * @details Pico SDK の GPIO 機能および SDK 組み込みのミリ秒タイマーを使用して
 *          モールス信号の物理出力と時間計測を行います。
 *
 * @copyright Copyright (c) 2026 Embedead-Inside
 * @license SPDX-License-Identifier: MIT-0
 */

#include "morse-encoder.h"
#include "pico/stdlib.h"

/** @brief モールス信号出力用の GPIO ピン番号 (オンボードLED等のデフォルトピン) */
#ifndef MORSE_GPIO_PIN
#define MORSE_GPIO_PIN PICO_DEFAULT_LED_PIN
#endif

/**
 * @brief RP2040/RP2350 用 GPIO 出力制御関数
 */
void morse_set_signal(uint8_t active)
{
    gpio_put(MORSE_GPIO_PIN, (active != 0U) ? true : false);
}

/**
 * @brief RP2040/RP2350 用 システム経過時間（ミリ秒）取得関数
 */
uint32_t morse_get_time_ms(void)
{
    return to_ms_since_boot(get_absolute_time());
}
