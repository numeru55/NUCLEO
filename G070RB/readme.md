2022/3の2.3.0からサポートされた。

# setup...

```bash
arduino-cli core install STMicroelectronics:stm32 --additional-urls https://github.com/stm32duino/BoardManagerFiles/raw/main/package_stmicroelectronics_index.json
```

# genetic G0 として書き込む

STM32CubeProg needed.
- https://www.stmcu.jp/design/sw_dev/pc_soft/58442/#58442_en

```bash
arduino-cli compile --fqbn STMicroelectronics:stm32:GenG0 hello
arduino-cli upload -p /dev/cu.usbmodem14103 --fqbn STMicroelectronics:stm32:GenG0 hello
arduino-cli monitor -p /dev/cu.usbmodem14103
```

# Nucleoとして書き込む

Mass Storageにコピーされる。

```Makefile
TARGET = blink_PA5
CORE = STMicroelectronics:stm32:Nucleo_64:pnum=NUCLEO_G070RB

compile:
        arduino-cli compile --fqbn ${CORE} ${TARGET}

upload: compile
        arduino-cli upload --fqbn ${CORE} ${TARGET}
```

# arduino pinout

```
                  PB8 D15 10 = SCL SPI2_SCK
                  PB9 D14 9  = SDA SPI2_NSS
                  AVD AVD 8
                  GND GND 7
1 NC              PA5 D13 6 SPI1_SCK I2S1_CK
2 IOREF           PA6 D12 5 SPI1_MISO I2S1_MCK
3 NRST            PA7 D11 4 SPI1_MOSI I2S1_SD
4 3V3             PB0 D10 3 SPI1_NSS I2S1_WS
5 5V               PC7 D9 2
6 GND              PA9 D8 1
7 GND
8 VIN              PA8 D7 8 SPI2_NSS
                  PB14 D6 7 SPI2_MISO
1 A0 PA0           PB4 D5 6 SPI1_MISO I2S1_MCK
2 A1 PA1           PB5 D4 5 SPI1_MOSI I2S1_SD
3 A2 PA4           PB3 D3 4 SPI1_SCK I2S1_CK
4 A3 PB1          PA10 D2 3 SPI2_MOSI
5 A4 PB11          PC4 D1 2 
6 A5 PB12          PC5 D0 1

PA5 - LED - GND  H:on L:off
PC13 - SW with on board pullup   H:open L:close
```

# Serialを使う

ボードの右端
```
PC4 D1 TX
PC5 D0 RX
```

# PIOでつかう

- Arduino コア 特に問題なさそう。[Upload] コマンドでアップロード。モニターも普通にできる。デバッグは不可
- STM32コアならさらにデバッグも可能。ただし，なぜか `main.cpp` ではだめで `main.c` で動かす必要がある。

# STM32 hal manual

https://www.st.com/resource/en/user_manual/um2319-description-of-stm32g0-hal-and-lowlayer-drivers-stmicroelectronics.pdf

# Thanks to:

STM32duino FreeRTOS
https://github.com/stm32duino/STM32FreeRTOS
