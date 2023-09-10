/*
 * u8g_arm.h
 *
 *  Created on: Sep 7, 2023
 *      Author: numeru55
 */

#ifndef U8G_ARM_H_
#define U8G_ARM_H_

// http://elastic-notes.blogspot.com/p/stm32-i2c-oled-ssd.html

//#include "stm32f1xx_hal.h"
#include "stm32g0xx_hal.h"

#include "u8g.h"

#define DATA_BUFFER_SIZE 1000
#define I2C_TIMEOUT 10000
#define DEVICE_ADDRESS 0x78 //device address is written on back side of your display
#define I2C_HANDLER hi2c1

extern I2C_HandleTypeDef hi2c1; // use your i2c handler

uint8_t u8g_com_hw_i2c_fn(u8g_t *u8g, uint8_t msg, uint8_t arg_val,
		void *arg_ptr);


#endif /* U8G_ARM_H_ */
