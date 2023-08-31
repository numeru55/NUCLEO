UM2364

https://okutsu-my.sharepoint.com/:b:/g/personal/yasunori_okutsu_onmicrosoft_com/ERyetlBnn2xCi3MfIlmr8PIBL1jTUXg9z4fFG63RqATD-Q?e=tLFkNi

onboard osc: no
PA1 MCO from STLINK
User button PE4 close:L open:H onboard pull-up

User LED PC5 on:H off:L

- VCP RX - PA4, TX - PA5 as UART1

PD1 - SWIM

```
1 NC
2 IOREF
3 NRST
4 3V3
5 5V
6 GND
7 GND
8 VIN

1 PB5(A0) AIN5 I2C_SDA
2 PB4(A1) AIN4 I2C_SCL
3 PB3(A2) AIN3 TIM1_ETR
4 PB2(A3) AIN2 TIM1_CH3N
5 PB1/PE2(A4) AIN1 TIM1_CH2N / I2C_SDA
6 PB0/PE1(A5) AIN0 TIM1_CH1N / I2C_SCL
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
