---
layout: post
title:  "Week #4 - Weekly Report 2"
date:   2015-02-13 00:00:00
categories: weekly
---

This is our second weekly report of the semester

#Brent Scheneman

---

#Michael Vartan

##µControllers

This week I began working on the LPC11u24, our microcontroller we will be using for the majority of our boards. Brent Scheneman chose the [LPC11u24 LPCXpresso Board](http://www.embeddedartists.com/products/lpcxpresso/lpc11U24_xpr.php) as our breakout board to begin development/testing while our other boards are being designed.

Unfortunately, this week I lack the hardware required to actually test the board, and don't have access to a windows computer to debug code using Keil. I have been building with the LPCXpresso software for mac, and will begin ASAP.

##Motor Drivers
I have been primarily working on starting the motor drivers. I have generated a struct which represents all of the information required to control the motors independent whatever else is going on in the processor. This can be seen in `MotorDriver.h` as shown below:

<script src="https://gist.github.com/vartan/387c45f51185bb266d43.js"></script>   
To avoid polluting the global namespace, I have decided to not have the motors declared as a global variable. Any part of the program which requires access to the motors must have a pointer to the motors passed to it from main. This can be seen in action in the current `main.c`:

<script src="https://gist.github.com/vartan/536645732eda5920834b.js"></script>

The motors are very straightforward to control in the code. See the example below.

<script src="https://gist.github.com/vartan/3f43cfe15a8703215b85.js"></script>

Next week I hope to have the PWM timing optimized to recalculate timer interrupt on the fly in order to reduce the amount of interrupts. This would reduce the interrupt count from `PWM_FREQUENCY * PWM_RESOLUTION` Hz (where PWM_RESOLUTION IS 200) to a maximum of `PWM_FREQUENCY * (MOTOR_COUNT * 2)` Hz.

All of the code for the MotorControllers can be seen (live) at 
[https://github.com/vartan/Xeebo/tree/master/MotorController](https://github.com/vartan/Xeebo/tree/master/MotorController). A snapshot of the code at the time of this post can be seen [here](https://github.com/vartan/Xeebo/tree/aa099bb59fe80b94c9b2bfb9b9bf18905909a856/MotorController).

---

#Sam Jacobs

---

#Steven Le
