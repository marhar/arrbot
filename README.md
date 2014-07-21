arrbot
======

Software related to the arrbot project


Utilities
---------

arrterm -- wrapper for terminal-based tty connection to arduino board

ServoCalibrate -- find and save the center point of your servo

ServoTester -- test servos

Drivers
-------

(as in making the robot drive around, not device drivers)

treadtester -- first test for tread motion, just moves to and fro.

Setup
-----

For ServoCalibrate and ServoTester:

servo ground (black or brown): arduino GND
servo power (red):  arduino RAW
servo signal (white or yellow): arduino pin 9

For TreadTester:  left servo on 9, right servo on 10.

experiment stuff
----------------
- mpu6050 is at i2c address 0x68
