/*

from
http://stm8sdatasheet.web.fc2.com/STVD-project06-TIMER-PWM/STM8S-TIMER-PWM.html

http://stm8sdatasheet.web.fc2.com/STVD-project09-TIMER-ONESHOT/STM8S-TIMER-ONE-SHOT.html

*/

#include "stm8s_conf.h"
#include "stm8s_it.h" /* SDCC patch: required by SDCC for interrupts */
#include "stdio.h"

#define PUTCHAR_PROTOTYPE int putchar(int c)
#define GETCHAR_PROTOTYPE int getchar(void)

void delay_ms(uint16_t ms);

uint32_t ticks_ms = 0;

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

  //delay_ms(5000);

  //printf("Start 100\n");
  //delay_ms(100);

  printf("Start 1000\n");
  delay_ms(1000);

  //printf("Start 5000\n");
  //delay_ms(5000);

  //printf("Start 10000\n");
  //delay_ms(10000);

  printf("end\n");

  while (1)
  {
  }
}

void delay_ms(uint16_t ms)
{

  TIM1_DeInit();

  TIM1_TimeBaseInit(
      //15999, // prescaler 0 ... 65535
      1599,
      TIM1_COUNTERMODE_DOWN,
      ms, // period
      0);

  //TIM1_ITConfig(TIM1_IT_UPDATE, ENABLE);

  TIM1_SelectOnePulseMode(TIM1_OPMODE_SINGLE);
  TIM1_OC1Init(
    TIM1_OCMODE_PWM2, 
    TIM1_OUTPUTSTATE_ENABLE, // for CH1 PC1
    TIM1_OUTPUTNSTATE_ENABLE, // for CH1N?
    300, 
    TIM1_OCPOLARITY_HIGH, 
    TIM1_OCNPOLARITY_HIGH, 
    TIM1_OCIDLESTATE_RESET, 
    TIM1_OCNIDLESTATE_SET
    ); // TIM1_CH1 output port

  TIM1_CtrlPWMOutputs(ENABLE); // for debug

  // start TIM1

  TIM1_Cmd(ENABLE);
  TIM1->CR1 |= TIM1_CR1_CEN;

  GPIO_WriteHigh(GPIOC, GPIO_PIN_5); // for debug

  while (TIM1->CR1 & TIM1_CR1_CEN)
  {
#if 0 // for debug
    printf("%2x %2x %d %d\r\n",
      TIM1->CNTRH, TIM1->CNTRL,
      TIM1->CR1 & TIM1_CR1_CEN,
      TIM1->SR1 & TIM1_SR1_UIF);
    for (uint32_t i=0; i<1000000L; i++) {}
#endif
  }

  GPIO_WriteLow(GPIOC, GPIO_PIN_5); // for debug
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
