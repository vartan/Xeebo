/*
 * PWM.h
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
    uint32_t *pwmRegister;       /**< Pointer to the register which drives pwm 
                                      on motor. For our motor, 0% is back, 
                                      100% is forwards, and as 50% is 
                                      approached, speed is decreased          */
    uint8_t pwmMask;             /**< Mask to isolate bits from pwm register  */
    uint32_t *enabledRegister;   /**< Pointer to the register which selects
                                      whether or not the motor is enabled     */
    uint8_t enabledMask;         /**< Mask to isolate bits from en register   */
    int8_t speed;                /**< Value which is read/written which 
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
void motorDriverPWMCycle();

#endif /* MOTORDRIVER_H_ */
