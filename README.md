# MineKey
##A very silly project to build a "better" keyboard for Modded Minecraft.

Prerequisites: The BIG one. I use a modded version of CaggyRotary by Martin Evans. You'll need to install it, then rename Rotary.cpp to CRotary.cpp, Rotary.h to CRotary.h,and update line 70 of CRotary.cpp to read #include "CRotary.h"
Clunky I know.
https://github.com/lostcaggy/rotary_caggy
This person deserves kudos! This is the first and only library I have found to handle rotary encoders on the Raspberry Pi Pico properly.

Use the Earlphilhower Raspberry Pi Pico board definition https://github.com/earlephilhower/arduino-pico

Revised schematic with better pin mappings and a spot for a 128x64 OLED rather than the 128x32 I used in the original proto board.
