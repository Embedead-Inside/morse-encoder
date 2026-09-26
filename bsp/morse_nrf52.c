/**
 * @file morse_nrf52.c
 * @brief Nordic nRF52 / nRF53 (nRF Connect SDK / Zephyr RTOS) 用 BSP 実装
 * @details Zephyr RTOS の `gpio_pin_set_dt` および `k_uptime_get_32` を使用します。
 *
 * @copyright Copyright (c) 2026 Embedead-Inside
 * @license SPDX-License-Identifier: MIT-0
 */

#include "morse-encoder.h"
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

static const struct gpio_dt_spec s_led = GPIO_DT_SPEC_GET(DT_ALIAS(led0), gpios);

/**
 * @brief Nordic / Zephyr 用 GPIO 出力制御関数
 */
void morse_set_signal(uint8_t active)
{
    (void)gpio_pin_set_dt(&s_led, (int)active);
}

/**
 * @brief Nordic / Zephyr 用 システム経過時間（ミリ秒）取得関数
 */
uint32_t morse_get_time_ms(void)
{
    return k_uptime_get_32();
}
