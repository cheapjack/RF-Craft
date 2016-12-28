
import serial

##################
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
ser = serial.Serial('/dev/ttyAMA0', 9600)
#################
# The Button sends the serial message (node , action)
# node is the value in #define NODEID in Line 10 of the Arduino code in ~/RF-Craft/arduino/button/button.io It comes with the default node of 1 on the arduino HAT
# action: "1", "Button Pressed"
#	"2", "Error"
#	"3", "OK"

#ser = serial.Serial('/dev/tty.SLAB_USBtoUART', 9600)
while True:
	print ser.readline()
