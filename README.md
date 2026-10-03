# morse-encoder

[![License: MIT-0](https://img.shields.io/badge/License-MIT--0-blue.svg)](https://spdx.org/licenses/MIT-0.html)
[![Language: C99](https://img.shields.io/badge/Language-C99-green.svg)](#)

組み込みシステム向けにC言語で書かれた、超軽量・プラットフォーム非依存のノンブロッキング型モールス符号エンコーダーモジュールです。

## 特徴

- **決定論的な超省メモリ設計**：動的確保を排除し静的メモリのみで動作。1文字16ビット（上位8bit: パターン、下位8bit: 長さ）のルックアップテーブルを採用。
- **完全ノンブロッキング・FSM駆動**：`delay()` を使用しないためリアルタイムタスクを阻害しません。
- **プラットフォーム非依存**：ハードウェア制御を抽象化し、多様なマイコンに移植可能。
- **国際モールス規格（ITU）準拠**：正確なスペース生成と主要文字・記号に対応。

---

## データ構造の仕組み

独自の16ビットビットフィールド形式でエンコードされています。
- **高位 8bit**: ビットパターン（`0`: 短点、`1`: 長点）
- **低位 8bit**: 符号長

---

## 使い方（クイックスタート）

ハードウェアに合わせて2つの関数（BSP）を実装します。

### 1. 依存関数の実装（BSP）
```c
#include "morse-encoder.h"

uint32_t morse_get_time_ms(void) { return your_hardware_get_millis(); }
void morse_set_signal(uint8_t state) { state ? your_hardware_led_on() : your_hardware_led_off(); }
```

### 2. メインループでの実行
```c
#include "morse-encoder.h"

int main(void) {
    morse_init();
    morse_start("SOS");
    while (1) {
        morse_update();
        if (!morse_is_busy()) { /* 完了処理 */ }
    }
}
```

---

## API リファレンス

| 関数プロトタイプ | 説明 |
| :--- | :--- |
| `void morse_init(void)` | 初期化と出力OFF |
| `void morse_start(const char *ascii_str)` | 送信シーケンス開始 |
| `void morse_update(void)` | 状態更新（ループ内で呼び出し） |
| `uint8_t morse_is_busy(void)` | ビジー状態判定 (1: 実行中, 0: 待機中) |

---

## ライセンス
このプロジェクトはMIT-0ライセンスのもとで公開されています。詳細は[LICENSE](LICENSE)ファイルをご覧ください。
- 商用利用・個人利用を問わず、完全自由に使用できます。
- 著作権表示やライセンス文言の保持・記載義務すらありません。
- ソースコードの改変、流用、再配布、自社製品への組み込み等、制限なくご活用いただけます。

<p align="right"><small><a name="note" class="muted-link">※一部AIによる生成・調整コードが含まれることがあります。</a></small></p>
