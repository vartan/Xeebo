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



int main() {
    int i;
    int badLoopCount;
    //USE EXTERNAL CRYSTAL TO GENERATE INTERNAL SYSTEM CLOCK
    LPC_SYSCON->SYSAHBCLKDIV             = 0x1;       //set clock divider for core to 1
    LPC_SYSCON->MAINCLKSEL               &= ~(0x03);  //set “main clock” to IRC oscillator, if not system will lock up when PLL turns off!(sec. 3.5.11)
    LPC_SYSCON->MAINCLKUEN               &= ~(1);     //write a zero to the MAINCLKUEN register (sec. 3.5.12), necessary for MAINCLKSEL to update
    LPC_SYSCON->MAINCLKUEN               |= 1;        //write a one to the MAINCLKUEN register (sec. 3.5.12), necessary for MAINCLKSEL to update
    LPC_SYSCON->SYSPLLCLKSEL             = 0x01;      //connect system oscillator to SYSTEM PLL (sec. 3.5.9)
    LPC_SYSCON->SYSPLLCLKUEN             &= ~(1);     //write a zero to SYSPLLUEN register (sec. 3.5.10), necessary for SYSPLLCLKSEL to update
    LPC_SYSCON->SYSPLLCLKUEN             |= 1;        //write a one to SYSPLLUEN register (sec. 3.5.10), necessary for SYSPLLCLKSEL to update
    LPC_SYSCON->PDRUNCFG                 |= (1<<7);   //power down the PLL before changing divider values (sec 3.5.35)
    LPC_SYSCON->SYSPLLCTRL               = 0x23;      //set MSEL = 0x00011 and PSEL = 0x01 (sec 3.5.3 and table 46 of sec. 3.11.4.1)
    LPC_SYSCON->PDRUNCFG                 &= ~(1<<7);  //power up PLL after divider values changed (sec. 3.5.35)
    while((LPC_SYSCON->SYSPLLSTAT & 1) == 0);         //wait for PLL to lock
    LPC_SYSCON->MAINCLKSEL               = 0x03;      //set system oscillator to the output of the PLL (sec. 3.5.11)
    LPC_SYSCON->MAINCLKUEN               &= ~(1);     //write a zero to the MAINCLKUEN register (sec. 3.5.12), necessary for MAINCLKSEL to update
    LPC_SYSCON->MAINCLKUEN               |= 1;        //write a one to the MAINCLKUEN register (sec. 3.5.12)
    //CONNECT SYSTEM OSCILLATOR TO CLKOUT PIN: This allows measurement with o-scope.
    LPC_IOCON->PIO0_1        &= 0xFFFFFFF8;       //clear FUNC bits (sec. 7.4.4)
    LPC_IOCON->PIO0_1        |= 0x01;             //set FUNC bits to CLKOUT function (sec. 7.4.4)
    LPC_GPIO->DIR[0] |= 0x01;
    LPC_SYSCON->CLKOUTSEL = 0x3;               //sec. 3.5.21
    LPC_SYSCON->CLKOUTUEN    = 0;                 //"CLKOUTUEN" has to be toggled for "CLKOTUCLKSEL" to accept the value written to it
    LPC_SYSCON->CLKOUTUEN    = 1;                 //"CLKOUTUEN" has to be toggled for "CLKOTUCLKSEL" to accept the value written to it
    LPC_SYSCON->CLKOUTDIV    = 1;                 //set divider to 1 (sec. 3.5.23)
    badLoopCount = 0;


   	struct MotorDriver motors[MOTOR_COUNT];
	initMotorDrivers(motors);
    motors[0].speed = -75;
    motors[1].speed = -50;
    motors[2].speed = -25;
    motors[3].speed = 100;
    motors[4].speed = 50;
    motors[5].speed = 75;
	while(1) {
	    for(i=0;i<10000;i++) {
	        if(MOTOR_TIMER->TC > MOTOR_TIMER->MR[0]) {
	            badLoopCount++;
	            MOTOR_TIMER->TCR  = (1<<1);       // disable/reset timer
	            MOTOR_TIMER->TCR  = (1<<0);       // enable run	            initMotorTimers();
	        }
	    }

	    motors[3].speed = motors[3].speed + 1;
	    if(motors[3].speed>99)
	        motors[3].speed = -100;
	    // prevent overrun

	}
	return 0;
}
