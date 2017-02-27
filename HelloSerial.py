#!/bin/python

import serial

ser = serial.Serial('/dev/ttyAMA0', 9600)


# assign your button id strings
button1_received = "1,1\r\n"
button2_received = "2,1\r\n"
button3_received = "3,1\r\n"
button4_received = "4,1\r\n"
button5_received = "5,1\r\n"


while True:
    serialcommand = str(ser.readline())
    if serialcommand == button1_received:
        print "Got mail from Button 1"
        sleep(1)
