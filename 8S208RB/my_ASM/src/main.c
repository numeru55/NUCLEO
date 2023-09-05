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
    printf("Hello STM8S\n");
    MY_DELAY;

    //u32 odr_address=(u32)&GPIOC->ODR;
    volatile unsigned char *my_odr;
    my_odr=&GPIOC->ODR;

  // __IO uint8_t pin_number=1<<5;

    //printf("odr_address %x\n", odr_address);
    //printf("pin_number %x\n", pin_number);
    printf("odr_address %x\n", &GPIOC->ODR);
    printf("my_odr %x\n", my_odr);
    MY_DELAY;

    uint16_t d=(uint16_t)my_odr;
    //uint16_t d=(uint16_t)(volatile unsigned char *)&GPIO->ODR;
    #if 0
    disableInterrupts();
    (void) my_odr; // to 1st of stack
    (void) d;  // to 2nd of stack
    __asm
        pushw x // sp = [1]x, [3]d, [5]&GPIO->ODR
        ldw x, (#5, sp) // x <- odr_address
        ldw (#3, sp),x
        popw x
    __endasm;
    enableInterrupts();
    #endif

    printf("d %x\n", d);
    MY_DELAY;

#if 0
    disableInterrupts();
    (void) odr_address; // to 1st of stack
    (void) pin_number;  // to 2nd of stack
    __asm
        pushw x // sp = [1]x, [3]odr_address, [5]pin_number
        push a // sp = [1]a, [2]x, [4]odr_address, [6]pin_number
        ldw x, (#4, sp) // x <- odr_address
        ld a, (x) // a <- [odr]
        xor a, (#6, sp)
        ld (x), a
        pop a
        popw x
    __endasm;
    enableInterrupts();
    MY_DELAY;
#endif


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
