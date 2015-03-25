/*
 * MotorDriver.h
 *
 *  Created on: Feb 12, 2015
 *      Author: vartan
 */

#ifndef MOTORDRIVER_H_
#define MOTORDRIVER_H_

#define MOTOR_COUNT 6
/**
 * Motor Driver
 *
 * This struct stores all of the information required to control the motors.
 */
struct MotorDriver {
    uint8_t pwmPort;                  /**< Pointer to the pwm pio control register */
    uint8_t pwmPin;
    uint8_t enabledPort;
    uint8_t enabledPin;
    volatile int8_t speed;                    /**< Value which is read/written which
                                      controls motor speed. -100 is full 
                                      backwards, 100 is full forwards, and 0 is 
                                      stop                                    */
};
/**
 * Initialize Motor Drivers
 * @param _motorDrivers Array of struct MotorDriver which describe each of the
 * MOTOR_COUNT motors.
 *
 * Initializes interrupts and MotorDriver structs required to generate the PWM
 * for the motors.
 */
void initMotorDrivers(struct MotorDriver *_motorDrivers);

/**
 * Motor Driver PWM Cycle
 *
 * This function is called by the CT32B0 interrupt controller in order to
 * manage the PWM all motors. Currently the interrupt is called 
 * PWM_FREQUENCY*PWM_RESOLUTION times per second. Future versions
 * of this code will calculate the next timer interrupt based on 
 * calculating when the next change will be required for the pwm cycle.
 */
void motorDriverPWMCycle();

#endif /* MOTORDRIVER_H_ */
