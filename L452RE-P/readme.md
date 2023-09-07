UM2206

https://okutsu-my.sharepoint.com/:b:/g/personal/yasunori_okutsu_onmicrosoft_com/ERyetlBnn2xCi3MfIlmr8PIBL1jTUXg9z4fFG63RqATD-Q?e=tLFkNi

onboard osc: no
PA1 MCO from STLINK
User button PC13 close:H open:L onboard pull-down

User LED PB13 on:H off:L

- VCP RX - PA3, TX - PA2 as UART1


```LEFT
1 NC
2 IOREF
3 NRST
4 3V3
5 5V
6 GND
7 GND
8 VIN

1 PA0 A0
2 PA1 A1
3 PC3 A2
4 PC2 A3
5 PC1 A4 I2C3_SDA
6 PC0 A5 I2C3_SCL
```

```RIGHT
10 PB8(D15) I2C1_SCL
 9 PB7(D14) I2C1_SDA
 8 VREF
 7 GND
 6 PB13(D13) SPI2_SCK  -->> LED
 5 PB14(D12) SPI2_MISO
 4 PB15(D11) SPI2_MOSI
 3 PA11(D10) SPI2_NSS
 2 PA8(D9)  TIM1_CH1
 1 PB6(D8)  

 8 PC7(D7)  
 7 PB10(D6)  TIM2_CH3
 6 PA15(D5)  TIM2_CH1
 5 PB5(D4)  
 4 PB3(D3)  TIM2_CH2
 3 PA12(D2)  
 2 PA9(D1)  UART1_TX
 1 PA10(D0)  UART1_RX
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
