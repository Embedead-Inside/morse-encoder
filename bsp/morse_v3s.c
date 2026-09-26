/**
 * @file morse_v3s.c
 * @brief Allwinner V3/V3s (ARM Cortex-A7) Linux ドライバ / Sysfs 抽象化 BSP 実装
 * @details Linux ユーザー空間からの sysfs (gpiod) または clock_gettime による高精度時間取得を提供します。
 *
 * @copyright Copyright (c) 2026 Embedead-Inside
 * @license SPDX-License-Identifier: MIT-0
 */

#include "morse-encoder.h"
#include <time.h>
#include <stdio.h>

/**
 * @brief Allwinner V3s / Linux 用 信号制御関数
 */
void morse_set_signal(uint8_t active)
{
    /* ドライバ / GPIO モジュール経由での書き込みロジック */
    (void)active;
}

/**
 * @brief Allwinner V3s / Linux 用 システム経過時間（ミリ秒）取得関数
 */
uint32_t morse_get_time_ms(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint32_t)((ts.tv_sec * 1000ULL) + (ts.tv_nsec / 1000000ULL));
}
