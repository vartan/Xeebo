---
layout: post
title:  "Week #5 - Weekly Report 3"
date:   2015-02-20 00:00:00
categories: weekly
---

This is our third weekly report of the semester

#Brent Scheneman
Due to the problems we are having with debugging the LPCXpresso board, it was discussed that we will try an alternative to the LPC Link debugger for our debugging needs. We will begin to use Segger's J-Link JTAG device which has been proven to work in the past. To solve the logistical aspect of actually connecting the J-Link to the target board, I'm going to make an adapter that goes from the 2x10 pin rectangular connector of the J-Link to an 8 pin straight pin header on the target board.

I made progress on the thruster driver board. I created the driver subsystems that include a Full-Bridge N-Channel MOSFET Driver, a MOSFET H-Bridge, and a current sensor. Six of these together create the top level system of the thruster driver board itself, along with the LPC 11u24 microcontroller. The last step before the final board layout can be completed is the additon of decoupling capacitors throughout the board. These will ensure all electronic components are receiving clean power.

Once the thruster driver is completed, the next board to be designed will the be the power management board. This will be responsible for converting the 22.1V from the batteries to 19V, 5V, and 3.3V for all electronic sub-systems. 

###Thruster Driver Sub-System
![SubSystem](/images/ThrusterDriverSubAssy.png)

###Thruster Driver Top Level
![TopLevel](/images/ThrusterDriverTopLevel.png)

---

#Michael Vartan
I have run into a very strange issue with the LPCXpresso board I am using, that has been giving me headaches all week.

For some odd reason, the timer counter sometimes runs past the match register. At first, I was concerned that perhaps my interrupt timing generator was too timing intensive and was taking longer than it took for match to be reached. However, I have tried decreasing the frequency of interrupts, as well as disabling the counter while the interrupt is being handled, and still the timer overruns about 8% of the time. 

I am concerned that perhaps there is a higher priority interrupt that is occurring from the debugger that may be taking control of the processor when the PWM should be happening. In order to debug this, I need to acquire a different debugger which I should have done by the next week.

In the meantime, I've been working on getting the PLL on the clock working. Where Keil gives you a function called set_pll, LPCXpresso seems to require that it be done manually. Unfortunately, if you misconfigure the clock, the debugger stops working until you perform a series of connections which reset the chip. After hours of trial and error, I got the PLL set with the following code from eewiki:

<script src="https://gist.github.com/vartan/c702672c2bc576ce34b7.js"></script>

Using this code, I successfully multiplied the clock to 50MHz.

![50MHz clock](/images/50mhz.png)

---


#Sam Jacobs

##Structure Update

###Status: Nearing End of Design Phase... About to start build phase

##Team Stratagey Regarding Structure
Per our team meeting Monday, Feb 16, 2015: 

Our team has made the decision to move forward and build the robot of which the design origitinated from within this team in parallel to the effort being undertaken by the M.E. team. 

Our team's strategy, philosophy and motivation is to move at an accellerated pace in order to complete the project and particiapte in the 2015 RoboSub competition.

Thus, after taking acount of the work I did last semester for the design of the structre, I cereated a new design that we will discuss and refine monday Feb 23.

Once the design is finalized by our team, construction of the frame will begin. 

The strcuture is absolutely critical to the development of this project. Major testing of the AI system controlling the motors and interfacing with the sensor suite inside of a functioning unit will be possilbe once the structure is complete and the electronics are inside of it.


##Structure Requirements

### Requirements

1. The structure must allow for the placement of all 6 motors such that full range of moment (yaw, pitch, heave, roll, thrust, rotation) is possilbe using vectored thrusting.
2. The strucutre shall be comprised of materials that we already have on hand
3. The structure must be designed such that heat dissipation will be efficient
4. The structure be designed such that the weight of the payload combined with the weight of the structure itself offset the positive bouynace from the volume of the air inside the electronics housing itself
5. The structure must be designed such that the payload can be readily accessable.
6. The completed craft must be within the weight and size requirements established in the RoboSub 2015 Competition Rules

## The Design

### Specifications

Max Width: 	2'""
Max Heigh: 	2'0"
Max Lenght: 2'0"

Electronics Housing Length: 		12"
Electronics Housing inner Diamater: 9.75"

Estimated Weight: 40 lbs


Zeebo's structure will be built around the 10" OD aluminum tube that we will cut to 1 foot in length. We will integrate the flange, gasket, and clear cover design in order to create a waterproof access point and to seal the main housing.

The exoskeleton will be designed around modularity using 8020 Aluminum Tubing. 

The Camera will be placed inside of the housing and point forwards. The thrusters that control pitch and heave will not block the view of the camera. The camera will be completely unobstructed.

The exoskeleton will hold the center electronics housing in place with braces as well as protect the thrusters from damage should the craft suffer a collision.

###Isometric Projection
![ZEEBO_STRUCTURE_PHOTO_1](/images/ZEEBO_STRUCTURE_PHOTO_1.png)

###Rear View Showing Thruster Placement in Xeebo Pattern
![ZEEBO_DESIGN_1_BACKSIDE](/images/ZEEBO_DESIGN_1_BACKSIDE.png)

###Bottom View
![ZEEBO_DESIGN_1_BOTTOM](/images/ZEEBO_DESIGN_1_BOTTOM.png)

###Front View
![ZEEBO_DESIGN_1_FRONT](/images/ZEEBO_DESIGN_1_FRONT.png)

###Side View
![ZEEBO_DESIGN_1_SIDE](/images/ZEEBO_DESIGN_1_SIDE.png)

### Top View
![ZEEBO_DESIGN_1_TOP](/images/ZEEBO_DESIGN_1_TOP.png)

### Camera Unobstructed by Vertical  Thrusters
![ZEEBO_DESIGN_FRONT_DETAIL](/images/ZEEBO_DESIGN_FRONT_DETAIL.png)

### Underside Detail where Claw will be Mounted
![ZEEBO_DESIGN_UNDERSIDE](/images/ZEEBO_DESIGN_UNDERSIDE.png)


---

#Steven Le

##Parts
The second mbed came in over the weekend.  I can now test the receive and transmit circuits independently from each other.

##Microphone Measurements
With the help of Matt Connolly, it was realized that microphone was working properly.  It was verified by changing the scale on Analog Discovery's Waveform software.

##Sampling Period and Sampling Frequency
![Sample Period](/images/am_sampleperiod.PNG)
It's fundamental to know the ranges and limitations of my mbed.  By using a GPIO toggle switch (pin 9), I was able to read into the ADC and find the sampling period to be 20 microseconds between.  This results in 1/20us = 50 kHz to be the sampling frequency in the best case with no code execution on the mbed besides reading the mic.  Nyquist sampling theorem states "the sampling frequency should be at least twice the highest frequency contained in the signal."

fs >= 2*fc,
where fs is the sampling frequency, and fc is the highest frequency contained in the signal.

##Approach To Acoustic Modem
Summary of this gentleman's response on stackoverflow.com regarding FFTs and Arduino (similar concepts)
(http://stackoverflow.com/questions/16843730/generate-fft-and-decode-on-arduino)

###Main Problem (Part 1):
Convert Audio Signal Into Stream of Numbers (1s and 0s)
1. Signal at right amplitude
2. Choosing sampling rate needed
3. Digitizing and storing data for later processing

1+3 are related since signal needs to be digitized before choosing right amplitude.
-Amplify the signal of microphone sound input before feeding into ADC with 5V input range since output may be in mV range.

####Choosing Sampling Rate
To detect a high frequency, I need to sample the signal "faster than it is changing".
Nyquist's Theorem = You have to sample at 2x the highest frequency THAT IS PRESENT in signal.
Sampling a high frequency signal with a low frequency sample clock results in "aliasing" with the output as something completely different from desired results.
Find frequencies of interest and remove all higher frequencies with a filter.
(*I've decided to use 2kHz and 10kHz for my mark and space frequencies)
Therefore, I would sample at 20kHz which is 20000 samples per second and store them in a location where I can pull and use the data.

###Problem 2:
Analyze the Signal
-Use FFT to analyze what frequencies were present in a signal and then do something with it.

##mbed Library for FFT
There are complex libraries that support FFT.  I'm going to have to source a library that can read data from the microphone and determine the frequency of the signals and return as an output to user.  It is ideal to have a frequency spectrum utilizing the data.

##Goal for the Week
1. Source FFT Library and implement with microphone circuit (receive) with results.
2. Develop drafted data transfer algorithm for the speaker circuit (transmit).
3. Draft a board layout for both circuits.