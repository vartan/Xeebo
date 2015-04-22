/*
 * MotorDriver.h
 *
 *  Created on: Feb 12, 2015
 *      Author: vartan
 */
#ifndef _MOTORDRIVER_H_
#define _MOTORDRIVER_H_

#define MOTOR_COUNT 6
#include "message_handler.h"
#include "globals.h"

/**
 * Motor Driver
 *
 * This struct stores all of the information required to control the motors.
 */
struct MotorDriver {
    uint8_t pwmPort;                  /**< Pointer to the pwm pio control register */
    uint8_t pwmPin;
    uint8_t directionPort;
    uint8_t directionPin;
    volatile int8_t speed;                    /**< Value which is read/written which
                                      controls motor speed. 0% is stopped, 100% is
                                      full backwards*/
};

union theMotors {
	struct MotorDriver motors[MOTOR_COUNT];
};
/**
 * Initialize Motor Drivers
 * @param _motorDrivers Array of struct MotorDriver which describe each of the
 * MOTOR_COUNT motors.
 *
 * Initializes interrupts and MotorDriver structs required to generate the PWM
 * for the motors.
 */
struct MotorDriver *initMotorDrivers(void);

/**
 * Motor Driver PWM Cycle
 *
 * This function is called by the CT32B0 interrupt controller in order to
 * manage the PWM all motors. Currently the interrupt is called 
 * PWM_FREQUENCY*PWM_RESOLUTION times per second. Future versions
 * of this code will calculate the next timer interrupt based on 
 * calculating when the next change will be required for the pwm cycle.
 */
void motorDriverPWMCycle(void);

void updateMotionVectorHandler(struct message_type *handler, uint8_t *buffer);


#endif /* MOTORDRIVER_H_ */
