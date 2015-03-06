---
layout: post
title:  "Week #7 - Weekly Report 4"
date:   2015-03-06 00:00:00
categories: weekly
---

This is our fourth weekly report of the semester

#Brent Scheneman

This week I concentrated on polishing up the schematic for the thruster driver board so that can be sent to get fabricated in the near future. I also focused on creating the schematic for the power board for the main computer. This board will be capable of outputing 19 V @ 4 A. This is done using a highly efficient (>90% efficiency) step-down switching regulator (LM22679) from Texas Instruments.


###Computer Power Board Schematic
![Computer Power Board](/images/computer_pwr_brd.png)

Before the schematic layout was started, I performed a few calculations to determine the correct supplement component values that are required for proper operation. These were dependent on the operating condition of the LM22679. Another circuit like this will be used to create a 5 V output as well. The set up is the same, the only difference will be the suppliment component values.

###Computer Power Board Calculations
![Inductor Calculation](/images/InductorCalculation.png)
<br>
<br>
![Volateg Divider Calculation](/images/VoltageDividerCalculation.png)

---

#Michael Vartan

This week I spent most of my efforts on Zeebo calculating water displacements in order to achieve neutral buoyancy. This involved two different things:

1. Calculate the weight of each of the components we can
2. Calculate the weight of the water displaced by the robot

 You can see my work in the spreadsheet below.

<div id="iframehere"></div>
<script>
//workaround because github/jekyll won't let me put an 
//iframe directly into the html.
    document.getElementById("iframehere").innerHTML = "<iframe width='100%' height='600px' frameborder='0' src='https://docs.google.com/spreadsheets/d/1r5tAl0xX0g0Y5hXtF5OFBNnbssQBHQ7P4RdQyiwTomY/edit?usp=sharing&single=true&gid=0&output=html'>test</iframe>";
</script>

##Calculating the weight of our components:
Some of our components we were able to pull weights off of datasheets. This included most of the electronic components, visible in rows 4-9. The rest of the items, however, had to be calculated.

###Aluminum Pieces
Luckily, for the aluminum pieces we have, I was able to find an online calculator which calculated the weight of each of our pieces easily. Below are the aluminum hull, flanges (both weights combined), and cover respectively.

![aluminum hull](/images/weight_hull.png) ![aluminum flanges](/images/weight_flange.png) ![aluminum cover](/images/weight_cover.png)


##Calculating Displacement
I was able to calculate approximate displacement of our AUV by 
finding the volume of its parts and multiplying that by the density
of water.

I found the volume of the main hull by calculating its shape as a cylinder. I also calculated volume of the flanges and covers by treating them as cylinders as well. 

In order to find the volume of the structure, I took the weight of the 80/20 we are expected to use, and divided it by the density of the aluminum (6105 alloy). 

In total, we are very close to neutral buoyancy of Zeebo. Before adding our PCB hardware, 80/20 connectors, and wiring, we are just over 3lbs buoyant. I project that we will have to add floats slightly to keep Zeebo neutrally buoyant.

---

#Sam Jacobs
## Refined Design 
I refined the design in order to shed weight. I redesigned the structure such that it would hug the central electronics tube instead of surround the craft in the form of an exoskeleton.

![New Zeebo](/images/RefinedZeebo.png)


I worked with Michael in the weight calculation effort by analyzing the design of the structure and extracting the total amount of 80/20 used in the design.

Thursday Mar 5 we procured parts from local suppliers. We obtained a solution for mounting the main electronics encolsure to the frame at Fergeson industrial supply in Signal Hill, Long Beach. I developed a way to mount the thrusters to the 80/20. The seabotix thrusters were supplied with #6 3/4" metal screws. We purchased #6 1 1/2" metal screws and will use a drill press to create 1/4" diamater holes in the 80/20 and secure the thrusters.

![pvc](/images/pvc1.png)

I constructed a 1:1 scale prototype out of PVC material. After creating the protoype, the other team members and I were able to have a common vision of how the robot will be built.


After finishing the building of the PVC protoype, I began custructing the 80/20 frame. I plan to have it completed in 2 weeks. 

![cutting](/images/week7_cutting.png)


I am propsing to use different hardware that is cheaper, stronger, less prone to rust, and more readily available. After reading what others have done to get around using the expensive proprietary 80/20 hardware that is described here: http://www.instructables.com/id/8020-Fastener-Alternatives/.



---

#Steven Le





