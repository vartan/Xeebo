---
layout: post
title:  "Week #10- Weekly Report 7"
date:   2015-03-27 00:00:00
categories: weekly
---

This is our seventh weekly report of the semester

#Brent Scheneman

##Thruster Driver Boards

This week I finished the thruster driver boards and sent them to OSHPark to get fabricated. We ordered 9 boards which give us three extra just in case something happens to the other 6. These were re-designed to be modular due to several reasons. If a driver goes out, we can easily replace the specific driver that failed instead of replacing the entire thruster controller board that had 6 drivers on it. This drastically reduces the cost and difficulty of debugging an issue. They have multiple main power inputs/outputs which allow us to daisy change the power across all drivers. We should have them back from the fab house by April 6 with the expedited process. Below are the board renderings and what the finished boards are expected to look like.

###Thruster Driver Board Rendering - TOP
![Thruster Driver Board Rendering - TOP](/images/ThrusterBoardRenderingTop.png)

###Thruster Driver Board Rendering - BOTTOM
![Thruster Driver Board Rendering - BOTTOM](/images/ThrusterBoardRenderingBottom.png)

---

#Michael Vartan

This week I primarily worked on fixing up the thruster controls. Unfortunately, working with the lpc11 development board has been a nightmare, as shown in my previous senior project reports; it is from LPCXpresso and the LPCXpresso software uses eclipse, which I'm not a fan of. There were some debugging issues that I was not able to work out, so I moved up to keil µVision. At first I tried running it through Keil on my mac, but Keil lacks software debugging support for the LPC11u24, and the hardware drivers do not work through WINE. Next, I tried running it through a virtual machine on my mac, but there was another issue of getting the debugger working on the copy of windows that I had. Finally, I pulled my old windows laptop away from my work and started chugging away.

I had three goals this week to meet:
1. Getting to the bottom of the missed-timing-interrupt
2. Converting the software to Brent's new motor driver design, using PWM/Direction instead of PWM and enable. 
3. Getting the clock speed to run at 48MHz instead of 12MHz

## Missed Timer 
I was able to get to the bottom of the missed-timing-interrupt, I am able to get over it by forcing the processor to check for timer overrun after each interrupt is handled. I'm not entirely clear what is causing the timer to be overrun before the interrupt handler exists. The interrupt handler seemingly shouldn't take that long, and I've tried stopping/starting the interrupt timer in the middle of the handler and I was still getting the overrun problem. In the end, although I'm not sure what caused the issue, I was able to solve it.

## New PWM Design 

The old board design was supposed to have two pins: PWM and enable. The PWM channel would be slower as it approached 50%, 100% would be full speed forwards direction, and 0% would be full speed backwards direction. We decided to change the motor controls to match the motor controllers on our first submarine, Xeebo.

This new (old) design dictates that the PWM channel now maps directly to speed. The lowest PWM duty cycle (0%) maps to off, and the highest PWM duty cycle (100%) matches to full power. 

I have made the changes in the motor driver code to match this configuration. It has not been tested, but it can be seen below:
<script src="https://gist.github.com/vartan/757383b16002378da006.js"></script>

<script src="https://gist.github.com/vartan/fd13810118796413b725.js"></script>

## Getting the clock speed to run at 48MHz instead of 12MHz
I was having trouble getting this to work on LPCXpresso because the clock settings on the LPC11u24 are so finnicky and the documentation is complicated. If you make a mistake in programming this, you effectively brick the chip until you reset it by hand by putting it in ISP mode. By setting the clock sources correctly and the PLL correctly, I was able to get the clock to run at 48MHz.

All of the changes I made this week, I have not been able to test with an oscilloscope. I am planning on spending all of my spring break free time working on this software to get it perfect.

---

#Sam Jacobs

### Frame Construction

This week I worked with the team to fabircate the parts for the frame. On thrusday I assembled the frame from the parts that the team worked on creating.
![sam10_5](/images/sam10_5.png)
![sam10_6](/images/sam10_6.png)

###Next Steps 
The next step is to mount the thrusters. We are going to asses the necessety to protect the thrusters. We are going to determine if we are going to modify the frame such that the thrusters can be mounted to the inner part of the frame or if we are going to design a protective cover or cage to surround the motor.

![sam10_1](/images/sam10_1.png)

The craft will be weighed out of the water and the volume of it will be calcuatled so we can determine the ideal weight of the payload in order to achieve netural bouyancy.
![sam10_7](/images/sam10_7.png)
![sam10_4](/images/sam10_4.png)

After the frame is in a comleted state I am going to transition to work on the electronics design for either test equipment for the various sensors we will have on the craft so we can have working subsystems to detect ranges and distances, listen for the pingers that will be placed around the competition area, etc.

![sam10_3](/images/sam10_3.png)
 
---

#Steven Le

##Circuit Issue Resolved
The mbed was not turning on last week due to a short in the system.  When utilizing a LM7805 linear regulator to output +5V on the rail (used as an external power supply), the voltage readings is verified with common reference ground.  However, when applying both circuits to that rail, the voltage drops to 0.16 volts.  After isolating both circuits, the culprit is from the MSGEQ7 circuit where there was erronous wiring leading to ground.  This was fixed and the circuit is now functional in hardware.  

##Power Regulation
The linear voltage regulator will not be used for the circuit for the following reasons:
1. The AnalogIn for the mbed takes 3.3V for ADC.
2. The optimal voltage for best performance on the MSGEQ7 is 5V (Typical: 3-5.5V).
3. Power supply for the microphone circuit is 1.5V with 1-10V for operating voltage range.

Current goal is to take a 3.3V power to all circuits (current prototype will receive from mbed and final project will receive from power distribution board) with a boost regulator to 5V for the MSGEQ7 for best performance.

##Signal Tests
![Raw Audio](/images/am_rx_rawAudio.png)
This is the audio signal coming out of the microphone circuit.

![Filtered Audio](/images/am_rx_filteredAudio.png)
This is the audio signal coming out of the MSGEQ7 before going into the mbed ADC AnalogIn pin.

##Current Issues
When strobing the multiplexor to grab data from each frequency range in software, the output on the terminal reads constant values of 40-43.  When put under an oscilloscope, sporatic readings are introduced.
Current debug solution will be to use the Analog Discovery to send a 1kHz/2.5kHz signal into the input of the MSGEQ7 and see if it can be analyzed and read.  In addition to output numbers on Tera Term emulator, a test circuit will be utilized with LEDs for visual representation (dimming of LEDS between frequency ranges).

##Next Step
Board design on the receive circuit will be drafted on DipTrace with all components from schematic.
Successful resolution to frequency generation to the circuit for data manipulation.
Boost converter to MSGEQ7 implementation with revised schematic to the board design.
The goal is to have a functional design before the next presentation.