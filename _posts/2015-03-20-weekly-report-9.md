---
layout: post
title:  "Week #9- Weekly Report 6"
date:   2015-03-20 00:00:00
categories: weekly
---

This is our sixth weekly report of the semester

#Brent Scheneman

##Thruster Controller Board

This week I focused on re-designing the thruster controller board. The schematic for the old H-Bridge drivers was complete and the board layout was nearly complete. It was decided to change the driver chip that we are using to reduce board space and complexity, which ultimately reduces the risk of system failures and board manufacturing costs. With the new driver, there will be 5 less IC's on the board per thruster. So this week I created new part board layouts for the new compoenents, including the new driver. I completely redesigned the schematic to work with the new drivers and made quite a bit of progress on the board layout. As seen in the pictures below, the board layouts for the individual drivers are designed. Next thing to do will be connecting the microcontroller to the drivers. With the new redesigned board, I made all traces that carry current to the motors wider to allow for higher current draw all while reducing the overall footprint of each driver compared to the original design.

###Thruster Driver Board Top Level Schematic
![Thruster Driver Board Top Level Schematic](/images/ThrusterBoard_TopLevelSch.png)

###Thruster Driver Board Driver Schematic
![Thruster Driver Board Driver Schematic](/images/ThrusterBoard_DriverSch.png)

###Thruster Driver Board Layout
![Thruster Driver Board Layout](/images/ThrusterBoard_TopLevelBrd.png)

###Thruster Driver Array Layout
![Thruster Driver Board Layout](/images/ThrusterBoard_DriverArrayBrd.png)

###Thruster Driver Layout
![Thruster Driver Board Layout](/images/ThrusterBoard_DriverBrd.png)

<br>

##Main Computer Power Board

Last week we recieved the power board for the Main Computer. This coming week I'll conduct a few tests to see if the board will do what we need it to (low noise, proper voltage output, etc.) before proceding forward in actually powerin the computer.

---

#Michael Vartan

---

#Sam Jacobs

---

#Steven Le

![Modified Circuit](/images/am_schematic_rx_v2.png)

##Revised Circuit with MSGEQ7
This week was dedicated to writing software to test the MSGEQ7 and displaying the filtered frequencies in conjunction with the electret microphone circuit.  I decided to switch from Vout (+3.3V) to VU (+5V out from the mbed USB power supplied from laptop) to power the electret microphone and the MSGEQ7 since the datasheet stated +5V gave the best performance.  After plugging in the mbed via USB, the mbed would not turn on with both loads from the microphone circuit and MSGEQ7.  The current draw is still under specifications which lead to a possible maximum dissipation issue with the mbed on the regulator.  As a solution, a 9V battery source will be utilized with a linear voltage regulator LM7805 to output +5V supplied to the microphone and MSGEQ7 with a common reference ground.  I had the same issue with an old project when a power supply was powering a microcontroller and several motors (additonal loads) exceeding the current draw.  The expected result would be 2 separate power supplies to the mbed and to the remaining circuits.  This cannot be verified until Saturday morning when I arrive back to town from my business trip.

Once verified and is powered on, software code can be uploaded to verify strobing in an audio spectrum with frequency ranges desired.

       Pinout:
               MSGEQ7             mbed LPC1768    Electret Mic                   
               VDDA   (Pin 1) --> VU (+5V) <----- VCC                            
               VSSA   (Pin 2) --> GND      <----- GND                            
     (*Analog) out    (Pin 3) --> p15                                            
               strobe (Pin 4) <-- p14                                            
               in     (Pin 5)              <----- AUD                            
               GND    (Pin 6) --> GND                                            
               reset  (Pin 7) <-- p13                                            
               ckin   (Pin 8) --> VU (+5V)                                       
                                                                                 

#include "mbed.h"
#include "MSGEQ7.h"

#define MAX 500

Serial pc(USBTX, USBRX);    // tx, rx

MSGEQ7 eq(p13, p14, p15);   // reset, strobe, analog

int main() {
    int i = 0;
    while(1) {
        eq.readInt(MAX); // Read in frequency data, mapped to a max number

        for(i = 0; i < 7; i++) {
            pc.printf("%d\t", eq.freqDataInt[i]);
        } // end for-loop
        pc.printf("\n");
    } // end while-loop
} // end main

This code will sample the data reading in and can be used for manipulation.