/**
 * @file morse_avr.c
 * @brief Microchip/Atmel 8bit AVR (ATmega328P等) 用 BSP 実装
 * @details avr-libc の GPIO 直列操作および Timer0 割り込みを用いたミリ秒計測です。
 *
 * @copyright Copyright (c) 2026 Embedead-Inside
 * @license SPDX-License-Identifier: MIT-0
 */

#include "morse-encoder.h"
#include <avr/io.h>
#include <avr/interrupt.h>

static volatile uint32_t s_avr_millis = 0U;

ISR(TIMER0_COMPA_vect)
{
    s_avr_millis++;
}

/**
 * @brief AVR 用 GPIO 出力制御関数 (PB5 / Arduino D13 例)
 */
void morse_set_signal(uint8_t active)
{
    if (active != 0U) {
        PORTB |= (1 << PB5);
    } else {
        PORTB &= ~(1 << PB5);
    }
}

/**
 * @brief AVR 用 システム経過時間（ミリ秒）取得関数
 */
uint32_t morse_get_time_ms(void)
{
    uint32_t ms;
    uint8_t sreg = SREG;
    cli();
    ms = s_avr_millis;
    SREG = sreg;
    return ms;
}
