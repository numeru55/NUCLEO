/*
 * PushButtons.h
 *
 *  Created on: Sep 27, 2021
 */

#ifndef INC_PUSHBUTTONS_H_
#define INC_PUSHBUTTONS_H_

/*

 This library is for multiple button, with de-bouncing, multiple push recognition.

   waveform
               _____                     ______________
  Button[0]         |||______________||||
               ________                       _________
  Button[1]            |||_________________|||

                ^   ^        ^      ^      ^    ^
                |   |        |      |      |    |
               [A] [B]      [C]    [D]    [E]  [F]

 enum fig

 INIT     [A] Initial state
 PRESSED  [B] Pushed any button. Starts time count.
 PRESSING [C] All buttons are pushed, and de-bouced. Return key bit.
		      For example, 0b11 means "2 buttons are pushed in almost same time."
		      0b1 means "Only first buttons are pushed."
 RELEASE  [D] Main Loop initialize key state, and library waits releasing buttons.
 RELEASED [E] Library detects "all the button is releasing."
   n/a    [F] After de-bounced, library goes initial state, [A].

notice: no care for overflow of HAL_GetTick().

 */

#define MAX_BUTTONS 3 // within 32
#define BUTTON_TIME 75 // in msec


enum Button_State_Value {
	INIT, PRESSED, PRESSING, RELEASE, RELEASED
};

void Button_Init(GPIO_TypeDef *G, uint16_t P);
void Button_Clear();
uint32_t Button_Loop();

#endif /* INC_PUSHBUTTONS_H_ */
