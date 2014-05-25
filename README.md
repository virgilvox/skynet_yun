skynet_yun
==========

Skynet support for the Arduino Yun.

Before you can use this you have to first update the yun system image and install node using the instructions below.


INSTALL INSTRUCTIONS:

1. Update the Yun Openwrt image. http://arduino.cc/en/Tutorial/YunSysupgrade
2. Expand the Yun disk space to an sd card. http://arduino.cc/en/Tutorial/ExpandingYunDiskSpace
3. Run the following commands;

opkg update

opkg install node

opkg install node-serialport

opkg install node-socket.io-client

4. Comment out the last line in /etc/innittab and reboot.
5. You can't git clone on the yun, so instead use another computer to move this repo to the sd card.
5. Run node skynet_yun.js 
6. Once it connects and authenticates you can send it messages from skynet and it'll push it to the serial port.


Arduino Code:

Download and Install Libraries:
https://github.com/neophob/LPD6803-RGB-Pixels
https://code.google.com/p/arduino-timerone/downloads/list

Once you have the libraries installed, program the Arduino Yun with the yunLed code.
Send it a payload that contains just an integer of 0,1,2, or 3.

msg.payload = 0; ->  ColorWipe - Blue

msg.payload = 1; ->  ColorWipe - Green


msg.payload = 3; ->  KnightRider - Blue
