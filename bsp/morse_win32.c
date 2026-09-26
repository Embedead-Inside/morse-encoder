/**
 * @file morse_win32.c
 * @brief Windows (CMD / PowerShell / Visual Studio) 環境用 動作テスト用 BSP 実装
 * @details Win32 API の `timeGetTime()` または `GetTickCount()` とコンソール出力を用い、
 *          PC 上で動作確認を完結させます。
 *
 * @copyright Copyright (c) 2026 Embedead-Inside
 * @license SPDX-License-Identifier: MIT-0
 */

#include "morse-encoder.h"
#include <windows.h>
#include <stdio.h>

/**
 * @brief Win32 テスト用 信号状態表示関数
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
 * @brief Win32 テスト用 システム経過時間（ミリ秒）取得関数
 */
uint32_t morse_get_time_ms(void)
{
    return (uint32_t)GetTickCount();
}
