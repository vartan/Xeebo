/*
 * PWM.c
 *
 *  Created on: Feb 12, 2015
 *      Author: vartan
 */

/*
typedef struct {
	uint32_t *pwmRegister;
	uint8_t pwmMask;
	uint32_t *directionRegister;
	uint8_t directionMask;
	int8_t value;
} PWM_Pin;

static PWM_Pin *pwmPins;
static uint8_t pwmPinCount;*/
#include "globals.h"

#include "MotorDriver.h"
#include "timers.h"
struct MotorDriver *motorDrivers;

void initMotorDrivers(struct MotorDriver *_motorDrivers) {
	motorDrivers = _motorDrivers;
	initMotorTimers();
}

void motorDriverPWMCycle() {
	static uint8_t currentPWMPercent;

	int i;
	struct MotorDriver motor;
	for(i = 0; i < MOTOR_COUNT; i++) {
		motor = motorDrivers[i];
		if(motor.value > currentPWMPercent) {
			*motor.pwmRegister |= motor.pwmMask;
			if(motor.value<0)
				*motor.directionRegister |= motor.directionMask;
			else
				*motor.directionRegister &= ~motor.directionMask;

		} else {
			*motor.pwmRegister &= (~motor.pwmMask);
		}
	}
	currentPWMPercent++;
}
