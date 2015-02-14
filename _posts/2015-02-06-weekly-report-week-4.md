---
layout: post
title:  "Week #4 - Weekly Report 2"
date:   2015-02-13 00:00:00
categories: weekly
---

This is our second weekly report of the semester

#Brent Scheneman

##LPC11U24 Breakout Board

![BreakoutBrd](/images/breakout_seperated.jpg)

As mentioned last week, we chose to go with the LPC11U24 microcontroller for all our microcontroller needs. We will be using it for our thruster driver board. The breakout board that was purchased is intended to be used with the LPCXpresso IDE, which turned out to be overly complicated. To use the breakout board with the Keil IDE, I desoldered the JTAG jumpers and cut the board in half to allow the U-Link Debugger to plug into the JTAG header on the breakout board.



##Thruster Driver Board

###Board Layout

![ThrusterDriver](/images/MotorDriver.PNG)

The schematic of the H-Bridges that I created last week have since been transfered into the board layout software. Six identical full H-Bridges have been laid out on the board. The next step is to place the LPC11U24 microcontroller onto the board along with the requisite power, communication, and crystal components.



###Concerns/Considerations

Throughout the board layout phase, constant consideration has to be given to control signal placement. When controlling large inductive loads, such as thrusters, large amounts of back-EMF is produced, which can induce unwanted voltage on control signals that are in close proximity to the H-Bridge outputs. All analog lines coming from the current sensors have to be placed far away from any H-Bridge output as well. 

After discussing the claw and torpedo shooter design with Sam, it is eveident that I will have to include addition load control hardware (MOSFETs) to provide additional control to the claw and torpedo shooter.

#ROBUST!!!

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
[our MotorController folder in github](https://github.com/vartan/Xeebo/tree/master/MotorController). A snapshot of the code at the time of this post can be seen [here](https://github.com/vartan/Xeebo/tree/aa099bb59fe80b94c9b2bfb9b9bf18905909a856/MotorController).

---

#Sam Jacobs
##Projectile Launcher Design

![overviewLauncher](/images/projectileSystemLoadedView.png)
This week I started the initial design for the projectile launcher. This design will serve as a jumping-off point and will be refined in the following reports. Construction will begin in 2 to 3 weeks, or when the design is finalized. The projectile launcher will fire a ABS Plastic torpedo at a velocity sufficient to propel it through the water at distances and speeds enough to achieve the goals in the RoboSub competition.

It will be activated with a single pin input. The main control system will interface with the launching system by asserting a signal high.

This will initlize the launch sequnce and the torpedo will fire.
# Launcher Control System
The projectile launcher control system will consist of a selenoid in a waterproof module. It will have an push against a shaft that will lock the projectile in place.

The selenoid along with its electronics will interace from a dry environment with the suberged environemnt with a rubber boot. On the submerged side, the shaft will lock the torpedo in place.

When the selenoid is activated, the arm will retract and the projectile will launch.

A manual safety lock will be installed that will block the torpedo once it is placed into the launcher.

The safety will be removed manually and the system will go into live mode. In live mode, the launcherwill fire the projectile when the selenoid is acvivated by the onboard computer.
![launchSystem](/images/projectileLaunchSystemOverview.png)

## Launch Sequence
### Step 1
![launchSystem](/images/Step 1.png)
### Step 2
![launchSystem](/images/Step 2.png)
### Step 3
![launchSystem](/images/Step 3.png)
### Step 4
![launchSystem](/images/Step 4.png)
### Step 5
![launchSystem](/images/Step 5.png)
### Step 6
![launchSystem](/images/Step 6.png)
### Step 7
![launchSystem](/images/Step 7.png)
### Step 8
![launchSystem](/images/Step 8.png)



---

#Steven Le
(Draft)

##Receive Circuit (Electret Microphone)

Receiving circuit has been tested.  Here is the updated block diagram:
[Placeholder for Photo]

Oscope readings measured in volts.
[Placeholder for Waveform]

###Additional Notes
Still waiting on second mbed microcontroller from SparkFun.  Expect latest mid next week.  In the mean time, 2 protoboards are utilized together to swap between circuits.  When the mbed comes in, testing will commence to communicate between circuits.

##JANUS
I've been looking into open source JANUS that utilizes a signaling protocol for underwater communications.  It is fairly new to me and am currently seeing if it would prove useful with a short learning curve.  MATLAB and C libraries are included.  More information and report next week.  The website can be seen here: http://januswiki.org/tiki-index.php
