#!/usr/bin/python

#import mcpi.minecraft as minecraft
#import mcpi.block as block
from mcpi import minecraft
from mcpi import block
from time import sleep
import serial


#mc = minecraft.Minecraft.create("127.0.0.1")
#mc = minecraft.Minecraft.create(server.address)
mc = minecraft.Minecraft.create()

#########################
# Pi mode               #
# RF-Craft HAT receiver #
#########################
# For older RPi Raspbian images use the default serial port, '/dev/ttyAMA0'  after disabling the serial console this could change platform to platform
# Open a terminal window from the menu bar
# $ ls /dev/tty*
# It should show a list of tty1 etc ports or on a Mac/UNIX something like this /dev/tty.SLAB_USBtoUART
# disable serial from instructions in Setup-RPi-Hat.md
#if using with RPi 2 or earlier with pre 2016 Raspbian Jessie
#ser = serial.Serial('/dev/ttyAMA0', 9600)
#if using a UART serial adaptor on Unix/Mac
#ser = serial.Serial('/dev/tty.SLAB_USBtoUART', 9600)
#if using RPi 3 with Raspbian Jessie 2016 and onwards releases follow instructions to disable serial and enable UART from instructions in Setup-RPi-Hat.md

# So therefore define your serial object like this
ser = serial.Serial('/dev/ttyS0', 9600)
#ser = serial.Serial('/dev/ttyAMA0', 9600)
#ser = serial.Serial('/dev/tty.SLAB_USBtoUART', 9600)
#########################################################
# The Button sends the serial message (node , action)   #
# node is the value in #define NODEID in Line 10 of the #
# Arduino code                                          #
# in ~/RF-Craft/arduino/button/button.ino               #
# It comes with the default node of 1 on the arduino HAT#
#                                                       #
# action "1", "ButtonPressed"                           #
# action "2", "Error"                                   #
# action "3", "OK"                                      #
#                                                       #
#########################################################

#mc.postToChat("Hello World!")
mc.postToChat("Hello Workshop this is RF-Craft setting up")
# assign your button id strings
button1_received = "1,1\r\n"
button2_received = "2,1\r\n"
button3_received = "3,1\r\n"
button4_received = "4,1\r\n"
button5_received = "5,1\r\n"

#Find my entityId for the first spawned player
entityIds = mc.getPlayerEntityIds()
me = entityIds[0]
print me
myTilePos = mc.entity.getTilePos(me)
#Make the camera follow the player
mc.camera.setFollow(me)

while True:
    serialcommand = str(ser.readline())
    if serialcommand == button1_received:
        print "Got mail from Button 1"
        mc.postToChat("Got mail from Button 1 saying " + serialcommand)
        mc.entity.setTilePos(4, 76,20, -64)
        sleep(1)
        mc.camera.setFollow()
