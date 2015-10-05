
import serial


ser = serial.Serial('/dev/tty.SLAB_USBtoUART', 9600)
while True:
	print ser.readline()
