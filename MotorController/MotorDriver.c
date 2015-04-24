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
    // motor 0: surge
    {.directionPort = 0, .directionPin = 21, .pwmPort = 0, .pwmPin = 22, .speed = 0}, 
    // motor 1: sway
    {.directionPort = 0, .directionPin = 3,  .pwmPort = 0, .pwmPin = 4,  .speed = 0},
    // motor 2: heave
    {.directionPort = 0, .directionPin = 5,  .pwmPort = 0, .pwmPin = 6,  .speed = 0},
    // motor 3: roll
    {.directionPort = 0, .directionPin = 8,  .pwmPort = 0, .pwmPin = 7,  .speed = 0},
    // motor 4: yaw
    {.directionPort = 0, .directionPin = 9,  .pwmPort = 0, .pwmPin = 16, .speed = 0},
    // motor 5: pitch
    {.directionPort = 0, .directionPin = 17, .pwmPort = 0, .pwmPin = 20, .speed = 0},
};


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


/**
 * Update Motion Vector Handler
 * @param handler Pointer to MotionVector info being handled
 * @param buffer  Pointer to message.
 */
void updateMotionVectorHandler(struct message_type *handler, uint8_t *buffer) {

    struct motion_data {
        uint8_t surge;
        uint8_t sway;
        uint8_t heave;
        uint8_t roll;
        uint8_t yaw;
        uint8_t pitch;
    };
    struct MotorConfiguration {
        struct MotorDriver surge;
        struct MotorDriver sway;
        struct MotorDriver heave;
        struct MotorDriver roll;
        struct MotorDriver yaw;
        struct MotorDriver pitch;
    };

    struct MotorConfiguration *motors = (struct MotorConfiguration*) motorDrivers;

    // convert buffer to test_message
    struct motion_data *message = (struct motion_data*) buffer;
        
    motors->surge.speed = message->surge;
    motors->sway.speed  = message->sway;
    motors->heave.speed = message->heave;
    motors->roll.speed  = message->roll;
    motors->yaw.speed   = message->yaw;
    motors->pitch.speed = message->pitch;

    // accessing the data through struct instead of byte array:
        

}

