# 目的

オシロスコープっぽいもの

128x32 SSD1306 OLED 使用
AIN0 = PA0 の波形を見る

trigger: Rise or Falling
sampling rate 実験したら 320k samples / sec が限界だった。

# ボード配線メモ

```
                            PB8 D15 10 = SCL -->> to OLED 128x32
                            PB9 D14 9  = SDA -->> to OLED 128x32
                            AVD AVD 8
                            GND GND 7
          1 NC              PA5 D13 6
          2 IOREF           PA6 D12 5
          3 NRST            PA7 D11 4 -->> TIM17 test PWM
          4 3V3             PB0 D10 3
          5 5V               PC7 D9 2
          6 GND              PA9 D8 1
          7 GND
          8 VIN              PA8 D7 8
                            PB14 D6 7
read -->> 1 A0 PA0           PB4 D5 6
          2 A1 PA1           PB5 D4 5 -->> button
          3 A2 PA4           PB3 D3 4 -->> button
          4 A3 PB1          PA10 D2 3 -->> button
          5 A4 PB11          PC4 D1 2
          6 A5 PB12          PC5 D0 1
```

# SW操作

上から見て PA10 PB3 PB5 の順番 CPU内プルアップ必要

起動後サンプルPWMの状況表示 どれか押すと進む

RUNNINGのとき
PB3とPB5でサンプリング時間の切り替え
PA10 ... STOPする

STOPしているとき
PB3とPB5でトリガーモード切替
PA10 ... RUNに戻る

# メモ

- 6ビット限定 サンプリング時間も最小 1.5cycle
- Continuousモード
- DMAを使用する場合，ADが終わるのが速すぎてDMAが追いつかずフリーズしてしまう。どうしてもDMAを使う場合，サンプリング周期を大きく，ADCクロックプリスケーラーも大きくする。
- よって，普通に読む方が早いという結論。TIM16を100kで動かし，TIM16の割り込みハンドラの中でADCすることに成功している。
- サンプルとして TIM17 でPWMを作っている。PA7に出力されるので，PA0に接続して読む。

コネクター右側

```
     PC9 1  2
PB8 10 \
         3  4
PB9  9 \
         5  6
AVDD 8 \
         7  8
 GND 7 \
         9 10
 PA5 6 \
        11 12
 PA6 5 \
        13 14
 PA7 4 \
        15 16  ...

```


# 参考

http://dad8893.blogspot.com/2019/03/stm32-adcdmanucleo-f446re.html
http://matsubara-ui-design.net/2022/06/stm32_adc/

# メモ

サンプリングデータは 0 --- 0x111111 6ビット
ターゲットは 0 --- 15までの16個の値，4ビット まずは2ビット切り落とし。

0 ... 0x1111

