---
layout: post
title:  "Week #5 - Weekly Report 3"
date:   2015-02-20 00:00:00
categories: weekly
---

This is our third weekly report of the semester

#Brent Scheneman

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

---

#Steven Le
