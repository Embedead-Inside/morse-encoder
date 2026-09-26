/**
 * @file morse_linux.c
 * @brief Linux / macOS / POSIX 環境用 動作テスト用 BSP 実装
 * @details コンソールターミナル上に視覚的なシグナル表示（`[*]` / `[ ]`）を行い、
 *          `clock_gettime` にて高精度なミリ秒を取得します。
 *
 * @copyright Copyright (c) 2026 Embedead-Inside
 * @license SPDX-License-Identifier: MIT-0
 */

#include "morse-encoder.h"
#include <stdio.h>
#include <time.h>

/**
 * @brief POSIX テスト用 信号状態表示関数
 */
void morse_set_signal(uint8_t active)
{
    if (active != 0U) {
        printf("[*] ");
    } else {
        printf("[ ] ");
    }
    fflush(stdout);
}

/**
 * @brief POSIX テスト用 システム経過時間（ミリ秒）取得関数
 */
uint32_t morse_get_time_ms(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint32_t)((ts.tv_sec * 1000ULL) + (ts.tv_nsec / 1000000ULL));
}
