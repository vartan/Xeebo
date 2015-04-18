---
layout: post
title:  "Week #11- Weekly Report 8"
date:   2015-04-17 00:00:00
categories: weekly
---

This is our eigth weekly report of the semester

#Brent Scheneman

##Thruster Driver Boards

This week I finished the thruster driver boards and sent them to OSHPark to get fabricated. We ordered 9 boards which give us three extra just in case something happens to the other 6. These were re-designed to be modular due to several reasons. If a driver goes out, we can easily replace the specific driver that failed instead of replacing the entire thruster controller board that had 6 drivers on it. This drastically reduces the cost and difficulty of debugging an issue. They have multiple main power inputs/outputs which allow us to daisy change the power across all drivers. We should have them back from the fab house by April 6 with the expedited process. Below are the board renderings and what the finished boards are expected to look like.

###Thruster Driver Board Rendering - TOP
![Thruster Driver Board Rendering - TOP](/images/ThrusterBoardRenderingTop.png)

###Thruster Driver Board Rendering - BOTTOM
![Thruster Driver Board Rendering - BOTTOM](/images/ThrusterBoardRenderingBottom.png)

---

#Michael Vartan 

Much has happened in the last few weeks! I am really excited to share all of the progress

##Missing timer interrupts
The missing timer interrupts issue turns out to be the strangest issue I have ever encountered. Sam and I were able to solve it: there were two very strange issues that were both happening simultaneously. 

1. There is a bit in the LPC11u24 timer settings called MR0R. This bit dictates that when the timer matches the match register, the timer counter will be reset. Somehow, sometimes the timer counter would NOT be reset by the match event. This was solved by manually setting TC=0 at the beginning of the interrupt routine. *Who knows?*
2. When I was testing, I turned off compiler optimizations because it makes debugging the code easier. Once we fixed the timer using the above technique, I turned compiler optimizations back on. Guess what? *It stopped working again!!* Somehow, an evil compiler bug caused the interrupt handler to break as well. 

When you have a hardware bug and a compiler bug in one function, clearly the deck is stacked against you. Luckily we were able to figure it out.

##Serial Communication on Zeebo-Brain "Server"
From now on, I am going to call the linux computer inside of the submarine the "Server". I decided to install NodeJS on the server because it is relatively quick, but more importantly the language is event-driven. I want the robot to be built from the ground up around the concept of events. Using events through NodeJS means that the process will efficiently use all of its resources yet never "spin" waiting for information. 

Potentially the most critical event on the server is peripheral communication. That is why I put a huge amount of effort into making an actual nodejs package for serial communication. This package creates a quick, intuitive interface to both asynchronous and synchronous handling of fixed-length messages. You can see a table of our current message specifications below for a better understanding of what a fixed-length-message entails.

<div id="iframehere"></div>
<script>
//workaround because github/jekyll won't let me put an 
//iframe directly into the html.
    document.getElementById("iframehere").innerHTML = "<iframe width='100%' height='600px' frameborder='0' src='https://docs.google.com/spreadsheets/d/1TP0-Qkuk-7ZXS9RNS5TpPRJ_JgtWoxkv3e7dtqB7E4Y/edit?usp=sharing&single=true&gid=0&output=html'>You must enable iframes, silly</iframe>";
</script>

The most important part of this interface is that it handles both **synchronous** and **asynchronous** message handling. What does this mean? Let's use `request motion vector` as an example. 

* Asynchronous handling

  - It would be favorable to have a knowledge at all times of what the robot is doing. Therefore, I may have a function called `updateMotionVectors` which will receive the serial data which contains the motion information, and then update the server's variable to reflect this change. This would look something like:

<script src="https://gist.github.com/vartan/045555ca743e48d6c711.js"></script>


* Synchronous handling:
 - On the other hand, we may want to specifically request the motion data and then do something with it. For example, when I want to turn the robot 90°, I will send the `NEW_MOTION` command. Then, I would like to receive a motion vector from the lpc11u24 and check it against the motion data I sent out. This would look something like:
 - 
<script src="https://gist.github.com/vartan/17435e9cf32bd90d8cac.js"></script>

The message handling package that I wrote can be seen on [github.com/vartan/serialmessages](https://github.com/vartan/serialmessages) with better documentation. It can also be installed througn the npm package manager with the command `bash npm install serialmessages`. My favorite part of creating this was being able to install the package that I created on a different machine, and watching it work!

##Serial Communication on LPC11u24
I did not forget about our little microcontroller, or neglect it. I made a pretty slick way of handling communication on it as well. I have not tested it on the microcontroller, but I've tested it on my computer and compiled it as well, so hopefully it'll just work when it's on the board. All in all, this code is about 174 lines, it can be seen on our github page [here](https://github.com/vartan/Xeebo/tree/master/messageHandler_c).

I was concerned about handling serial messages over the UART because if the handler takes too long, it may overflow the UART buffer. Therefore, I decided instead to create a queue of messages on the heap and handle them in a FCFS fashion. 

The struct for an individual message handler looks as follows:


When the first byte of a message comes in over UART, space gets allocated in the heap for a buffer of size receiveLength. Then, each byte gets put into the buffer until it is filled. Then, this buffer and message are both sent on the message queue, to be handled in main by the following code:

<script src="https://gist.github.com/vartan/690cec1e53bc4b104688.js"></script>

Receive handlers also have their own syntactic sugar. Notice below, there is a struct called test_message_response. I create a pointer of test_message_response, and point it to the first byte in the buffer. This then becomes an alias for `uint8_t buffer`, with explicit naming. This can also be used to send raw integers and other datatypes bytwise over serial, and receive them as their native type on the handler side (as long as endianness is preserved). If I sent a 4 byte integer from the server, it would be received as 4 individual bytes on the lpc. However, if I replaced `uint8_t packet1` with `int integerPacket`, `integerPacket` would now be the original int sent over from the client. Wild!

<script src="https://gist.github.com/vartan/a51c6a4c6c3969952539.js"></script>

##Server Reinstall
Unfortunately, there was a kernel issue when upgrading the operating system, so I had to reinstall the server from scratch. Due to lack of time, I installed ubuntu server on the server instead of Arch Linux. 

Then, I installed autossh and created a daemon which will detect when Zeebo is connected to the school's wifi, and automatically create an ssh tunnel, forwarding port 22 to a raspberry pi in my apartment. This allows me to ssh into the robot from anywhere, despite the closed network at CSULB.


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