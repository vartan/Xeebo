---
layout: post
title:  "Week #13- Weekly Report 10"
date:   2015-05-01 00:00:00
categories: weekly
---

This is my continuing weekly report (#10) of the semester

#Steven Le

##April 29, 2015

###Hardware Revisions
I've decided to change the capacitor (C4) to AUDIO IN on the MSGEQ7 to from 0.01uF to 0.1uF because SparkFun had an old datasheet from the Mixed Signal Integration back in 2004.  The revised schematic acquired is dated 2011.  This doesn't affect the board because it is just a change in capacitor value.

###Revised Schematic From Datasheet
![MSGEQ7 Revised Datasheet Schematic](/images/am_msgeq7ds.png)

###Board Revisions
I've made it cleaner on my schematic and pcb layout.  I do expect in the next iteration to utilize a 5.0V supply for the MSGEQ7 for better calibration since prototype is using 3.3V from the mbed LPC1768 to the rest of the components.  When sending out the board, it came out to a size of 2.51 x 2.51 inches which should have been minimized to 2.5 x 2.5 inches, reducing costs.  I will note that my next iteration will remove the mbed protoboard and have just the 40-pin LPC1768 chip with intention of reducing board size at the very least to 2 x 2 inches.

###Rx PCB Board Rendering - TOP
![Rx PCB Board Front Rendering](/images/am_rx_boardfront1.0.png)

###Rx PCB Board Rendering - BOTTOM
![Rx PCB Board Back Rendering](/images/am_rx_boardback1.0.png)

###Tx PCB Board Rendering - TOP
![Tx PCB Board Front Rendering](/images/am_tx_boardfront1.0.png)

###Tx PCB Board Rendering - BOTTOM
![Tx PCB Board Back Rendering](/images/am_tx_boardback1.0.png)

##April 30, 2015

###Working with Software
Since the MSGEQ7 detects peak frequencies, utilizing the timing diagram with the inputs STROBE and RESET are very important in analyzing.