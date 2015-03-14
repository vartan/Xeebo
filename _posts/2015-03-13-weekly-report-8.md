---
layout: post
title:  "Week #8 - Weekly Report 5"
date:   2015-03-13 00:00:00
categories: weekly
---

This is our fifth weekly report of the semester

#Brent Scheneman

##JTAG Adapter Cable
I started off the week by making the JTAG adapter cable which will allow us to program the LPCXpresso board using a stand alone JTAG programmer like Segger's J-Link device. The adapter converts the 2x10 pin connector configuration on the J-Link to the 1x8 pin header on the LPCXpresso.

###J-Link Connector
![J-Link Connector](/images/JLinkPinOut.png)

###LPCXpresso Connector
![LPCXpresso Connector](/images/LPCXpressoProgPin.png)

###JTAG Adapter
![JTAG Adapter](/images/JTAG_Adapter.png)


##Thruster Driver Control Board
This week I focused on finishing up the board layout for the thruster driver control board so it can be sent out for fabrication this coming Sunday (March 15). Most of the work was reconfiguring the MOSFET H-Bridge layouts to better utilize board space. 

###H-Bridge Revised
![H-Bridge Revised](/images/RevisedThrusterOutputs.png)

After revising the board, I opted to change out the IC we are using for the drivers. Instead we will be using a VNH5019A-E from ST Electronics. The reason for this is because it will cut down on board space because its a single chip compared to 6 chips which we are currently using, which will reduce the cost to get the board fabricated. Second, the control needed is less complicated than our current control scheme. This chip has built in H-Bridges and current sensor.

###VNH5019A-E
![VNH5019A-E](/images/VNH5019A-E.png)

##Main Computer Power Board
After completing the main computer power board and calculating the total cost to produce, I discovered that a store boughten power module that outputs 19V @ 4A was cheaper. I place an order for one and it will be here next Monday (March 16). This will also cut down on the time it would take to get a working board. If this was custom produced, it would take a minimum of a week (1 week for FAB and a few hours to assemble).

###Main Computer Power Board
![Main Computer Power Board](/images/MainComputerPowerBoard.png)


---

#Michael Vartan

---

#Sam Jacobs

##Week's Summary
This week I went from design to construction to test of the structure. 
###Sam and Matt Transporting Zeebo
![Sam and Matt Transporting Zeebo](/images/samAndMatt.png)
###Design - Monday/Tuesday
![Design - Monday/Tuesday](/images/zeebo_connectors.png)
###Construction - Tuesday/Wednesday
![Construction - Tuesday/Wednesday](/images/const1.png)
###Assembled Frame - Thursday
![Assembled Frame - Thursday](/images/built1.png)
###Test - Thursday
![Float Test](/images/floatingZeebo.png)
##The findings:
The weight of the structure is low enough such that we have the potential to achieve netural buoyancy.

The calculations for neutral buoyancy were incorrect as the volume of the motors were not factored into the original calculations. On Thursday night we put the structure sans the motors and electronic equipment into the pool and it floated. After the approx 10 lbs of motors and equipment are added to the craft it will approach slight negative buoyancy. 

However, the structure was designed with a large apparatus on the bottom that was to articulate with the yaw/pitch/ascend/descend thrusters and the payload. This caused the craft to tent to upright itself. This would have been ideal if we wanted to have a robot that stayed upright.

However since we are designing the UUV to be completely maneuverable in all directions the structure must be symmetrical.

The structure is going to be reimplemented with a symmetrical design with fewer materials. 

The savings in weight are going to be calculated and included in the next report, and a mathematical analysis of the structure will be done in order to calculate the the neutral buoyancy volume/weight point do design and refine to.
##Monday
80/20 material was transferred to ME team to be cut for a design I was to make this week. The requirement was to have exact measurements to be cut by the ME team once and only once.
Structure
![Structure](/images/zeeboStructure.png)
Connectors Used in Structure
![Connectors Used](/images/zeebo_connectors.png)
Itemized Lengths of Pieces of Frame
![Itemized Lengths of Pieces of Frame](/images/80_20_Lengths_Catalog.png)


##Tuesday
Design and Fabrication
![Design and Fabrication](/images/fab1.png)
Designed the structure with exact measurements and placement of brackets.
Design and Fabrication
![Design and Fabrication](/images/fab2.png)
Went to ME team to get the pieces cut.
Design and Fabrication
![Design and Fabrication](/images/fab3.png)
Worked with Steven and Michael to begin assembly of the frame.
Construction
![Construction](/images/const1.png)

##Wednesday
Continued to work on the frame.
Construction
![Construction](/images/const2.png)
Construction
![Construction](/images/const3.png)
Construction
![Construction](/images/const4.png)
##Thursday
Completed the frame. Attached the clear covers to the flanged with Matt.
Assembled Frame
![Assembled Frame](/images/built2.png)
Assembled Frame
![Assembled Frame](/images/built3.png)

Tested the frame by submerging it in the pool. The next task is to redesign and reconstruct a symmetrical frame and reduce the weight of the craft by 2-5 pounds.
Float Test
![Float Test](/images/floatingZeebo2.png)
Post Test Dihydrogen Monoxide Ballast Purge
![Leak](/images/leak.png)

---

#Steven Le

##Frame
Assisted Sam and Michael with building the frame for the housing after parts have been machined and delivered to specifications from the ME team.  Testing has been done as shown above from other members.  Delivery time was on schedule with satisfactory results.
![Build](/images/work1.jpg)
![Build](/images/work2.jpg)
![Build](/images/work3.jpg)

##mbed to MATLAB
I solved the error when transmitting data from the mbed uC to MATLAB.  Tera Term which is the software emulator used to output data cannot be used in the COM port when MATLAB is accessing the COM to retrieve the data.
![Data Retrieval](/images/am_MATLAB_test.png)
With this, I can analyze and manipulate the values to visual see data representation between binary, decimal, and correlate the information.

##MSGEQ7 Graphic Equalizer Display Filter
![MSGEQ7](/images/am_msgeq7_block.png)
Recommended by Matthew, this IC is a CMOS chip that can divide the audio spectrum into seven bands: 
63Hz
160Hz
400Hz
1kHz
2.5kHz
6.25kHz
16kHz
In a nuthshell, they're 7 built-in bandpass filters.  An audio signal can be sent through it and see an audio spectrum analyzer.  They are peak detected and muxed to the output to give DC representation of amplitude of each band.  It operates between 2.7-5.5 volts (5 volts best performance) and utilizes an anti-alias filter.  5 of these components have been ordered with expected delivery no later than Monday, May 16th.  This in the hardware domain can prove useful in frequency detection, filtering out undesired noise and range boundaries.  It will be utilized in the receive circuit with the electret microphone.
For convenience, there is a MSGEQ7 Library API that will be utilized in coding the software aspect since this IC is normally used in Spectrum Analyzation in LCD displays.
For reference:
http://developer.mbed.org/users/chrisisthefish/code/MSGEQ7/
While the components are enroute, software is be written.

##Schematic Revision
In the revised schematic with the MSGEQ7, the AUD input of the electret microphone circuit will feed into pin 5 of the IC (Signal 'In').  The remaining pins will include capacitors and a resistor for the clk (Pin 8) with credit to Chris Wilson and the datashseet in the mbed forums: http://developer.mbed.org/users/chrisisthefish/notebook/mbed-audio-spectrum-analyzer/
![Typical Wiring](/images/am_msgeq7.png)
![Strobe Timing Diagram](/images/am_strobe.png)
The strobe input will be controlled by the mbed which will be clocked to retrieve the 7 frequencies sequentially.  Each output of the frequencies will be saved into an array for later processing.