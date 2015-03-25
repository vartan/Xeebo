/*
 * timers.h
 *
 *  Created on: Feb 12, 2015
 *      Author: vartan
 */

#ifndef MOTORCONTROLLER_TIMERS_H_
#define MOTORCONTROLLER_TIMERS_H_

/**
 * Init Motor Timers
 *
 * Initializes timer which is used to generate control signals for the motors.
 * Generated time depends on PWM_FREQUENCY, PWM_RESOLUTION, and SYSTEM_CLOCK 
 * from globals.h, and TIMER_DIVIDER in timers.h
 */
void initMotorTimers(void);

#endif /* MOTORCONTROLLER_TIMERS_H_ */
