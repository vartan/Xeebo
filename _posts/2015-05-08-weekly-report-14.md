---
layout: post
title:  "Week #14- Weekly Report 11"
date:   2015-05-08 00:00:00
categories: weekly
---

This is my continuing weekly report (#11) of the semester

#Steven Le

##May 4, 2015

###Received Board Designs
Boards came in.  I made note for next iteration 2.0 to include LEDS for debugging purposes and changing the widths of the pins for debug on the receive board since the header pins used for the mic aren't the same.  Also for the transmit board, the button pattern was intended for a surface mount pushbutton, not the through-hole like the components I have.  It's a simple fix to solder on the top of the board instead of the back.

![Board Front](/images/am_board1.0_front.jpg)
![Board Back](/images/am_board1.0_back.jpg)

##May 7, 2015

###Software Implementation
After soldering the parts on the receive board, testing commenced.  A timer was used in software in addition to implementing a start bit to start data transmission.

![Board Soldered](/images/am_board1.0_soldered.jpg)

A 11 second 4-bit signal was sent with a ~16.5% error rate with noise interference.  More revisions will be done.

![Software implementation](/images/am_rx1.0_test.png)

###Timing Delays
Every time a serial display to the UART is used, ~22ms is delayed in the program.  I noticed by removing a 4 iteration for-loop, the total timer of the program is reduced by ~89ms (From 11389 ms to 11300 ms).
At 4800 baud rate, my time is at 11425 ms.
At 9600 baud rate, my time is at 11300 ms.
At 14400 baud rate, my time is at 11252 ms.

When the frequency is undetermined, a 'N' symbol is displayed.  On next iteration, I would like to add a parity correction bit to change the original data signal received.

![Unknown Bit](/images/am_rx1.0_test_N.png)