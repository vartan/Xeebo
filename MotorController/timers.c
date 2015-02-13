/*
 * timers.c
 *
 *  Created on: Feb 12, 2015
 *      Author: vartan
 */
#include "lpc11uxx.h"
#include "timers.h"
#include "globals.h"
#include "MotorDriver.h"
void initMotorTimers() {
	//Ensure clock is enabled for C32B0
	//  Bit 9: C32B0
	//    0: Disable clock
	//	  1: Enable clock (Default, redundant)
	LPC_SYSCON->SYSAHBCLKCTRL |= 1<<9;

	//Prescale register
	//  Ignoring prescale register, our min frequency can be 90Hz
	LPC_CT32B0->PC = TIMER_DIVIDER - 1;

	//Match Register
	//  Match at PWM_RESOLUTION * PWM_FREQUENCY SECONDS
	LPC_CT32B0->MR[0] = SYSTEM_CLOCK/(PWM_FREQUENCY * PWM_RESOLUTION * TIMER_DIVIDER);

	//CTCR
	//  BIT 0: CEN
	//    0: The counters are disabled
	//    1: The Timer Counter and Prescale Counter are enabled for counting.
	LPC_CT32B0->CTCR |= 1<<0;

	//Match Control Register
	//  Bit 0: MR0I - Interrupt on MR0
	//    0: Disabled
	//    1: Enabled
	LPC_CT32B0->MCR |= 1<<0;

	//Count Control Register
	//  Bit 1:0
	//    00: Timer counter - every rising PCLK edge (Default, redundant)
	LPC_CT32B0->CTCR &= ~( (1<<0) | (1<<1) );

	NVIC_EnableIRQ(TIMER_32_1_IRQn);
}
void TIMER32_0_IRQHandler() {
	motorDriverPWMCycle();
}
