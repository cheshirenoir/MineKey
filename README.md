# MineKey
A very silly project to build a "better" keyboard for Modded Minecraft.  

##Prerequisites:
You'll need to include the following libraries. They're availabe from the Arduino Library manager  
https://github.com/lostcaggy/rotary_caggy  
https://github.com/adafruit/Adafruit_BusIO  
https://github.com/adafruit/Adafruit-GFX-Library  
https://github.com/adafruit/Adafruit_SSD1306  
Use the Earlphilhower Raspberry Pi Pico board definition https://github.com/earlephilhower/arduino-pico  

##Installation:
Drag the UF2 file to your Pico and that should be it.  

##Compiling
You'll need to put the contents of the libraries folder in your local libraries folder. It contains a modified version of the original keyboard.h file.  

##Some thanks
Brendan and Michael for putting up with my stupid comments and fumblling.  
lostcaggy - This person deserves kudos! This is the first and only library I have found to handle rotary encoders on the Raspberry Pi Pico properly.  
Earlphilhowe - Your work allowed me to actually finish this project!  
johnwasser in the Arduino forums - Your keyboard mod worked to let me generate raw keys for all my keyboards  

##Latest HW differences
Revised schematic with better pin mappings and a spot for a 128x64 OLED rather than the 128x32 I used in the original proto board.  

##Current Key mappings:
I probably should move these to an external file that you can drag into the Pico, but I don't know how to do that. Someone else can add that functionality :-D  

No modifier implements a Numeric Keypad. Row by row, the keys are:  
> 7, 8, 9, /  
> 4, 5, 6, *  
> 1, 2, 3, -  
> 0, stop, return, +   

With the upper META key held down, you mostly get additional function keys. Row by row, the keys are:  
> F13, F14, F15, F16  
> F17, F18, F19, F20  
> F21, F22, F23, F24  
> KEY_OPEN, KEY_HELP, KEY_PROPS, KEY_FRONT  

With the lower SUPER key held down, you get multimedia keys. Row by row, the keys are:  
> KEY_MEDIA_PLAYPAUSE, KEY_MEDIA_STOPCD, KEY_MEDIA_PREVIOUSSONG, KEY_MEDIA_NEXTSONG  
> KEY_MEDIA_EJECTCD, KEY_MEDIA_WWW, KEY_MEDIA_BACK, KEY_MEDIA_FORWARD  
> KEY_MEDIA_STOP, KEY_MEDIA_FIND, KEY_MEDIA_SCROLLUP, KEY_MEDIA_SCROLLDOWN  
> KEY_MEDIA_EDIT, KEY_MEDIA_COFFEE, KEY_MEDIA_REFRESH, KEY_MEDIA_CALC  

With both SUPER and META held down gets you all sorts of random keys. Many probably won't work. Row by row, the keys are:  
> KEY_KPCOMMA, KEY_YEN, KEY_KATAKANAHIRAGANA, KEY_HENKAN  
> Keypad_A, Keypad_B, Keypad_C, Keypad_D  
> Keypad_E, Keypad_F, Keypad_00, Keypad_000  
> Keypad_XOR, Keypad_@, Keypad_+/-, Keypad_!  

CC-BY-SA
