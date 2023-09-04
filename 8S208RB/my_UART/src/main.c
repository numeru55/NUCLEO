/*

from
~/.platformio/platforms/ststm8/examples/spl-uart-simple-printf

onboard osc: no
PA1 MCO from STLINK
User button PE4 close:L open:H onboard pull-up

User LED PC5 on:H off:L

- VCP RX - PA4, TX - PA5 as UART1

PD1 - SWIM

*/

#include "stm8s.h"
#include "stm8s_it.h" /* SDCC patch: required by SDCC for interrupts */
#include "stdio.h"

#define PUTCHAR_PROTOTYPE int putchar(int c)
#define GETCHAR_PROTOTYPE int getchar(void)

void my_setup();
void my_delay(uint8_t c);

void main(void)
{

  my_setup();
  my_delay(3);

  printf("GPIOE->IDR address %x\r\n", &(GPIOE->IDR));

  GPIO_Init(GPIOC, GPIO_PIN_5, GPIO_MODE_OUT_PP_LOW_FAST);

  while (1)
  {
    printf("GPIOE->IDR [4] %d\r\n", ((GPIOE->IDR) & 1<<4) >> 4);

    GPIOC->ODR = (GPIOC->ODR) | 1<<5;
    printf("GPIOC->ODR %02X\r\n", GPIOC->ODR);

    my_delay(2);

    GPIOC->ODR = (GPIOC->ODR) & !(1<<5);
    printf("GPIOC->ODR %02X\r\n", GPIOC->ODR);

    my_delay(1);
  }
}

void my_setup() {
  /* High speed internal clock prescaler: */
  CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);

  UART1_DeInit();
  UART1_Init(
      (uint32_t)9600,
      UART1_WORDLENGTH_8D,
      UART1_STOPBITS_1,
      UART1_PARITY_NO,
      UART1_SYNCMODE_CLOCK_DISABLE,
      UART1_MODE_TXRX_ENABLE);
}

void my_delay(uint8_t c) // wait about c [sec]
{
  for (uint8_t c0 = 0; c0 < c; c0++)
  {
    // simple wait ~1000ms @ 16MHz
    for (uint32_t i = 0; i < 1600000L; i++)
      __asm__("nop");
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
