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
    /*
    //Ensure clock is enabled for C32B0
    //  Bit 9: C32B0
    //    0: Disable clock
    //    1: Enable clock (Default, redundant)
    LPC_SYSCON->SYSAHBCLKCTRL |= 1<<9;

    //Prescale register
    //  Prescale register will be the minimum wait time for PWM
    MOTOR_TIMER->PR = SYSTEM_CLOCK /
            (PWM_FREQUENCY * PWM_RESOLUTION) - 1;

    //Match Register
    //  Match at PWM_RESOLUTION * PWM_FREQUENCY SECONDS
    MOTOR_TIMER->MR[0] = 200; // wait whole cycle for first interrupt to be triggered

    //TCR
    //  BIT 0: CEN
    //    0: The counters are disabled
    //    1: The Timer Counter and Prescale Counter are enabled for counting.
    MOTOR_TIMER->TCR |= 1<<0;

    //Match Control Register
    //  Bit 0: MR0I - Interrupt on MR0
    //    0: Disabled
    //    1: Enabled
    MOTOR_TIMER->MCR |= (1<<0) | (1<<1);

    //Count Control Register
    //  Bit 1:0
    //    00: Timer counter - every rising PCLK edge (Default, redundant)
    MOTOR_TIMER->CTCR &= ~( (1<<0) | (1<<1) );
    MOTOR_TIMER->TCR = (MOTOR_TIMER->TCR & (~(1<<1))) | (1<<0);
*/
    NVIC_EnableIRQ(TIMER_32_0_IRQn);
    NVIC_SetPriority(TIMER_32_0_IRQn, 0);
    LPC_SYSCON->SYSAHBCLKCTRL |= 1 << 9;          // enable 16-bit timer0 clock
    MOTOR_TIMER->CTCR = 0;                         // disable counter mode
    MOTOR_TIMER->IR   = 0x1F;                      // interrupt flag
    MOTOR_TIMER->TCR  = (1<<1);       // disable/reset timer

    MOTOR_TIMER->PR   = SYSTEM_CLOCK /
            (PWM_FREQUENCY * PWM_RESOLUTION) - 1;        // set prescaler
    MOTOR_TIMER->MR0  = 200;           // set match register

    MOTOR_TIMER->MCR  = (1<<0) | (1<<1);      // enable interrupts/autoreset

    MOTOR_TIMER->TCR  = (1<<0);       // enable run
}
int timerLoopCount = 0;
    int badCount = 0;

void TIMER32_0_IRQHandler() {
    int interrupt = MOTOR_TIMER->IR;
    MOTOR_TIMER->IR = interrupt; // immediately clear interrupt

    //MOTOR_TIMER->TCR  = (1<<1);       // disable/reset timer
    motorDriverPWMCycle();
    timerLoopCount++;
        if(MOTOR_TIMER->TC > MOTOR_TIMER->MR0) {
            badCount++;
            MOTOR_TIMER->TC = MOTOR_TIMER->MR0;
        }
    //MOTOR_TIMER->TCR  = (1<<0);       // enable run
}
