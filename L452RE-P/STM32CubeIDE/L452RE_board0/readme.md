# nucleo L452RE

- 32.768k to PC14/PC15 OSC32

- no ext clock, so PH0 and PH1 can be used for GPIO.

- PA13/PA14 - SWDIO/SWCLK

- USER button PC13 open:L, close:H
- LED PB13 H:ON, L:close
- PB3 to SWO

# Left connector

```
1 A0 PA0 ADC1_IN5
2 A1 PA1 ADC1_IN6
3 A2 PC3 ADC1_IN4
4 A3 PC2 ADC1_IN3
5 A4 PC1 ADC1_IN2
6 A5 PC0 ADC1_IN1
```

# Right Connector

```
10 D15  PB8 I2C1_SCL
 9 D14  PB7 I2C1_SDA
 8 AVDD 
 7 GND
 6 D13  PB13
 5 D12  PB14
 4 D11  PB15 TIM15_CH2
 3 D10  PA11 TIM1_CH4
 2  D9   PA8 TIM1_CH1
 1  D8   PB6

 8  D7   PC7
 7  D6  PB10
 6  D5  PA15
 5  D4   PB5
 4  D3   PB3
 3  D2  PA12
 2  D1   PA9 UART1 TX
 1  D1  PA10 UART2 RX
```