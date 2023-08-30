/*

from
~/.platformio/platforms/ststm8/examples/spl-uart-simple-printf

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

  printf("TIM1 example\n");

  TIM1_DeInit();

  // TIM1_SelectOnePulseMode(TIM1_OPMODE_SINGLE);

  TIM1_TimeBaseInit(
    //15999, // prescaler 0 ... 65535
    3000,
    TIM1_COUNTERMODE_UP, 
    1000,  // period to ARRH/ARRL default
    0);


  TIM1_ITConfig(TIM1_IT_UPDATE, ENABLE);


  uint16_t ms=65535;

  TIM1->ARRH = (uint8_t)(ms >> 8);
  TIM1->ARRL = (uint8_t)(ms);

  //TIM1->CR1 = TIM1->CR1 & 0b11111110;


  TIM1->SR1 = TIM1->SR1 & 0b11111110;
  printf("%2x %2x %d\r\n",TIM1->CNTRH, TIM1->CNTRL, TIM1->SR1 & 1);
  TIM1_ClearFlag(TIM1_FLAG_UPDATE); // 再スタート
  printf("%2x %2x %d\r\n",TIM1->CNTRH, TIM1->CNTRL, TIM1->SR1 & 1);
  
  TIM1->CR1 = TIM1->CR1 | 1;
  printf("Started\n");
  //TIM1_Cmd(ENABLE);

  //while( TIM1->CR1 & 1 ) {} // loop while CEN=1

  //printf("TIM1 end\n");

  while (1)
  {
    printf("%2x %2x %d\r\n",TIM1->CNTRH, TIM1->CNTRL, TIM1->SR1 & 1);
    for (uint32_t i=0; i<1000000L; i++) {}
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
