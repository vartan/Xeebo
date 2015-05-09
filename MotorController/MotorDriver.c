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
#include "message_handler.h"

static struct MotorDriver motorDrivers[] = {
    // motor 0: pitch_bow
    {.directionPort = 0, .directionPin = 21, .pwmPort = 0, .pwmPin = 22, .speed = 0}, 
    // motor 1: pitch_stern
    {.directionPort = 0, .directionPin = 3,  .pwmPort = 0, .pwmPin = 4,  .speed = 0},
    // motor 2: yaw_port
    {.directionPort = 0, .directionPin = 5,  .pwmPort = 0, .pwmPin = 6,  .speed = 0},
    // motor 3: yaw_starboard
    {.directionPort = 0, .directionPin = 8,  .pwmPort = 0, .pwmPin = 7,  .speed = 0},
    // motor 4: roll_top
    {.directionPort = 0, .directionPin = 9,  .pwmPort = 0, .pwmPin = 16, .speed = 0},
    // motor 5: roll_bottom
    {.directionPort = 0, .directionPin = 17, .pwmPort = 0, .pwmPin = 20, .speed = 0},
};

    struct my_motor_config {
        struct MotorDriver pitch_bow;
        struct MotorDriver pitch_stern;
        struct MotorDriver yaw_port;
        struct MotorDriver yaw_starboard;
        struct MotorDriver roll_top;
        struct MotorDriver roll_bottom;
    };
		struct my_motor_config *motorConfiguration = (struct my_motor_config *)&motorDrivers;

struct MotorDriver *initMotorDrivers() {
    uint8_t i;

    for(i=0;i<MOTOR_COUNT;i++) {
        motorDrivers[i].speed = 0;
        LPC_GPIO->DIR[motorDrivers[i].pwmPort] |= 1<<motorDrivers[i].pwmPin;
        LPC_GPIO->DIR[motorDrivers[i].directionPort] |= 1<<motorDrivers[i].directionPin;
        if(!motorDrivers[i].pwmPort)
            LPC_GPIO->B0[motorDrivers[i].pwmPin]     |= (1<<3) | (1<<4);
        else
            LPC_GPIO->B1[motorDrivers[i].pwmPin]     |= (1<<3) | (1<<4);

        if(!motorDrivers[i].directionPort)
            LPC_GPIO->B0[motorDrivers[i].directionPin] |= (1<<3) | (1<<4);
        else
            LPC_GPIO->B1[motorDrivers[i].directionPin] |= (1<<3) | (1<<4);
    }
    initMotorTimers();
    return motorDrivers;
}

void motorDriverPWMCycle() {
    static uint32_t currentPWMCycle;

    uint32_t nextPWMCycle, motorPWM, i;
    int8_t motorValue;

    // by default, the next PWM cycle is the rollover
    nextPWMCycle = PWM_RESOLUTION;
    // loop through each motor
    for(i = 0; i < MOTOR_COUNT; i++) {
        // absolute motor value
        motorValue = motorDrivers[i].speed>0?motorDrivers[i].speed:-motorDrivers[i].speed;
        if(motorDrivers[i].speed > 0) {
            LPC_GPIO->CLR[motorDrivers[i].directionPort] |= 1<<motorDrivers[i].directionPin;
        } else {
            LPC_GPIO->SET[motorDrivers[i].directionPort] |= 1<<motorDrivers[i].directionPin;
        }
                
        // add 100 to motor value in order to convert from [-100, 100] to [0, 100]
        motorPWM = motorValue*PWM_RESOLUTION/100;
            
        if(motorPWM > currentPWMCycle) {
            // force enable motor
            LPC_GPIO->SET[motorDrivers[i].pwmPort]     |= 1<<motorDrivers[i].pwmPin;
        } else {
            // low motor PWM
            LPC_GPIO->CLR[motorDrivers[i].pwmPort]     |= 1<<motorDrivers[i].pwmPin;
        }
        // this motor is the next motor to pay attention to if it is
        // the closest one after the current cycle
        if(motorPWM < nextPWMCycle && motorPWM > currentPWMCycle) {
            nextPWMCycle = motorPWM;
        }
    }
    MOTOR_TIMER->MR0 = (nextPWMCycle - currentPWMCycle) % PWM_RESOLUTION;

    // calculate next "current PWM cycle" value
    currentPWMCycle = (nextPWMCycle)%PWM_RESOLUTION;

    // fire the next interrupt when the next motor switch must occur
}



void updateMotionVectorHandler(struct message_type *handler, uint8_t *buffer) {

    struct motion_data_type {
        uint8_t surge;
        uint8_t sway;
        uint8_t heave;
        uint8_t roll;
        uint8_t yaw;
        uint8_t pitch;
    };
    struct motion_data_type *motion_data = (struct motion_data_type*) buffer;


    const int INVERTED = -1;
    const int NORMAL   = 1;

    motorsDrivenByVectors(
		&motorConfiguration->pitch_bow.speed, 
		&motorConfiguration->pitch_stern.speed,
    motion_data->pitch, 
		INVERTED, 
		NORMAL, 
		motion_data->heave, 
		NORMAL, 
		NORMAL);

    motorsDrivenByVectors(&motorConfiguration->yaw_port.speed, &motorConfiguration->yaw_starboard.speed, 
        motion_data->yaw, NORMAL, INVERTED, motion_data->surge, NORMAL, NORMAL);

    motorsDrivenByVectors(&motorConfiguration->roll_top.speed, &motorConfiguration->roll_bottom.speed, 
        motion_data->roll, INVERTED, INVERTED, motion_data->sway, INVERTED, NORMAL);


    struct MotorConfiguration *motors = (struct MotorConfiguration*) motorDrivers;

    // accessing the data through struct instead of byte array:

}


void motorsDrivenByVectors(volatile int8_t *motor1, volatile int8_t *motor2, 
        int8_t vector1, int8_t vector1motor1modifier, 
        int8_t vector1motor2modifier, int8_t vector2, 
        int8_t vector2motor1modifier, int8_t vector2motor2modifier) {

    signed char motor1values[2], absValues[2], motor2values[2],
    larger;
    int motor1base, motor2base, motor1modifier, motor2modifier, motor1value, 
    motor2value,motor1_half_modifier,motor2_half_modifier, signDiffMotor1, 
    signDiffMotor2;
    
    // Calculate effective motor 1 vectors with modifiers
    motor1values[0] = vector1 * vector1motor1modifier;
    motor1values[1] = vector2 * vector2motor1modifier;

    // Calculate effective motor 2 vectors with modifiers    
    motor2values[0] = vector1 * vector1motor2modifier;
    motor2values[1] = vector2 * vector2motor2modifier;
    
    // get absolute values of motor values.
    absValues[0] = abs(motor1values[0]);
    absValues[1] = abs(motor1values[1]);

    // get the absolute larger vector
    larger   = (absValues[1] > absValues[0]) ? 1 : 0;
    
    // motor 1 base is the larger vector of the two
    motor1base     = motor1values[larger];
    // motor 1 modifier is the smaller of the two vectors
    motor1modifier = motor1values[!larger];
    // motor 2 base is the larger vector of the two
    motor2base     = motor2values[larger];
    // motor 2 modifier is the smaller of the two vectors
    motor2modifier = motor2values[!larger];
    
    // Calculate the sign difference (multiplier). The sign difference
    // will be used to move overflow out of one motor and into another.
    // This calculation is 100% magic and has no sensible logic -- Michael
    if(larger) {
        signDiffMotor2 = vector1motor1modifier == vector1motor2modifier ? 1 : -1;
        signDiffMotor1 = vector2motor1modifier == vector2motor2modifier ? 1 : -1;
    } else {
        signDiffMotor1 =  vector1motor1modifier == vector1motor2modifier ? 1 : -1;
        signDiffMotor2 =  vector2motor1modifier == vector2motor2modifier ? 1 : -1;
    }

    signDiffMotor1 *= vector1motor2modifier == vector2motor2modifier ? 1 : -1;
    signDiffMotor2 *= vector1motor1modifier == vector2motor1modifier ? 1 : -1;
    
    // The motors begin at the base value.
    motor1value = motor1base;
    motor2value = motor2base;

    // Calculate half of the modifier value. This is used because
    // we modify half on one motor, half on the other.
    motor1_half_modifier = motor1modifier/2;
    motor2_half_modifier = motor2modifier/2;   
    // Add the modifiers
    motor1value += motor1_half_modifier;
    motor2value += motor2_half_modifier;
    
    // When a value overflows past 100, move the overflow to the other motor.
    if(motor1value > 100) {
        motor2value += signDiffMotor2 * (motor1value - 100);
        motor1value = 100;
    } else if(motor1value < -100) {
        motor2value += signDiffMotor2 * (motor1value + 100);
        motor1value = -100;
    }
    if(motor2value > 100) {
        motor1value += signDiffMotor1 * (motor2value - 100);
        motor2value = 100;
    } else if(motor2value < -100) {
        motor1value += signDiffMotor1 * (motor2value + 100);
        motor2value = -100;
    }
    *motor1 = motor1value;
    *motor2 = motor2value;
}

