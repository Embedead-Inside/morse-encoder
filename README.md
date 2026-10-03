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

ご使用の環境（通常のC言語環境、またはArduino環境）に合わせて、依存関数（BSP）を実装して組み込みます。

### A. 通常のC言語環境（ベアメタル、各社MCU HAL、RTOS等）

純粋なC言語環境（`morse-encoder.c` と同一のリンケージ）で動作させる場合の最小構成です。

#### 1. 依存関数（BSP）の実装 (`bsp_generic.c`)
```c
#include "morse-encoder.h"
#include "your_mcu_hal.h" // ご使用のマイコンのヘッダー

/* 1. ハードウェアのシステムタイマー（ミリ秒）を返す関数 */
uint32_t morse_get_time_ms(void) {
    return HAL_GetTick(); // 例: STM32CubeHALの場合
}

/* 2. 指定された状態（1:ON, 0:OFF）に応じてGPIOを制御する関数 */
void morse_set_signal(uint8_t state) {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, state ? GPIO_PIN_SET : GPIO_PIN_RESET);
}
```

#### 2. メインループの実装 (`main.c`)
```c
#include "morse-encoder.h"

int main(void) {
    // ハードウェアの初期化をここで行う
    
    morse_init();
    morse_start("SOS");

    while (1) {
        morse_update(); // 状態遷移マシンをノンブロッキングで更新
        
        // 他のバックグラウンドタスクをここに記述可能
    }
}
```

---

### B. Arduino環境（C++ / クロスプラットフォーム）

Arduino環境の関数（`millis()` や `digitalWrite()`）はC++としてコンパイルされるため、BSP側の拡張子を **`.cpp`** にして連携させます。CPUの種類（AVR、ESP32、RP2040、ARM等）を問わず完全に共通のコードで動作します。

#### 1. 依存関数（BSP）の実装 (`bsp_arduino.cpp`)
```cpp
#include <Arduino.h>
#include "morse-encoder.h"

/* 1. Arduinoのタイマーから現在時刻（ms）を取得 */
uint32_t morse_get_time_ms(void) {
    return millis();
}

/* 2. 指定された状態に応じて内蔵LEDを制御 */
void morse_set_signal(uint8_t state) {
    digitalWrite(LED_BUILTIN, state ? HIGH : LOW);
}
```

#### 2. スケッチの実装 (`.ino`)
`delay()` を使用しないため、`loop()` 内で他の処理を同時に実行してもモールス信号の点滅が途切れることはありません。
```cpp
#include "morse-encoder.h"

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    morse_init();
    morse_start("SOS CQ CQ");
}

void loop() {
    morse_update(); // 毎ループ高速に呼び出します
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
