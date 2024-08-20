# CPU SPEC

- L452RE 80MHz 512kB Flash 160kB RAM  1 - Op-Amp 1 - DAC
- G431RB 170MHz 128kB Flash 22kB RAM 3-Op-Amp 4-DAC
- G0B1RE 64MHz 512kB Flash 144kB RAM  3 - Comparators 1- DAC
- G070RB 64MHz 128kB Flash 36kB RAM
- G031F8 64MHz 64kB Flash 8kB RAM
- F303K8 72MHz 64kB Flash 12kB RAM 4-PGA 2-DAC
- L432KC 80MHz 256kB Flash 64kB RAM 1-Op-Amp 2-DAC
- 

# タイマーの解説

難しいけど

https://www.st.com/resource/ja/application_note/an4776-generalpurpose-timer-cookbook-for-stm32-microcontrollers-stmicroelectronics.pdf

# STM32CubeIDEでcppを扱う

ほぼこの方法でいける

https://qiita.com/FlechaMaker/items/de9c663d1b394e5a2862

# C レジスターに直接アクセスする

```c
  /* USER CODE BEGIN 2 */

  TIM6->SR = (TIM6->SR) & 0xfffffffe; // clear UIF
  HAL_TIM_Base_Start(&htim6);

  HAL_Delay(100);
  uint32_t f0=(TIM6->SR) & 1; // UIF
  uint32_t c0=TIM6->CNT;

  HAL_Delay(1000); // TIM6 finished.

  HAL_Delay(50);
  uint32_t f1=(TIM6->SR) & 1; // UIF
  uint32_t c1=TIM6->CNT;

  /* USER CODE END 2 */
```

```c
  uint16_t a=   TIM14->CCR1;

  // 中略

  while (1)
  {
	  if ( HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_5) == HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_9)) {
		  TIM14->CCR1 = 80;
		  HAL_Delay(1000);

	  } else {
		  TIM14->CCR1 = 10;
		  HAL_Delay(1000);
	  }
```

# 雑多メモ

```main.c
#include <stdio.h>

int my_print(unsigned char * p, unsigned char q) {
    for (int i=0; i<q; i++) {
        printf("%d\n", p[i]);
    }
}

int main(void){
    // Your code here!
    unsigned char data[]={0,1,2,3,4};
    my_print((unsigned char *)&data+2, 3);
}
```
実行結果
```
2
3
4
```
