---
layout: post
title:  "Week #10- Weekly Report 7"
date:   2015-03-27 00:00:00
categories: weekly
---

This is our seventh weekly report of the semester

#Brent Scheneman

---

#Michael Vartan

---

#Sam Jacobs

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