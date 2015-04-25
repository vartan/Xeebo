---
layout: post
title:  "Week #12- Weekly Report 9"
date:   2015-04-24 00:00:00
categories: weekly
---

This is our last weekly report (#9) of the semester

#Brent Scheneman

##Thruster Drivers
The thruster drivers were assembled and secured to Zeebo's main electronics plate that is made out of 1/8" aluminum plate that I cut on a band saw. Once all the drivers were secured, I wired them up for power as well as for control. 
<br>
![Thruster Driver Mounting](/images/MountingDrivers.PNG)
<br>
![Zeebo Electronics Plate](/images/ElectronicsPlate.PNG)
<br>
![Zeebo Electronics Plate Installed](/images/ElectronicsPlateInstalled.PNG)

##IMU Board
I designed the Inertial Measurement Unit (IMU) board and sent it off to get fabricated as well as the stencil that will make applying the solder paste during assembly much easier. We have received the boards, stencils, and parts for the IMU boards so those will be assembled this weekend and will be installed and tested in Zeebo next week.
<br>
![IMU Board](/images/IMUBoard.PNG)

#Michael Vartan 


#Sam Jacobs

###First Autonomous Test of Zeebo
We have celebrated a major milestone in the development of our project. On Monday 4/20/2015 we conducted the first autonomous test of Zeebo traversing under its own command.
![Zeebo in pool...GO BEACH!](/images/sam_week_12_pool.png)

Zeebo was programmed to drive forward for 10 seconds, wait 10 seconds, then drive in reverse for 10 seconds. The pattern was set to repeat 5 times.

My contribution to the success of this test was the mechanical design and assembly of the frame.

### Zeebo on Display
![Me and Zeebo](/images/sam_week_12_robot.png)
The two major design requirements  of the frame were such that Zeebo would be
1. Neurally Buoyant
2. Fully maneuverable (Yaw/Pitch, Ascend/Descend, Forward/Reverse, Rotate, and Roll)

### Ready for Deployment
![Completely Assembled Water Ready](/images/sam_week_12_robot_assembled.png)
We have enjoyed continued success with the design from the mechanical and waterproofing standpoint. Our gasket has not allowed any water seepage at depths from 0 to 5 feet which we have tested.

## Structural Issues That were Revised
After our first test, it was found that the way in which the frame articulated with the hull prevented easy access to the electronics payload and contributed to a high level of difficulty in removing the front cover.
![Front View of Zeebo](/images/sam_week_12_robot_front.png)

## Pre Test Troubleshooting
I refined the design and purchased new parts and reassembled the mountain components. The cover can be removed in a fraction of the time it took previously.

### Isometric 3D  Drawing
![Iso](/images/sam_week_12_CAD_iso.png)

I assisted Brent and Michael in debugging the electronics and software.

I provided my support and  input  to Brent in troubleshooting the inverter issue and I assisted Michael in debugging the UART ISR problem, which Michael eventually solved.

The team assisted me in the final checks and maintenance in the structure before we deployed.

## Next Steps
Brent has helped me source an actuator that I will use in the design of the torpedo launching system. 

### Actuator
CAT# SOL-143
![Actuator Pic](/images/sam_week_12_actuator.png)
MAGNETIC LATCHING SOLENOID, 33VDC

MSA (Magnet Schultz of America). 33 Vdc 17 ohm D-Frame, magnetic latching solenoid. Intermittent-duty. Built-in permanent magnet holds the plunger in fully-retracted position until it is manually (or mechanically) extracted. Plunger is equipped with a U-shaped pin that can be used for pull-type operation. Spring and clip keep plunger away from magnet when not energized. 42 x 40 x 36mm (1.65 x 1.55 x 1.40"). Two 6.5" leads terminate to 2-pin Molex-type socket. Plunger is 0.50" diameter x 2.01" long.




#Steven Le

##Boards

Both boards have been sent out to fabrication through OSH Park with Super Swift expedited shipping.  Turn around time will be 5 business days expected Friday, May 1st.  Hardware implementation is complete with continuous software revisions to function as expected.
![Receive Board - TOP](/images/am_rx_board2.png)
![Transmit Board - TOP](/images/am_tx_board2.png)

##Final Steps
Complete the transmit end algorithm to send data through the speaker.
Analyze the received signal via mic, distinguish the desired frequencies and convert to digital representation with UART response for verification.