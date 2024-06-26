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

#define MY_DELAY                         \
  for (uint32_t i = 0; i < 1000000; i++) \
  {                                      \
  }

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

  ADC2->CR1 = (ADC2->CR1 & 0b10001100) |
              (0b000 << 4) | // [6:4] SPSEL=0 prescaler
              (0b0 << 1) |   // [1] CONT=0 single mode
              (0b1 << 0);    // [0] ADON=1
  ADC2->CR2 = ADC2_CR2_RESET_VALUE | ADC2_CR2_ALIGN; // to right align
  ADC2->CSR = ADC2_CSR_RESET_VALUE; // reset CSR means select CH=0.

  printf("ADC2 setup\n");
  MY_DELAY;

  while (1)
  {
    ADC2->CR1 |= ADC2_CR1_ADON; // start ADC
    while ((ADC2->CSR & ADC2_CSR_EOC) ^ ADC2_CSR_EOC)
    {
      // printf("CR1 %02x\n", ADC2->CR1);
      // printf("CSR %02x\n", ADC2->CSR);
      // MY_DELAY;
    }

    uint8_t adcL = ADC2->DRL;
    uint8_t adcH = ADC2->DRH;
    ADC2->CSR &= (~ADC2_CSR_EOC); // clean EOC
    // printf("DRH %d\n",adcH);
    // printf("DRL %d\n",adcL);
    printf("DATA %d\n", ((adcH << 8) | adcL));
    MY_DELAY;
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
