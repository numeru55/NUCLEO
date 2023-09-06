/*	INTERRUPT VECTORS TABLE FOR STM8S208
 *	Copyright (c) 2008 by COSMIC Software
 */
extern void _stext();		/* startup routine */

#pragma section const {vector}

void (* const @vector _vectab[32])() = {
	_stext,			/* RESET       */
	0,			/* TRAP        */
	0,			/* TLI         */
	0,			/* AWU         */
	0,			/* CLK         */
	0,			/* EXTI0       */
	0,			/* EXTI1       */
	0,			/* EXTI2       */
	0,			/* EXTI3       */
	0,			/* EXTI4       */
	0,			/* beCAN RX    */
	0,			/* beCAN TX    */
	0,			/* SPI         */
	0,			/* TIMER 1 OVF */
	0,			/* TIMER 1 CAP */
	0,			/* TIMER 2 OVF */
	0,			/* TIMER 2 CAP */
	0,			/* TIMER 3 OVF */
	0,			/* TIMER 3 CAP */
	0,			/* UART1 TX    */
	0,			/* UART1 RX    */
	0,			/* I2C         */
	0,			/* UART3 TX    */
	0,			/* UART3 RX    */
	0,			/* ADC2        */
	0,			/* TIMER 4 OVF */
	0,			/* EEPROM ECC  */
	0,0,0,0,0,		/* Reserved    */
	};
