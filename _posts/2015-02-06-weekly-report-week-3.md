---
layout: post
title:  "Week #3 - Weekly Report 1"
date:   2015-02-06 00:00:00
categories: weekly
---

This is our first weekly report of the semester

#Brent Scheneman
...

#Michael Vartan
##Main Computer
###Setting up
We took our size requirements very seriously, and bought/put together a small computer with a small SSD, which we found meets our specs

###Operating System
Next, we decided that Arch Linux fit our needs for Zeebo because it is a very bare bones and quick operating system. On the other hand, this bare bones operating system is installed entirely manually, which requires much more work than most operating systems.
  
###We used the following resources to install Arch Linux:

* http://www.linuxveda.com/2014/06/07/arch-linux-tutorial/
* https://wiki.archlinux.org/index.php/installation_guide#Connect_to_the_Internet
* http://www.wikihow.com/Install-Arch-Linux



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
###OpenCV
We began testing OpenCV via the example program packaged in NPM, which uses face detection to detect Mona Lisa’s face, and then draws a circle over it. 
 
###Camera
Once the camera arrived, we performed the same test with the live camera feed. We benchmarked that our computer could perform face detection on over 10 frames per second. We anticipate that face detection is more resource intensive than finding simple shapes and colors, so we will have no problem with being able to react quick enough for our missions. 




#Sam Jacobs
Yelling!!!!

#Steven Le
...
