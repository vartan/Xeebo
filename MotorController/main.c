/*
 * main.c
 *
 *  Created on: Feb 12, 2015
 *      Author: vartan
 */
#include "lpc11uxx.h"
#include "main.h"
#include "globals.h"
#include "MotorDriver.h"
#include "timers.h"

int badCountMain = 0;
int main() {
  struct MotorDriver motors[MOTOR_COUNT];
int i;
	initMotorDrivers(motors);
    motors[0].speed = 10;
    motors[1].speed = 20;
    motors[2].speed = 30;
    motors[3].speed = -10;
    motors[4].speed = 75;
    motors[5].speed = 90;
	while(1) {

	    motors[3].speed = motors[3].speed + 1;
	    if(motors[3].speed>=50)
	        motors[3].speed = -50;
			if(MOTOR_TIMER->TC > MOTOR_TIMER->MR0) {
				badCountMain++;
				MOTOR_TIMER->TC = MOTOR_TIMER->MR0 - 1;
			}
			for(i=0;i<600000;i++);


	}
}
