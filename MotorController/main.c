/*
 * main.c
 *
 *  Created on: Feb 12, 2015
 *      Author: vartan
 */
#include "lpc11uxx.h"
#include "main.h"
#include "MotorDriver.h"



int main() {
	struct MotorDriver motors[MOTOR_COUNT];

	initMotorDrivers(motors);
	while(1) {
	}
}
