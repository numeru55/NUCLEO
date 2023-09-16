/*
 * PushButtons.c
 *
 *  Created on: Sep 27, 2021
 */

#include "main.h"
#include "PushButtons.h"

uint8_t BUTTON_NUM=0;

struct BUTTON_BUFFER_struct {
	GPIO_TypeDef *GPIOx;
	uint16_t GPIO_Pin;
} BUTTON_BUFFER[MAX_BUTTONS];


void Button_Init(GPIO_TypeDef *G, uint16_t P){
	BUTTON_BUFFER[BUTTON_NUM].GPIOx = G;
	BUTTON_BUFFER[BUTTON_NUM].GPIO_Pin = P;
	BUTTON_NUM++;
}

uint32_t BUTTON_CODE=0; // previous key code
uint32_t BUTTON_PREV_TIME=0; // previous time

enum Button_State_Value BUTTON_STATE=INIT;

void Button_Clear(){
	BUTTON_STATE=RELEASE;
}

uint32_t Button_Loop(){
	uint32_t current_key=0xffffffff;
	for (int i=BUTTON_NUM-1; (i>0)|(i==0); i--) {
		current_key = (current_key<<1) |
				(HAL_GPIO_ReadPin(BUTTON_BUFFER[i].GPIOx, BUTTON_BUFFER[i].GPIO_Pin));
	}

	current_key = ~current_key;

	// return current_key;

	switch (BUTTON_STATE) {
		case INIT:
			if (current_key>0) {
				BUTTON_STATE=PRESSED;
				BUTTON_CODE=current_key;
				BUTTON_PREV_TIME=HAL_GetTick();
			}
			return 0;
			break;
		case PRESSED:
			if (current_key > BUTTON_CODE ) { // means push more buttons
				BUTTON_CODE = current_key;
				BUTTON_PREV_TIME=HAL_GetTick();
				return 0;
			}
			if (HAL_GetTick()-BUTTON_PREV_TIME > BUTTON_TIME) {
				BUTTON_STATE=PRESSING;
				return current_key;
			}
			return 0;
			break;
		case PRESSING: //  means returned keycode but main loop is not clear.
			return BUTTON_CODE;
			break;
		case RELEASE:
			if (current_key == 0) {
				BUTTON_STATE=RELEASED;
				BUTTON_PREV_TIME=HAL_GetTick();
			}
			return 0;
			break;
		case RELEASED:
			if (current_key>1) {
				BUTTON_STATE=RELEASE;
				return 0;
			}
			if (HAL_GetTick()-BUTTON_PREV_TIME > BUTTON_TIME) {
				BUTTON_STATE=INIT;
			}
			return 0;
			break;
	}
	return 0; // never reach
}
