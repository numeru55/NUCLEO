UM2364

https://okutsu-my.sharepoint.com/:b:/g/personal/yasunori_okutsu_onmicrosoft_com/ERyetlBnn2xCi3MfIlmr8PIBL1jTUXg9z4fFG63RqATD-Q?e=tLFkNi

onboard osc: no
PA1 MCO from STLINK
User button PE4 close:L open:H onboard pull-up

User LED PC5 on:H off:L

VCP RX - PA4
VCP TX - PA5

PD1 - SWIM

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

コマンドパレット - build は問題なく終了

Mac アップロードもOK -v で確認した結果

```bash
"stm8flash" -c stlinkv21 -p stm8s208?b -s flash -w .pio/build/nucleo_8s208rb/firmware.hex
```

デバッグはいまだできない

https://community.platformio.org/t/debug-support-with-stm8-s103f3p6-having-external-st-link-debugger/18563/3

# STM8CubeMX

- JREをインストール
- アプリをダウンロードして，terminal上で展開し，`sudo ./SetupSTM8CubeMX-1_5_0_macos` でセットアップする。
