/*
 * MotorDriver.c
 *
 *  Created on: Feb 12, 2015
 *      Author: vartan
 */

#include "globals.h"

#include "LPC11Uxx.h"
#include "MotorDriver.h"
#include "timers.h"
struct MotorDriver *motorDrivers;

void initMotorDrivers(struct MotorDriver *_motorDrivers) {
    uint8_t i;
	motorDrivers = _motorDrivers;


    motorDrivers[0].enabledPort   = 0;
    motorDrivers[0].enabledPin    = 21;
    motorDrivers[0].pwmPort       = 0;
    motorDrivers[0].pwmPin        = 22;

    motorDrivers[1].enabledPort   = 0;
    motorDrivers[1].enabledPin    = 3;
    motorDrivers[1].pwmPort       = 0;
    motorDrivers[1].pwmPin        = 4;

    motorDrivers[2].enabledPort   = 0;
    motorDrivers[2].enabledPin    = 5;
    motorDrivers[2].pwmPort       = 0;
    motorDrivers[2].pwmPin        = 6;

    motorDrivers[3].enabledPort   = 0;
    motorDrivers[3].enabledPin    = 8;
    motorDrivers[3].pwmPort       = 0;
    motorDrivers[3].pwmPin        = 7; // led?

    motorDrivers[4].enabledPort   = 0;
    motorDrivers[4].enabledPin    = 9;
    motorDrivers[4].pwmPort       = 0;
    motorDrivers[4].pwmPin        = 16;

    motorDrivers[5].enabledPort   = 0;
    motorDrivers[5].enabledPin    = 17;
    motorDrivers[5].pwmPort       = 0;
    motorDrivers[5].pwmPin        = 18;

    motorDrivers[6].enabledPort   = 0;
    motorDrivers[6].enabledPin    = 19;
    motorDrivers[6].pwmPort       = 0;
    motorDrivers[6].pwmPin        = 20;





    for(i=0;i<MOTOR_COUNT;i++) {
        motorDrivers[i].speed                         = 0;
        LPC_GPIO->DIR[motorDrivers[i].pwmPort] |= 1<<motorDrivers[i].pwmPin;
        LPC_GPIO->DIR[motorDrivers[i].enabledPort] |= 1<<motorDrivers[i].enabledPin;
        if(!motorDrivers[i].pwmPort)
            LPC_GPIO->B0[motorDrivers[i].pwmPin]     |= (1<<3) | (1<<4);
        else
            LPC_GPIO->B1[motorDrivers[i].pwmPin]     |= (1<<3) | (1<<4);

        if(!motorDrivers[i].enabledPort)
            LPC_GPIO->B0[motorDrivers[i].enabledPin] |= (1<<3) | (1<<4);
        else
            LPC_GPIO->B1[motorDrivers[i].enabledPin] |= (1<<3) | (1<<4);
    }


	initMotorTimers();
}

void motorDriverPWMCycle() {
	static uint32_t currentPWMCycle;

	uint32_t nextPWMCycle, motorPWM, i;
	int8_t motorValue;

	// by default, the next PWM cycle is the rollover
	nextPWMCycle = PWM_RESOLUTION;
	// loop through each motor
	for(i = 0; i < MOTOR_COUNT; i++) {
	    motorValue = motorDrivers[i].speed;
        // add 100 to motor value in order to convert from [-100, 100] to [0, 100]
	    motorPWM = motorValue*PWM_RESOLUTION/200 + PWM_RESOLUTION/2;
	    if(motorValue == 0) {
	    	// disable motor
            LPC_GPIO->CLR[motorDrivers[i].enabledPort] |= 1<<motorDrivers[i].enabledPin;
		    // turn off motor pwm
            LPC_GPIO->CLR[motorDrivers[i].pwmPort]     |= 1<<motorDrivers[i].pwmPin;
		} else if(motorPWM >= currentPWMCycle) {
			// force enable motor
            LPC_GPIO->SET[motorDrivers[i].enabledPort] |= 1<<motorDrivers[i].enabledPin;
	        // high motor PWM
            LPC_GPIO->SET[motorDrivers[i].pwmPort]     |= 1<<motorDrivers[i].pwmPin;
		} else {
			// force enable motor
            LPC_GPIO->SET[motorDrivers[i].enabledPort] |= 1<<motorDrivers[i].enabledPin;
	        // low motor PWM
            LPC_GPIO->CLR[motorDrivers[i].pwmPort]     |= 1<<motorDrivers[i].pwmPin;
		}
	    // this motor is the next motor to pay attention to if it is
	    // the closest one after the current cycle
	    if(motorPWM < nextPWMCycle && motorPWM > currentPWMCycle) {
	        nextPWMCycle = motorPWM;
	    }
	}
    MOTOR_TIMER->MR[0] = (nextPWMCycle - currentPWMCycle) % PWM_RESOLUTION;

	// calculate next "current PWM cycle" value
	currentPWMCycle = (nextPWMCycle)%PWM_RESOLUTION;

	// fire the next interrupt when the next motor switch must occur
}
