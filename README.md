## First make changes in the LEDController.ino file before you upload it to your ESP32

1. change the number of LEDs according to how many your matrix or strip has in the LEDController.ino file (lines 13 and 16)
2. choose which type of LED you have(RGB versus RGBW)in the LEDController.ino (lines 24 and 25)
3. assign the ESP32 a IP or comment out lines 19 to 21 and 46 if you want to use DHCP in the LEDController.ino
4. set the SSID and your network password in line 53 of the LEDController.ino

## Then make changes in the touchdesigner project

5. set your ESP32 IP in the OSC out1 module as Network Address
6. set the number of rows your LED matrix has in the numPixels1 module constants, or the squareroot of the number of LEDs your strip has

The speed of UDP messages is controlled by the LFO module(frequency) 

Enjoy.
