arrbot
======

Software related to the arrbot project


Utilities
---------

arrterm -- wrapper for terminal-based tty connection to arduino board

servo_calibrate -- find the center point of your servo

servo_tester -- test servos


Setup
-----

For servo_calibrate and servo_tester:

servo ground (black or brown): arduino GND
servo power (red):  arduino RAW
servo signal (white or yellow): arduino pin 9

experiment stuff
----------------
- mpu6050 is at i2c address 0x68
