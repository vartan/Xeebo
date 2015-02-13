/*
 * PWM.h
 *
 *  Created on: Feb 12, 2015
 *      Author: vartan
 */

#ifndef MOTORDRIVER_H_
#define MOTORDRIVER_H_

#define MOTOR_COUNT 6

struct MotorDriver {
	uint32_t *pwmRegister;
	uint8_t pwmMask;
	uint32_t *directionRegister;
	uint8_t directionMask;
	int8_t value;
};
void initMotorDrivers(struct MotorDriver *_motorDrivers);
void motorDriverPWMCycle();

#endif /* MOTORDRIVER_H_ */
