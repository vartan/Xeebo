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

/**
 * Update Motion Vector Handler
 * @param handler Pointer to MotionVector info being handled
 * @param buffer  Pointer to message.
 */
void updateMotionVectorHandler(struct message_type *handler, uint8_t *buffer);


/**
 * Motors Driven By Vector
 * @param  motor1                Pointer to first motor
 * @param  motor2                Pointer to second motor
 * @param  vector1               First vector which modifies the motor
 * @param  vector1motor1modifier How vector 1 modifies motor 1 (most likely 
 *                               -1 or 1 depending on motor direction)
 * @param  vector1motor2modifier How vector 1 modifies motor 2 (most likely 
 *                               -1 or 1 depending on motor direction)
 * @param  vector2               Second vector which modifies the motor
 * @param  vector2motor1modifier How vector 2 modifies motor 1 (most likely 
 *                               -1 or 1 depending on motor direction)
 * @param  vector2motor2modifier How vector 2 modifies motor 2 (most likely 
 *                               -1 or 1 depending on motor direction)
 * @return                       void
 */
void motorsDrivenByVectors(volatile int8_t *motor1, volatile int8_t *motor2, 
        int8_t vector1, int8_t vector1motor1modifier, 
        int8_t vector1motor2modifier, int8_t vector2, 
        int8_t vector2motor1modifier, int8_t vector2motor2modifier);
#endif /* MOTORDRIVER_H_ */
