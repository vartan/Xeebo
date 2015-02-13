/*
 * PWM.c
 *
 *  Created on: Feb 12, 2015
 *      Author: vartan
 */

#include "globals.h"

#include "MotorDriver.h"
#include "timers.h"
struct MotorDriver *motorDrivers;

void initMotorDrivers(struct MotorDriver *_motorDrivers) {
	motorDrivers = _motorDrivers;
	initMotorTimers();
}

void motorDriverPWMCycle() {
	static uint8_t currentPWMCycle;

	int i, motorValue;
	for(i = 0; i < MOTOR_COUNT; i++) {
	    motorValue = motorDrivers[i].speed;
	    // add 100 to motor value in order to convert from [-100, 100] to [0, 100]
		if(motorValue && motorValue + 100 > currentPWMCycle) {
	        *motorDrivers[i].enabledRegister |= motorDrivers[i].enabledMask;
		    *motorDrivers[i].pwmRegister |= motorDrivers[i].pwmMask;
		} else {
		    *motorDrivers[i].enabledRegister &= ~motorDrivers[i].enabledMask;
		    *motorDrivers[i].enabledRegister &= ~motorDrivers[i].pwmMask;
		}
	}
	currentPWMCycle = (currentPWMCycle + 1) % PWM_RESOLUTION;
}
