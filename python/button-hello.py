
#from mcpi import minecraft
#import server
import serial

#mc = minecraft.Minecraft.create(server.address)

ser = serial.Serial('/dev/tty.SLAB_USBtoUART', 9600)
serialstring = ser.readline()
first = serialstring[0]
second = serialstring[1]
third = serialstring[2]

while True:
	if len(serialstring) > 1:
	#	mc.postToChat("Hello CloudMaker this is Serial " + str(ser.readline()))
		print "First ", first
	else:
		print ser.readline()

ser.close
