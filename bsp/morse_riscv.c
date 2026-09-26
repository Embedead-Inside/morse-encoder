/**
 * @file morse_riscv.c
 * @brief 汎用 RISC-V アーキテクチャ用 BSP 実装
 * @details RISC-V 標準 CSR (`mtime` / `rdtime`) による時間管理およびレジスタ直列 GPIO 制御を提供します。
 *
 * @copyright Copyright (c) 2026 Embedead-Inside
 * @license SPDX-License-Identifier: MIT-0
 */

#include "morse-encoder.h"

#define RISCV_TIMER_FREQ_HZ (10000000ULL) /* 10 MHz */

/**
 * @brief RISC-V 64bit mtime レジスタ直接読み出し
 */
static inline uint64_t riscv_get_mtime(void)
{
    uint64_t mtime;
    __asm__ __volatile__ ("rdtime %0" : "=r"(mtime));
    return mtime;
}

/**
 * @brief 汎用 RISC-V 用 GPIO 出力制御関数
 */
void morse_set_signal(uint8_t active)
{
    (void)active;
}

/**
 * @brief 汎用 RISC-V 用 システム経過時間（ミリ秒）取得関数
 */
uint32_t morse_get_time_ms(void)
{
    return (uint32_t)((riscv_get_mtime() * 1000ULL) / RISCV_TIMER_FREQ_HZ);
}
