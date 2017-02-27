# Setup RPi for use with HATS

You need to disable serial console on your Pi and enable UART with 
`sudo raspi-config`

Select Advanced Options/Serial and disable the serial login shell or Interface Options/Serial and disable the serial login shell but enable the hardware(UART)

If you are not receiving messages on your **receiver HAT** in **RPI mode** from your **RF-Craft HAT** in **EXT** transmitter mode with a NODE ID of 1 ie (1,1)

You may also have to follow the below [instructions](https://www.hackster.io/fvdbosch/uart-for-serial-console-or-hat-on-raspberry-pi-3-5be0c2) from [Frederick Vandenbosch](https://www.hackster.io/fvdbosch)

## Raspberry Pi 3 & Raspbian Jessie 2017

It seems the recently launched Raspberry Pi 3 behaves differently with regards to the UART interface on the GPIO header. In this guide I go through the steps I took to get the UART working for serial console or HAT communication.

I am assuming you are using a recent Raspbian Jessie image (2016-03-18 or more recent) on Raspberry Pi 3, that the file system has been expanded and that enough space is left for the software updates to be installed.

Let’s go!

### Update Software

The first thing you’ll probably need to do is to ensure all software components are up-to-date. Update the repository and upgrade the installed packages:

`pi@raspberrypi:~ $ sudo apt-get update && sudo apt-get upgrade -y`

Update the firmware:

`pi@raspberrypi:~ $ sudo rpi-update`

Reboot to apply the changes:

`pi@raspberrypi:~ $ sudo reboot`

### Enable UART

 A new property has been introduced to enable the UART on the Pi. This property will put the core frequency to a minimum, ensuring stability. It’s possible to put the core frequency to maximum as well, assuming the power supply is powerful enough and the Pi 3 is properly cooled (heatsink!).

 Enabling UART with minimum core frequency:

 `pi@raspberrypi:~ $ sudo nano /boot/config.txt`

```
# Enable UART
enable_uart=1
```

More information on this newly introduced property can be [found here](https://www.raspberrypi.org/forums/viewtopic.php?f=28&t=141195)

### Disable Console

To disable the console, edit the following file as follows:

 `pi@raspberrypi:~ $ sudo nano /boot/cmdline.txt`

```
#dwc_otg.lpm_enable=0 console=serial0,115200 console=tty1 root=/dev/mmcblk0p2 rootfstype=ext4 elevator=deadline fsck.repair=yes rootwait
dwc_otg.lpm_enable=0 console=tty1 root=/dev/mmcblk0p2 rootfstype=ext4 elevator=deadline fsck.repair=yes rootwait
```

Reboot to apply the change:

`pi@raspberrypi:~ $ sudo reboot`


### Testing

Verify it all works by using screen
Install it first if you dont have it; its handy!
`sudo apt-get install screen`

then listen on the `/dev/ttyS0` serial port at 9600 baudrate that your HAT communicates with.

`screen /dev/ttyS0 9600`

Power your other **RF-Craft HAT** in **EXT** mode and set a **NODE** value of 1 using the 1234 switch (next to the analoginput block on the board), and you should receive the message `1,1` which means `NODEID=1,Button Pressed`

**TIP** To set a node ID of 1 Just set the node switch 1 to ON which is 1 in binary
or for a node ID of 3 set the node switch 1 and 2 to ON, 3 in binary.


