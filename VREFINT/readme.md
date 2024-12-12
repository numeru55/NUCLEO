```main.c
  HAL_ADCEx_Calibration_Start(&hadc1);

  HAL_ADC_Start(&hadc1);

  HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);

  uint32_t VrefValue=HAL_ADC_GetValue(&hadc1);

  float V;
  __IO uint16_t *VrefCal = (__IO uint16_t*)0x1FFF75AA;

  V = 3.3f * (float)*VrefCal / (float)VrefValue;
```

https://qiita.com/kotetsu_yama/items/0efc42b291a94a06f460
