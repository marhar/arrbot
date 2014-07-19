arrbot
======

Software related to the arrbot project


Utilities
---------

arrterm -- wrapper for terminal-based tty connection to arduino board

ServoCalibrate -- find and save the center point of your servo

ServoTester -- test servos


Setup
-----

For ServoCalibrate and ServoTester:

servo ground (black or brown): arduino GND
servo power (red):  arduino RAW
servo signal (white or yellow): arduino pin 9

experiment stuff
----------------
- mpu6050 is at i2c address 0x68
