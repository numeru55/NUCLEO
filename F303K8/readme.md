# User Manual

https://www.st.com/resource/en/user_manual/um1956-stm32-nucleo32-boards-mb1180-stmicroelectronics.pdf

# Pin Out

VCP TX: PA2
VCP RX PA15

```
CN3 (Left Side)

Adruino STM32  Function
  D1     PA9   USART1 TX
  D0     PA10  USART1 RX
  RST    NRST
  GND    GND
  D2     PA12
  D3     PB0   TIM3_CH3
  D4     PB7
  D5     PB6   TIM16_CH1N
  D6     PB1   TIM3_CH4
  D7     PF0
  D8     PF1
  D9     PA8   TIM1_CH1
  D10    PA11  SPI_CS || TIM1_CH4
  D11    PB5   SPI1_MOSI || TIM17_CH1
  D12    PB4   SPI1_MISO

CN4 (Right Side)

Adruino STM32  Function
  VIN    VIN   Power Input
  GND    GND
  RST    NRST
  +5V    +5V
  A7     PA2   ADC1_IN3 connected to VCP_TX
  A6     PA7   ADC2_IN4
  A5     PA6   ADC2_IN3 || I2C1_SCL -SB16- PB6
  A4     PA5   ADC2_IN2 || I2C1_SDA -SB18- PB7
  A3     PA4   ADC2_IN1
  A2     PA3   ADC1_IN4
  A1     PA1   ADC1_IN2
  A0     PA0   ADC1_IN1
  AREF   AVDD
  +3V3   +3V3
  D13    PB3   SPI1_SCK connected to LD3(LED), H=ON
```


# Aruduino setup

```bash
arduino-cli core install STMicroelectronics:stm32 --additional-urls https://github.com/stm32duino/BoardManagerFiles/raw/main/package_stmicroelectronics_index.json
```


# STM32Cube IDE

- Win [Ctrl] + Space で候補を呼び出すことができる
- ブレークポイントで止まるとき，止まった行の実行前になっている。たとえば以下の行で止まっていたら，PB3を1にする前で停止している。

```main.c
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, 1); // ON
```

- 変数にメッセージ等を書いてブレークポイントで止めて値を見ることで，UARTデバッグのかわりが十分できそう。以下で `HAL_Delay` のところで止めて変数 s の値を見ればOK

```main.c
  char *s;

  while (1)
  {
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, 1); // ON
	  s="ON!";
	  HAL_Delay(100);
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, 0); // OFF
	  s="OFF!";
	  HAL_Delay(1000);
  }
```
