/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "my_SSD1306.h"
#include "PushButtons.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;

I2C_HandleTypeDef hi2c1;

TIM_HandleTypeDef htim16;
TIM_HandleTypeDef htim17;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

volatile uint16_t ADC_result_buffer[256];
volatile uint8_t ADC_buffer_count=255; // 0 ... 255 running

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_I2C1_Init(void);
static void MX_TIM17_Init(void);
static void MX_ADC1_Init(void);
static void MX_TIM16_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){

    if(htim == &htim16) {
    	if (ADC_buffer_count < 255) {
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
            ADC_result_buffer[ADC_buffer_count++]=HAL_ADC_GetValue(&hadc1);
    	}
    }
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
    setbuf(stdout, NULL);
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_I2C1_Init();
  MX_TIM17_Init();
  MX_ADC1_Init();
  MX_TIM16_Init();
  /* USER CODE BEGIN 2 */

	HAL_ADCEx_Calibration_Start(&hadc1);

	HAL_ADC_Start(&hadc1);
	//HAL_ADC_Start_DMA(&hadc1, (uint32_t *)&ADC_result_buffer, sizeof(ADC_result_buffer) / sizeof(ADC_result_buffer[0]));
	//HAL_ADC_Start_DMA(&hadc1, (uint32_t *)&ADC_result_buffer, 1);
	//hdma_adc1.Instance->CCR &= ~(DMA_IT_TC | DMA_IT_HT);
	//   __HAL_DMA_DISABLE_IT(&hdma_adc, DMA_IT_TC);
	//__HAL_DMA_DISABLE_IT(&hdma_adc1, DMA_IT_TC);

	HAL_TIM_Base_Start_IT(&htim16);

	HAL_TIM_PWM_Start(&htim17, TIM_CHANNEL_1);

	OLED_Init(&hi2c1);

	OLED_clear(); // and set cursor to 0,0
	//      12345678901234
	printf("Boot nucleo\n");
	printf("  G070RB");

	HAL_Delay(1000);

	OLED_clear(); // and set cursor to 0,0
	//printf("push button\n");

	/*
	 * TIM17 仮PWMの状況を表示する
	 * プリスケーラー 63999 PSC
	 * リロード値 49 ARR
	 * 比較値 24 CCR1
	 *
	 * 周波数 64MHz / (PSC+1) / (ARR+1) = 20Hz
	 * ON Duty = (CCR1 + 1) / (ARR + 1) = 50%
	 *
	 *  PSC  ARR CCR1  Hz Duty
	 * 63999  49  24   20  50
	 * 63999   9   4  100  50
	 *
	 */

	TIM17->PSC = 639;
	TIM17->ARR = 9;
	TIM17->CCR1 = 4;

#if 0
	printf("PSC ARR CCR1\n");
	printf("%d %d %d", TIM17->PSC, TIM17->ARR, TIM17->CCR1);

	while(
			HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5) &
			HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3) &
			HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10)
			) {}

	OLED_clear(); // and set cursor to 0,0
	HAL_Delay(100);
#endif

	printf("TIM17 %dHz\n", 64000000 / ((TIM17->PSC)+1) / ((TIM17->ARR)+1));
	printf("duty %d%%", ((TIM17->CCR1)+1) * 100 / ((TIM17->ARR)+1));

	while(
			HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5) &
			HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3) &
			HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10)
			) {}

	OLED_clear(); // and set cursor to 0,0
	HAL_Delay(100);

	// 上から見て PA10 PB3 PB5 の順番 CPU内プルアップ必要

	Button_Init(GPIOB, GPIO_PIN_5);   // bit 0
	Button_Init(GPIOB, GPIO_PIN_3);   // bit 1
	Button_Init(GPIOA, GPIO_PIN_10);  // bit 2

	enum {
		SAMPLING, STOPPED
	} AD_STATUS = SAMPLING;

	enum {
		RISE, FALL
	} TRIGGER_SELECT = RISE;

	/*
	 * TIM16で割り込みをかけてADしている
	 */

	struct {
		char *name;
		uint16_t prescaler;
		uint16_t reload;
	} sampling_table[] = {
			{ "320k", 24, 7 },
			{ "250k", 31, 7 },
			{ "100k", 63, 9 },
			{ " 50k", 63, 19 },
			{ " 25k", 63, 39 },
			{ " 10k", 63, 99 },
			{ "  5k", 63, 199 },
			{ "2.5k", 63, 399 },
			{ "  1k", 63, 999 },
			{ " 100", 639, 999 }
	};

#define SAMPLING_VALUE_MAX 9

	uint8_t SAMPLING_VALUE = 3;

	/*
	 * 単にSAMPLING_VALUE からペリフェラルレジスタをセットするだけの関数
	 */

	void set_sampling_rate() {
		TIM16->PSC = sampling_table[SAMPLING_VALUE].prescaler;
		TIM16->ARR = sampling_table[SAMPLING_VALUE].reload;
	}

	set_sampling_rate();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	  /*
	   * とにかく先に状況をを描画する
	   */

	  OLED_set_cursor(0, 2);
	  if (AD_STATUS == SAMPLING) {
		  printf("RUN  ");
	  } else {
		  printf("STOP ");
	  }
	  if (TRIGGER_SELECT == RISE) {
		  printf("_|- ");
	  } else {
		  printf("-|_ ");
	  }
	  printf("%s", sampling_table[SAMPLING_VALUE].name);

	  if (AD_STATUS == SAMPLING) {

		  // AD sampling main

		  ADC_buffer_count = 0; // means start sampling

		  //OLED_set_cursor(0, 0);
		  //printf("Running...");
		  while(ADC_buffer_count < 255) {} // wait finish sampling. stored ADC_result_buffer[0...127]

		  /*
		   * bit 0 -+  display_buffer_0  (AD>>2) = 15
		   * bit 1  |
		   *  ..
		   * bit 7 -+                    (AD>>2) = 8
		   *
		   * bit 0 -+  display_buffer_1  (AD>>2) = 7
		   * bit 1  |
		   *  ..
		   * bit 7 -+                    (AD>>2) = 0
		   *
		   */

		  uint8_t display_buffer_1[256];
		  uint8_t display_buffer_0[256];
		  uint8_t trigger;
		  trigger=0;

		  for (uint8_t i=0; i<255; i++) {
			  ADC_result_buffer[i] = ADC_result_buffer[i] >> 2;
			  uint8_t y0, y1;
			  if (i<1) {
				  y0=ADC_result_buffer[i];
				  y1=y0;
			  } else {
				  if (ADC_result_buffer[i]>ADC_result_buffer[i-1]) {
					  y0=ADC_result_buffer[i-1];
					  y1=ADC_result_buffer[i];
				  } else {
					  y0=ADC_result_buffer[i];
					  y1=ADC_result_buffer[i-1];
				  }
				  /*
				   * ついでにトリガーを探す 100までの限定
				   */
				  if ( (trigger==0) && (i>8) && (i<100) && (y0<8) && (y1>7)){
					  if ((TRIGGER_SELECT == RISE) && (ADC_result_buffer[i-1]<ADC_result_buffer[i])) {
						  trigger=i-8;
					  } else {
						  if ((TRIGGER_SELECT == FALL) && (ADC_result_buffer[i-1]>ADC_result_buffer[i])) {
							  trigger=i-8;
						  }
					  }
				  }

			  }

			  /*  今の値と前の値を使ってバー状にドットを作る。
			   *  0<= y0 <= y1 <= 0
			   *  for example...
			   *  y0=3, y1=10 ... result_0 0b1110 0000 result_1 0b0001 1111
			   *
			   *  y1=10 means result_16_1 = 0b1111 1111 1110 0000 = (0xffff) << (15-y1)
			   *  y0=3  means result_16_0 = 0b0001 1111 1111 1111 = (0xffff) >> y0
			   *                               AND       AND
			   *                             result_1   result_0
			   */

			  uint16_t result_16_1 = (0xffff) << (15-y1);
			  uint16_t result_16_0 = (0xffff) >> y0;
			  display_buffer_0[i] = ( result_16_1 & result_16_0 ) & 0xff;
			  display_buffer_1[i] = ( result_16_1 & result_16_0 ) >> 8;
		  }

		  OLED_set_cursor(0, 0);
		  //OLED_put_len(&ADC_result_buffer, 128);
//		  OLED_put_len(trigger + (&display_buffer_0), 128);
		  OLED_put_len((uint8_t *)&display_buffer_0+trigger, 128);
		  OLED_set_cursor(0, 1);
		  OLED_put_len((uint8_t *)&display_buffer_1+trigger, 128);

		  //OLED_set_cursor(0, 0);
		  //printf("%d %d %d  ", ADC_result_buffer[0], TIM16->PSC, TIM16->ARR);

	  }


	  //   PA10 PB3 PB5
	  // bit 2   1   0

	uint32_t k = Button_Loop();
	if (k) {
		Button_Clear();
		if (AD_STATUS == SAMPLING) {
			if (k & 0b100) {
				// TRIGGER_SELECT = (!(TRIGGER_SELECT)) & 1;
				AD_STATUS = STOPPED;
			} else {
				// change sampling rate
				// TIM16->PSC, TIM16->ARR
				if (k & 0b10) {
					if (SAMPLING_VALUE>0) { SAMPLING_VALUE--; }
				} else {
					if (SAMPLING_VALUE < SAMPLING_VALUE_MAX) { SAMPLING_VALUE++; }
				}
				/*
				TIM16->PSC = sampling_table[SAMPLING_VALUE].prescaler;
				TIM16->ARR = sampling_table[SAMPLING_VALUE].reload;
				 */
				set_sampling_rate();
			}
		} else {
			if (k & 0b100) {
				// TRIGGER_SELECT = (!(TRIGGER_SELECT)) & 1;
				AD_STATUS = SAMPLING;
			} else {
				if (k & 0b10) {
					TRIGGER_SELECT=FALL;
				} else {
					TRIGGER_SELECT=RISE;
				}
			}
		}
	}

  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV1;
  RCC_OscInitStruct.PLL.PLLN = 8;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
  hadc1.Init.Resolution = ADC_RESOLUTION_6B;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc1.Init.LowPowerAutoWait = DISABLE;
  hadc1.Init.LowPowerAutoPowerOff = DISABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;
  hadc1.Init.SamplingTimeCommon1 = ADC_SAMPLETIME_1CYCLE_5;
  hadc1.Init.SamplingTimeCommon2 = ADC_SAMPLETIME_1CYCLE_5;
  hadc1.Init.OversamplingMode = DISABLE;
  hadc1.Init.TriggerFrequencyMode = ADC_TRIGGER_FREQ_HIGH;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLINGTIME_COMMON_1;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x00602173;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief TIM16 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM16_Init(void)
{

  /* USER CODE BEGIN TIM16_Init 0 */

  /* USER CODE END TIM16_Init 0 */

  /* USER CODE BEGIN TIM16_Init 1 */

  /* USER CODE END TIM16_Init 1 */
  htim16.Instance = TIM16;
  htim16.Init.Prescaler = 63;
  htim16.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim16.Init.Period = 999;
  htim16.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim16.Init.RepetitionCounter = 0;
  htim16.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim16) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM16_Init 2 */

  /* USER CODE END TIM16_Init 2 */

}

/**
  * @brief TIM17 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM17_Init(void)
{

  /* USER CODE BEGIN TIM17_Init 0 */

  /* USER CODE END TIM17_Init 0 */

  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  /* USER CODE BEGIN TIM17_Init 1 */

  /* USER CODE END TIM17_Init 1 */
  htim17.Instance = TIM17;
  htim17.Init.Prescaler = 63999;
  htim17.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim17.Init.Period = 49;
  htim17.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim17.Init.RepetitionCounter = 0;
  htim17.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim17) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_OC_Init(&htim17) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_TOGGLE;
  sConfigOC.Pulse = 24;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_OC_ConfigChannel(&htim17, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  __HAL_TIM_ENABLE_OCxPRELOAD(&htim17, TIM_CHANNEL_1);
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.BreakFilter = 0;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim17, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM17_Init 2 */

  /* USER CODE END TIM17_Init 2 */
  HAL_TIM_MspPostInit(&htim17);

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_7B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart2, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart2, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : LED_GREEN_Pin */
  GPIO_InitStruct.Pin = LED_GREEN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(LED_GREEN_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PA10 */
  GPIO_InitStruct.Pin = GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB3 PB5 */
  GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

// printf from
// https://yukblog.net/stm32cubeide-printf-uart/

int _write(int file, char *ptr, int len)
{
  //HAL_UART_Transmit(&huart2,(uint8_t *)ptr,len,10);
	for (int i=0; i<len; i++) {
		OLED_put_c(ptr[i]);
	}
  return len;
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
