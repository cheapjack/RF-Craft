#!/usr/bin/python

# Uncomment if running hello world for Cloudmaker
#from mcpi import minecraft
#import server
import serial

#mc = minecraft.Minecraft.create(server.address)
########################################
# Mac: list your serial ports in Terminal 
# $ ls /dev
# It should show something like this /dev/tty.SLAB_USBtoUART', 9600
# So therefore define your serial object like this
# ser = serial.Serial('/dev/tty.SLAB_USBtoUART', 9600)
##################
# Raspberry Pi Mode
# $ ls /dev
# It should show something like this /dev/tty.AMA0
# So therefore define your serial object like this
# You may need to release the serial port with raspi-config
# $ sudo raspi-config
# ser = serial.Serial('/dev/ttyAMA0', 9600)

ser = serial.Serial('/dev/tty.SLAB_USBtoUART', 9600)

serialstring = ser.readline()
first = serialstring[0]
second = serialstring[1]
third = serialstring[2]

while True:
	if len(serialstring) > 1:
	# Uncomment if running hello world for Cloudmaker
	#mc.postToChat("Hello CloudMaker World this is Serial " + str(ser.readline()))
		print "First ", first
	else:
		print ser.readline()

ser.close
