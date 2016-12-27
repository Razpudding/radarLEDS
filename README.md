# radarLEDS
My first hardware project: a NodeMCU playing Radar Love by Golden Earring and flashing lights along to the song.

How to use:
If you want to recreate this build, you'll need:
* a piezo for the sound
* a physical button to detect user input
* a LDR to detect light in the room
* a multi color LEDstrip
* a board (I used the nodeMCU)

How it works:
The physical setup combined with the code in this repo will make a device that waits until a button is pressed. When done so, the LEDstrip displays how much light is in the room. Once most of the lights in the room are turned off, the LDRs output will trigger a script that turns the piezo on and off repeatedly, causing the intro and chorus to be played three times while the LEDs flash.

Why I made this:
I wanted to eperiment with hardware, specifically the nodeMCU. As this was my first hardware project, there were a lot of lessons to be learned. As the holidays were coming up, I decided to build a truck for my dad that is "solar powered". Charge it in the light, then turn off all the lights in the room and watch the show.
I had some help from a friend who is a musician, he figured out whcih notes were in the song and how long they last. From there on out it was mostly tweaking the script and building the physical setup.
All in all I spent about 4 whole days making this.

The project is probably up to the conventions of the hardware scene as I;m not familiar with those, but if you want me to explain anything, just let me know.

![image of the finished product](https://razpudding.github.io/img/finished_project.jpg)
