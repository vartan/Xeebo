/*
 * globals.h
 *
 *  Created on: Feb 12, 2015
 *      Author: vartan
 */
#include <stdint.h>
#ifndef MOTORCONTROLLER_GLOBALS_H_
#define MOTORCONTROLLER_GLOBALS_H

#define SYSTEM_CLOCK 		12000000*4

#define PWM_FREQUENCY 		100
#define MAX_MESSAGE_HANDLER  3


/** PWM resolution step */
#define PWM_RES_STEP        5
 
// DO NOT MODIFY BELOW THIS LINE, FUNCTIONALITY MAY BE BROKEN

#define PWM_RESOLUTION 		100/PWM_RES_STEP
#define MOTOR_TIMER         LPC_CT32B0

#endif /* MOTORCONTROLLER_GLOBALS_H */
