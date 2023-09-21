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

1 PA0 A0 COMP1_PUT SAI1_EXTCLK
2 PA1 A1
3 PC3 A2 SAI_SD_A
4 PC2 A3
5 PC1 A4 I2C3_SDA
6 PC0 A5 I2C3_SCL
```

```RIGHT
10 PB8(D15) I2C1_SCL   SAI1_MCLK_A
 9 PB7(D14) I2C1_SDA   SAI1_FS_A
 8 VREF
 7 GND
 6 PB13(D13) SPI2_SCK  -->> LED  SAI1_SCK_A
 5 PB14(D12) SPI2_MISO           SAI1_MCLK_A
 4 PB15(D11) SPI2_MOSI           SAI1_SD_A
 3 PA11(D10) SPI2_NSS COMP1_OUT
 2 PA8(D9)  TIM1_CH1             SAI1_SCK_A
 1 PB6(D8)                       SAI1_FS_B

 8 PC7(D7)  
 7 PB10(D6)  TIM2_CH3 I2C2_SCL SAI1_SCK_A
 6 PA15(D5)  TIM2_CH1
 5 PB5(D4)                     SAI1_SD_B
 4 PB3(D3)  TIM2_CH2           SAI1_SCK_B
 3 PA12(D2)  
 2 PA9(D1)  UART1_TX           SAI1_FS_A
 1 PA10(D0) UART1_RX           SAI1_SD_A
```

```RIGHT MORPHO
          PC9    1  2 PC8
I2C1 SCL  PB8    3  4 PC6
I2C1 SDA  PB7    5  6 PC5
        VREF --- 7  8 --- 5V_STLINK
        GND  --- 9 10 PB0
    (LED) PB13  11 12 PA10
          PB14  13 14 PA9
          PB15  15 16 PB11
          PA11  17 18 PB2
          PA8   19 20 --- GND
          PB6   21 22 PB1
          PC7   23 24 PA7
          PB10  25 26 PA6
          PA15  27 28 PA5
          PB5   29 30 PA4
          PB3   31 32 --- AGND
          PA12  33 34 PC4
          PA9   35 36 PA3
          PA10  37 38 PA2
```

# STmicro online training

https://www.st.com/content/st_com/ja/support/learning/stm32-education/stm32-online-training/stm32l4-online-training.html

