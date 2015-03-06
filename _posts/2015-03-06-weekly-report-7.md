---
layout: post
title:  "Week #7 - Weekly Report 4"
date:   2015-02-20 00:00:00
categories: weekly
---

This is our fourth weekly report of the semester

#Brent Scheneman

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
Luckily, for the aluminum pieces we have, I was able to find an online calculator which calculated the weight of each of our pieces easily.

**Aluminum hull: **

![aluminum hull](/images/weight_hull.png)

**Aluminum flanges (combined weight)**
![aluminum flanges](/images/weight_flange.png)

**Aluminum cover**
![aluminum cover](/images/weight_cover.png)


##Calculating Displacement
I was able to calculate approximate displacement of our AUV by 
finding the volume of its parts and multiplying that by the density
of water.

I found the volume of the main hull by calculating its shape as a cylinder. I also calculated volume of the flanges and covers by treating them as cylinders as well. 

In order to find the volume of the structure, I took the weight of the 80/20 we are expected to use, and divided it by the density of the aluminum (6105 alloy). 

In total, we are very close to neutral buoyancy of Zeebo. Before adding our PCB hardware, 80/20 connectors, and wiring, we are just over 3lbs buoyant. I project that we will have to add floats slightly to keep Zeebo neutrally buoyant.
---

#Sam Jacobs

---

#Steven Le





