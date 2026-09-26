/**
 * @file morse_rx.c
 * @brief Renesas RX シリーズ (RX651 / RX600等) CC-RX / GCC 用 BSP 実装
 * @details PORT (PODR) レジスタアクセスおよび CMT (コンペアマッチタイマ) 経過時間を使用します。
 *
 * @copyright Copyright (c) 2026 Embedead-Inside
 * @license SPDX-License-Identifier: MIT-0
 */

#include "morse-encoder.h"
#include "iodefine.h"

extern volatile uint32_t g_rx_cmt_ms_count;

/**
 * @brief Renesas RX 用 GPIO 出力制御関数
 */
void morse_set_signal(uint8_t active)
{
    PORT1.PODR.BIT.B0 = (active != 0U) ? 1U : 0U;
}

/**
 * @brief Renesas RX 用 システム経過時間（ミリ秒）取得関数
 */
uint32_t morse_get_time_ms(void)
{
    return g_rx_cmt_ms_count;
}
