/*

from
http://stm8sdatasheet.web.fc2.com/STVD-project06-TIMER-PWM/STM8S-TIMER-PWM.html

http://stm8sdatasheet.web.fc2.com/STVD-project09-TIMER-ONESHOT/STM8S-TIMER-ONE-SHOT.html

10 PE1(D15) I2C_SCL
 9 PE2(D14) I2C_SDA
 8 VREF
 7 GND                 <<--
 6 PC5(D13) SPI1_SCK   <<-- LED
 5 PC7(D12) SPI1_MISO
 4 PC6(D11) SPI1_MOSI
 3 PE5(D10) SPI1_NSS
 2 PC4(D9)  TIM1_CH4
 1 PD3(D8)  TIM2_CH2

 8 PD1(D7)  SWIM
 7 PC3(D6)  TIM1_CH3
 6 PC2(D5)  TIM1_CH2
 5 PG0(D4)  CAN_TX
 4 PC1(D3)  TIM1_CH1   <<--
 3 PE0(D2)  CLK_CCO
 2 PD5(D1)  UART3_TX
 1 PD6(D0)  UART3_RX

*/

#include "stm8s_conf.h"
#include "stm8s_it.h" /* SDCC patch: required by SDCC for interrupts */
#include "stdio.h"

#define PUTCHAR_PROTOTYPE int putchar(int c)
#define GETCHAR_PROTOTYPE int getchar(void)

void main(void)
{

  CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1); // 16MHz / 1 = 16MHz

  UART1_DeInit();
  UART1_Init(
      (uint32_t)9600,
      UART1_WORDLENGTH_8D,
      UART1_STOPBITS_1,
      UART1_PARITY_NO,
      UART1_SYNCMODE_CLOCK_DISABLE,
      UART1_MODE_TXRX_ENABLE);

  GPIO_Init(GPIOC, GPIO_PIN_5, GPIO_MODE_OUT_PP_HIGH_FAST);

  GPIO_WriteLow(GPIOC, GPIO_PIN_5); // for debug

  TIM1_DeInit();

  TIM1_TimeBaseInit(
      //15999, // prescaler 0 ... 65535
      15999,
      TIM1_COUNTERMODE_UP,
      1, // period
      0);

  TIM1_OC1Init(
    TIM1_OCMODE_PWM1, // count up -> down
    TIM1_OUTPUTSTATE_ENABLE, // for CH1 PC1
    TIM1_OUTPUTNSTATE_DISABLE, // for CH1N need to change option byte
    1, // must be less than period
    TIM1_OCPOLARITY_HIGH,  // for CH1
    TIM1_OCNPOLARITY_HIGH, // for CH1N
    TIM1_OCIDLESTATE_SET,  // for CH1
    TIM1_OCNIDLESTATE_SET  // for CH1N
    );

  TIM1_CtrlPWMOutputs(ENABLE);

  // start TIM1

  TIM1_Cmd(ENABLE);
  //TIM1->CR1 |= TIM1_CR1_CEN;

  GPIO_WriteHigh(GPIOC, GPIO_PIN_5); // for debug

  while (1)
  {
  }
}


/**
 * @brief Retargets the C library printf function to the UART.
 * @param c Character to send
 * @retval char Character sent
 */
PUTCHAR_PROTOTYPE
{
  /* Write a character to the UART1 */
  UART1_SendData8(c);
  /* Loop until the end of transmission */
  while (UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET)
    ;

  return (c);
}

/**
 * @brief Retargets the C library scanf function to the USART.
 * @param None
 * @retval char Character to Read
 */
GETCHAR_PROTOTYPE
{
#ifdef _COSMIC_
  char c = 0;
#else
  int c = 0;
#endif
  /* Loop until the Read data register flag is SET */
  while (UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET)
    ;
  c = UART1_ReceiveData8();
  return (c);
}

#ifdef USE_FULL_ASSERT

/**
 * @brief  Reports the name of the source file and the source line number
 *   where the assert_param error has occurred.
 * @param file: pointer to the source file name
 * @param line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  (void)file;
  (void)line;
  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
 * @}
 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
