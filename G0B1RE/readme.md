UM2324

https://www.st.com/resource/en/user_manual/um2324-stm32-nucleo64-boards-mb1360-stmicroelectronics.pdf

```                  
                            PB8 D15 10 = SCL SPI2_SCK I2S2_CK
                            PB9 D14 9  = SDA SPI2_NSS I2S2_WS
                            AVD AVD 8
                            GND GND 7
          1 NC              PA5 D13 6 SPI1_SCK I2S1_CK  DAC1_OUT2
          2 IOREF           PA6 D12 5 SPI1_MISO I2S1_MCK
          3 NRST            PA7 D11 4 SPI1_MOSI I2S1_SD
          4 3V3             PB0 D10 3 SPI1_NSS I2S1_WS
          5 5V               PC7 D9 2
          6 GND              PA9 D8 1
          7 GND
          8 VIN              PA8 D7 8 SPI2_NSS I2S2_WS
                            PB14 D6 7 SPI2_MISO I2S2_MCK
          1 A0 PA0           PB4 D5 6 SPI1_MISO I2S1_MCK
          2 A1 PA1           PB5 D4 5 SPI1_MOSI I2S1_SD
DAC1_OUT1 3 A2 PA4           PB3 D3 4 SPI1_SCK I2S1_CK
          4 A3 PB1          PA10 D2 3 SPI2_MOSI I2S2_SD
          5 A4 PB11          PC4 D1 2 
          6 A5 PB12          PC5 D0 1

PA5 - LED - GND  H:on L:off
PC13 - SW with on board pullup   H:open L:close
```
