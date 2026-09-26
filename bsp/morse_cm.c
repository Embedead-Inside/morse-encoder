/**
 * @file morse_cm.c
 * @brief ARM Cortex-M 汎用 (Cortex-M0/M3/M4等) CMSIS 準拠 BSP 実装
 * @details CMSIS 標準の SysTick タイマーおよび汎用 GPIO レジスタアクセス構造を使用した汎用ドライバです。
 *
 * @copyright Copyright (c) 2026 Embedead-Inside
 * @license SPDX-License-Identifier: MIT-0
 */

#include "morse-encoder.h"
#include "RTE_Components.h"
#include CMSIS_device_header

static volatile uint32_t s_cm_systick_counter = 0U;

/**
 * @brief SysTick ハンドラ（1ms 周期割り込みで呼び出し）
 */
void SysTick_Handler(void)
{
    s_cm_systick_counter++;
}

/**
 * @brief ARM Cortex-M 汎用 GPIO 出力制御関数
 */
void morse_set_signal(uint8_t active)
{
    /* 環境に応じたレジスタ操作に置換可能 */
    (void)active;
}

/**
 * @brief ARM Cortex-M 汎用 システム経過時間（ミリ秒）取得関数
 */
uint32_t morse_get_time_ms(void)
{
    return s_cm_systick_counter;
}
