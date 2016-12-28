#!/usr/bin/python
# Send messages to a CanaryMod server with RasperryJuice1.3 plugin

from mcpi import minecraft
from mcpi import block
from time import sleep
import serial


#mc = minecraft.Minecraft.create("127.0.0.1")
#mc = minecraft.Minecraft.create(server.address)
mc = minecraft.Minecraft.create()
# By default the server will be a local instance of the CanaryMod server
#########################
# PC/Mac/Linux  mode    #
# RF-Craft HAT receiver #
#########################
# use the default serial port, 'COM1', '/dev/ttyAMA0' this will change platform to platform '/dev/tty.usbserial-A400f5sm'
# You can list your serial ports in Terminal
# Open a terminal window from the menu bar
# $ ls /dev
# It should show something like this /dev/tty.SLAB_USBtoUART', 9600
# So therefore define your serial object like this
# Or use the serial id that shows up on the Arduino IDE
#ser = serial.Serial('/dev/ttyAMA0', 9600)
#ser = serial.Serial('COM1', 9600)
ser = serial.Serial('/dev/tty.usbserial-A400f5sm', 9600)
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

# CanaryMod and mcpi can't seem to agree on the coordinates of player positions and we've found you need to add -256 to x, add 64 to y and add -8 to z to make your coordinates match with the Minceraft client

#mc.postToChat("Hello World!")
mc.postToChat("Hello Workshop this is RF-Craft setting up")
# assign your button ids
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
    if serialcommand == button5_received:
        print "Got mail from Button 5"
        mc.postToChat("Got mail from Button 5 saying " + serialcommand)
        mc.entity.setTilePos(4, 76,20, -64)
        sleep(1)
        mc.camera.setFollow()
