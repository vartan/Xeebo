---
layout: post
title:  "Week #3 - Weekly Report 1"
date:   2015-02-06 00:00:00
categories: weekly
---

This is our first weekly report of the semester

#Brent Scheneman

##LPC11U24 Breakout Board
![BreakoutBrd](/images/zeebo_breakoutBrd.jpg)

To help with the developement of the firmware for the thruster driver/control board, we decided to designa  breakout board for the LPC11U24 microcontroller. This will speed up the thruster driver/control board development because while the physical aspects of the thruster driver/control board is being designed, the firmware can be developed and tested in parallel. After a schematic and a preliminary board layout was finished, Team Zeebo decided to purchase a pre-made breakout board (LPXCpresso LPC11U24). This has saved both time and money.

![LPCXpresso](/images/zeebo_lpcxpresso.jpg)

##Thruster Driver/Control Board

The first stages of designing the thruster driver board has begun. Currently it is in the schematic phase. So far all the component layouts and schematic symbols have been created. The schematic and board layout has been completed for the H-Bridges, which include four N-Channel MOSFETs. The next step is to add the Full-Bridge MOSFET Driver (A3940) and LPC11U24 to the design. 

---

#Michael Vartan
![Computer](/images/zeebo_computer.jpg)

##Main Computer

###Setting up

We took our size requirements very seriously, and bought/put together a small computer with a small SSD, which we found meets our specs

###Operating System

Next, we decided that Arch Linux fit our needs for Zeebo because it is a very bare bones and quick operating system. On the other hand, this bare bones operating system is installed entirely manually, which requires much more work than most operating systems.
  
###We used the following resources to install Arch Linux:

* [Linux Veda](http://www.linuxveda.com/2014/06/07/arch-linux-tutorial/)
* [Archlinux Wiki](https://wiki.archlinux.org/index.php/installation_guide#Connect_to_the_Internet)
* [WikiHow](http://www.wikihow.com/Install-Arch-Linux)



##Installing OpenCV

Once the operating system was installed, we began installing dependencies for our control system. We decided to install Python and Node for scripting languages. 
Next we installed the dependencies for OpenCV. The following dependencies were installed:

    intel-tbb, ilmbase, openexr, xcb-proto, xproto, libxdmcp, libxau, libxcb, 
    kbproto, libx11, xextproto, libxext, videoproto, libxv, libxvmc, alsa-lib, 
    libpng, graphite, harfbuzz, freetype2, fontconfig, gsm, lame, fribidi, 
    recode, enca, libass, libvdpau, libxml2, libbluray, libmodplug, 
    libasyncns, inputproto, libxi, recordproto, fixesproto, libxfixes, 
    libxtst, libice, libsm, libogg, flac, libvorbis, libsndfile, json-c, 
    libpulse, libtheora, libpciaccess, libdrm, wayland, xf86vidmodeproto, 
    libxxf86vm, damageproto, libxdamage, libxshmfence, elfutils, libomxil-
    bellagio, libtxc_dxtn, llvm-libs, mesa, mesa-libgl, libva, libvpx, opencore
    -amr, openjpeg, opus, rtmpdump, orc, schroedinger, renderproto, 
    libxrender, sdl, speex, libjpeg-turbo, v4l-utils, libx264, xvidcore, x265, 
    ffmpeg, xineramaproto, libxinerama, xine-lib, libraw1394, libdc1394, atk, 
    libdatrie, libthai, pixman, cairo, libxft, pango, libxcursor, randrproto, 
    libxrandr, compositeproto, libxcomposite, shared-mime-info, libtiff, 
    libdaemon, avahi, libcups, jasper, gdk-pixbuf2, hicolor-icon-theme, gtk-
    update-icon-cache, gtk2, glu, libxt, libxmu, pangox-compat, gtkglext, 
    opencv


We ran into an issue with python versioning, which required us to make a symlink between python2 to ~/.bin/python.  

Lastly, we installed the “opencv” package via NPM in order to use openCV with NodeJS.

##Testing
![OpenCV Test - Live Webcam](/images/michael_circle.png)

###OpenCV

We began testing OpenCV via the example program packaged in NPM, which uses face detection to detect Mona Lisa’s face, and then draws a circle over it. 
 
###Camera

Once the camera arrived, we performed the same test with the live camera feed. We benchmarked that our computer could perform face detection on over 10 frames per second. We anticipate that face detection is more resource intensive than finding simple shapes and colors, so we will have no problem with being able to react quick enough for our missions. 


---



#Sam Jacobs
##Main Structure Housing Acquisition
The main housing was ordered from metals depot.
#![T3R10250](/images/tube.jpg)

Part: T3R10250  
Description 10 OD x .250 wall x 9.50 ID 6061 Aluminum Round Tube

##Design of Bulkeads for Main Housing
I have been designing aluminum flanges that will be welded to the main housing. 12 inch diamater acrylic disks will be secured to the flanges with a rubber gasket sitting between them. The layered-materials will be held together with 6 1/2 inch bolts.

##Conceptual Design: Bulkhead Integration with Housing
#![bulkheadDesign](/images/bulkheadDesign.jpg)

##Projectile Launcher
###Concept
The AUVSI RoboSub committie requires that the projectile launcher be non lethal and that the projeciles it launches not reach a velocity in air great enough such that they would cause harm to anyone that they impact. In short, the projectile launcher must be very low performance.

###Projectile Launcher Feature
The launcher will be 3/4inch PVC with 1/2inch inner diamaeter. One end (the breach) will be capped and have an attachment point such that it sill afix to the main structure of the Zeebo UUV. The breach will have a spring that will compress when the missile is loaded. The muzzle end will be open to the water, and the missile will exit the muzzle end of the launcher when fired.

####Launcher Apparatus
At a length in the launcher the length of the missile there will be an aparatus that will be controlled with an electormechanical device, either a stepper motor with a lever, a high tourque servo motor (cheapest) attached to a rotating cylinder, or a linear actuator (expensive). When the electromechanical device is actived it will cause the apparatus to unobstruct the blocking component that is holding the missile in the launcher, causing the spring to expand and the missile to achieve a linear velocity and exit the launcher. 

####Missiles(Torpedos) 
The missiles will be made of Pipe 1/2 inch in diamater 6 inches long with stabalizing fins and a nose-cone. The pipe will be made out af a lightweight material and will be small enough in diamater that it will be able to freely slide out of the launcher while still being held in place by the launcher.


---

#Steven Le

##Procurement of Parts

Parts from Digikey and Digilent have come in to complete the list of components for this project:
    8-ohm, 3-watt speaker (100Hz-20kHz frequency range)
    Electret Condenser Microphone (omnidirectional 20Hz-20kHz)
    Various ranges of resistors, capacitors, transistors
    Jumper wires
    Pushbuttons
    Breadboard
    LM741 Operational Amplifiers
    mbed LPC1768 Microcontroller

###Additional Notes
An additional microcontroller is purchased with an expected lead time of a week to save time and separating the circuits for receive and transmit.  It proved time consuming to testing circuits using one uC.

##Debugging Tools & Software
I will be utilizing the Analog Discovery from Digilent which will supplement in troubleshooting throughout the project using oscilloscope features and measuring capabilities on provided software Digilent WaveForms.

##Concept
In designing the acoustic modem, the approached method is binary frequency-shift keying.
http://en.wikipedia.org/wiki/Frequency-shift_keying#Audio_FSK
This modulation method (BFSK) will be using a pair of frequencies for data transmission through series of 0s and 1s (binary).

"1" = mark frequency
"0" = space frequency

An example from wikipedia is shown below:
[img]http://en.wikipedia.org/wiki/Frequency-shift_keying#mediaviewer/File:Fsk.svg[/img]

In regards to demodulating a BFSK signal, I'm researching into utilizing the "Goertzel algorithm" on the microcontroller as a more efficient method to perform tone detection with less CPU power than utilizing the Fast Fourier Transform (FFT).
(Resource: http://www.embedded.com/design/configurable-systems/4024443/The-Goertzel-Algorithm)

##Application

##Flowchart
#![Receive Flowchart](/images/am_flowchart.png)