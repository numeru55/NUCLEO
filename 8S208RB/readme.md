UM2364

https://okutsu-my.sharepoint.com/:b:/g/personal/yasunori_okutsu_onmicrosoft_com/ERyetlBnn2xCi3MfIlmr8PIBL1jTUXg9z4fFG63RqATD-Q?e=tLFkNi

onboard osc: no
PA1 MCO from STLINK
User button PE4 close:L open:H onboard pull-up

User LED PC5 on:H off:L

- VCP RX - PA4, TX - PA5 as UART1

PD1 - SWIM

```LEFT
1 NC
2 IOREF
3 NRST
4 3V3
5 5V
6 GND
7 GND
8 VIN

1 PB5(A0) AIN5 (alt)I2C_SDA
2 PB4(A1) AIN4 (alt)I2C_SCL
3 PB3(A2) AIN3 (alt)TIM1_ETR
4 PB2(A3) AIN2 (alt)TIM1_CH3N
5 PB1(A4) AIN1 (alt)TIM1_CH2N / (SB)PE2 I2C_SDA
6 PB0(A5) AIN0 (alt)TIM1_CH1N / (SB)PE1 I2C_SCL

(alt) needs to change option byte
(SB) needs to change SB setting
```

```RIGHT
10 PE1(D15) I2C_SCL
 9 PE2(D14) I2C_SDA
 8 VREF
 7 GND
 6 PC5(D13) SPI1_SCK
 5 PC7(D12) SPI1_MISO
 4 PC6(D11) SPI1_MOSI
 3 PE5(D10) SPI1_NSS
 2 PC4(D9)  TIM1_CH4
 1 PD3(D8)  TIM2_CH2

 8 PD1(D7)  SWIM
 7 PC3(D6)  TIM1_CH3
 6 PC2(D5)  TIM1_CH2
 5 PG0(D4)  CAN_TX
 4 PC1(D3)  TIM1_CH1
 3 PE0(D2)  CLK_CCO
 2 PD5(D1)  UART3_TX
 1 PD6(D0)  UART3_RX
```

# platformio

https://docs.platformio.org/en/latest/boards/ststm8/nucleo_8s208rb.html

STM8ボードとSPLをインストールする

```platformio.ini
[env:nucleo_8s208rb]
platform = ststm8
board = nucleo_8s208rb
framework = spl
```

`~/.platformio/packages/framework-ststm8spl/Project/STM8S_StdPeriph_Examples/GPIO/GPIO_Toggle`にサンプルがある。ソースファイルをPIOのsrcフォルダーにすべてコピー。

ピン定義を変更

```main.c
//#define LED_GPIO_PORT  (GPIOH)
//#define LED_GPIO_PINS  (GPIO_PIN_3 | GPIO_PIN_2 | GPIO_PIN_1 | GPIO_PIN_0)

#define LED_GPIO_PORT  (GPIOC)
#define LED_GPIO_PINS  (GPIO_PIN_5)
```

コマンドパレット - run でおうちの mac と会社の Win で実行できた。


Mac アップロードもOK -v で確認した結果

```bash
"stm8flash" -c stlinkv21 -p stm8s208?b -s flash -w .pio/build/nucleo_8s208rb/firmware.hex
```

Win 

```ps1
"stm8flash" -c stlinkv21 -p stm8s208?b -s flash -w .pio\build\nucleo_8s208rb\firmware.hex
D
```

デバッグはいまだできない

https://community.platformio.org/t/debug-support-with-stm8-s103f3p6-having-external-st-link-debugger/18563/3


# sdccをVSCODEでコンパイルする

参考にならないか

http://kyoro205.blog.fc2.com/blog-entry-663.html

# STM8CubeMX

- JREをインストール
- アプリをダウンロードして，terminal上で展開し，`sudo ./SetupSTM8CubeMX-1_5_0_macos` でセットアップする。


# TIM1 One Shot reference

http://www.emcu.it/STM8/STM8-Discovery/Tim1eTim4/TIM1eTIM4.html

https://embedded-lab.com/blog/continuing-stm8-microcontroller-expedition/5/

# PWM

CH1Nに出すためにはオプションバイトの設定が必要だと

http://stm8sdatasheet.web.fc2.com/STVD-project06-TIMER-PWM/STM8S-TIMER-PWM.html

# ペリフェラルのレジスターのアドレス

`uint32_t odr_address=(uint32_t)&GPIOC->ODR;` のような書き方が許されない。sdccの制約のようだ。

```c:main.c（抜粋）
    volatile unsigned char *my_odr;
    my_odr=&GPIOC->ODR;
    uint16_t d=(uint16_t)my_odr;
    printf("d %x\n", d);
```
これで変数 d に `GPIOC->ODR` のアドレス 0x500a が入る。
