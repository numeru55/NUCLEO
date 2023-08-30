#include "stm8s.h"
#include "stm8s_it.h"    /* SDCC patch: required by SDCC for interrupts */

void main(void)
{

  /* High speed internal clock prescaler: */
  CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);

  GPIO_Init(GPIOC, GPIO_PIN_5, GPIO_MODE_OUT_PP_HIGH_FAST);

  TIM1_DeInit();
  TIM1_TimeBaseInit(  // refer packages - framework ... - Libraries - STM8... - src - stm8_tim1.c
    1599, // prescaler to TIM1->PSCRH, TIM1->PSCRL
    TIM1_COUNTERMODE_UP, 
    5000,  // period to TIM1->ARRH, TIM1->ARRL
    0); // TIM1_RepetitionCounter to TIM1->RCR
  TIM1_ITConfig(TIM1_IT_UPDATE, ENABLE);
  TIM1_Cmd(ENABLE); // set TIM1->CR1 of CEN 

  enableInterrupts();

  while (1)
  {
  }

}

#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

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
