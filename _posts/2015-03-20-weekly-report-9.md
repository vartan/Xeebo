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
This week I primarily helped Sam and Matt work on the structure again. 

Matt has been building a backup PVC frame just in case the aluminum one won't 
work out in the end, and I've been supporting him with that. The mounting 
method for the PVC frame is by using a long bolt through the flange/cover and 
then through the PVC. This is an absolutely stable way to mount the frame, 
however it makes it a little more difficult to work inside of the robot.

Once again Sam documented this much better than I ever could and I would just
be repeating his report. We did a waterproofing test with Zeebo and found that
it unfortunately did leak. We are suspecting that that the leak was from the rubber gasket, we are looking to get a silicone gasket instead. I am hoping that it is from our seal and not from the weld.

When it was in the water, we found that it was barely sinking after we weighed it down. After the test, we brought it to the school gym to weigh it, and found it to be exactly 50lb. This means that our weight calculations were accurate.

<div id="iframehere"></div>
<script>
//workaround because github/jekyll won't let me put an 
//iframe directly into the html.
    document.getElementById("iframehere").innerHTML = "<iframe width='100%' height='600px' frameborder='0' src='https://docs.google.com/spreadsheets/d/1r5tAl0xX0g0Y5hXtF5OFBNnbssQBHQ7P4RdQyiwTomY/edit?usp=sharing&single=true&gid=0&output=html'>test</iframe>";
</script>



---

#Sam Jacobs
Worked with Matt and Michael to assemble the housing. We conducted another live test in the pool to check the integrity of the seals on the housing.
![week8_1](/images/week8_1.png)
The results of the test showed leaks forming and water accumulating at a rate of approximately 1 cup per minute at a depth of 10 feet.

We weighed the hull, fully sealed, with an acrylic front cover and aluminum back cover, 12 bolts of 1/2 diameter and 2-3 inch length, and a payload consisting of approximately 20 lbs of water and weighed in the entire craft at 50 lbs. 
![week8_2](/images/week8_2.png)
At 50lbs in freshwater, the hull sank to the bottom of the pool. It was tied to a cord and I was able to lift it up from the pool floor using only my index finger and thumb. I estimate that it was 5 lbs too heavy in its state.

The team is going to buy a spring scale to make testing and honing in on the ideal neutral buoyancy more feasible during actual testing.
![week8_3](/images/week8_3.png)
I revised the structure from last week’s test to design in the fixes that the team and I deliberated on. I reduced the overall amount of 80/20 material used by 24”. We used 8 feet or 64” of 80/20 in the previous design, and have reduced the overall amount of 80/20 used by 25%. 

I have used a significantly less amount of hardware (which is what adds up to contribute to a lot of weight) on the new design.
![week8_4](/images/week8_4.png)
I have designed it to be symmetrical across the x-axis, the y-axis, and the z-axis, independently.

I have in mind a method for attaching the hull to the frame that will significantly reduce weight. 

The focus of my next week’s work will be to design in the attachment system that I have been developing and planning. 
![week8_5](/images/week8_5.png)
We will conduct another test using the newly designed structure and determine the maximum weight of the payload. 

After that, I will send the pieces to Brent to be drilled using his professional industrial fabrication systems that he has and the motors will be mounted to the frame.

Following the motor attachment, there will be 2 major designs:
![week8_6](/images/week8_6.png)

1. The inner frame that mounts the payload electronics to the hull. We will need to develop requirements for that to design to. Some initial requirements may include the ability to transfer heat from the boards to the interior of the hull and to design it as lightweight as possible.

2. The  through-hole connector array afixed to the acriylic faceplate.
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