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

  GPIO_Init(GPIOC, GPIO_PIN_5, GPIO_MODE_OUT_PP_HIGH_FAST); // for PC5 LED H:ON, L:OFF

  GPIO_WriteLow(GPIOC, GPIO_PIN_5);

  while (1)
  {
    volatile unsigned char *my_odr = &GPIOC->ODR;
    __IO uint16_t odr_address = (uint16_t)my_odr;
    __IO uint8_t pin_number = GPIO_PIN_5;
    
    //printf("1st pin_number = %x\n", pin_number);

    disableInterrupts();
    (void)odr_address; // to 1st of stack
    (void)pin_number;  // to 2nd of stack
    __asm
      push a
      pushw x // sp = [1]x [3]a [4]odr_address [6]pin_number
      ldw x, (#4, sp) // let x <- odr_address
      ld a, (x) // let a <- [odr]
      or a, (#6, sp) // a <- [odr] or pin_number
      ld (x), a // [odr] <- [odr] or pin_number
      pushw y  // blink loop
      ldw y, #0xffff
      99999$:
        decw y
        jrne 99999$ // JR not equal 0
      popw y // loop end
      neg (#6, sp) // pin_number <- not(pin_number)
      dec (#6, sp)
      ld a, (x) // a <- [odr]
      and a, (#6, sp) 
      ld (x), a // [odr] = [odr] and not(pin_number)
      popw x
      pop a
    __endasm;
    enableInterrupts();

    //printf("2nd pin_number = %x\n", pin_number);

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
