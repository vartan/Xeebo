---
layout: post
title:  "Week #10- Weekly Report 7"
date:   2015-03-27 00:00:00
categories: weekly
---

This is our seventh weekly report of the semester

#Brent Scheneman

##Thruster Driver Boards

This week I finished the thruster driver boards and sent them to OSHPark to get fabricated. We order 9 boards which give us three extra just in case something happens. These were re-designed to be modular due to several reasons. If a driver goes out, we can easily replace the specific driver instead of replacing the entire thruster controller board that had 6 drivers on it. This drastically reduces the cost and difficulty of debugging an issue. They have multiple main power inputs/outputs which allow us to daisy change the power across all drivers. We should have them back from the fab house by April 6 with the expedited process. Below are the board renderings and what the finished board are expected to look like.

###Thruster Driver Board Rendering - TOP
![Thruster Driver Board Rendering - TOP](/images/ThrusterBoardRenderingTop.png)

###Thruster Driver Board Rendering - BOTTOM
![Thruster Driver Board Rendering - BOTTOM](/images/ThrusterBoardRenderingBottom.png)

---

#Michael Vartan

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
## 
---

#Steven Le

(DRAFT)

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

More to come.