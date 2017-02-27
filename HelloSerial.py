#!/bin/python

import serial

#disable serial from instructions in Setup-RPi-Hat.md
#if using with RPi 2 or earlier with pre 2016 Raspbian Jessie
#ser = serial.Serial('/dev/ttyAMA0', 9600)
#if using a UART serial adaptor on Unix/Mac
#ser = serial.Serial('/dev/tty.SLAB_USBtoUART', 9600)
#if using RPi 3 with Raspbian Jessie 2016 and onwards releases follow instructions to disable serial and enable UART from instructions in Setup-RPi-Hat.md
ser = serial.Serial('/dev/ttyS0', 9600)


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
