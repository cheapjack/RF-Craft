# Setup RPi for use with HATS

You need to disable serial on your Pi with 
`sudo raspi-config`

Select Advanced Options/Serial and disable the serial login shell or Interface Options/Serial and disable the serial login shell but enable the hardware(UART)


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

Verify by using screen
Install it first if you dont have it; its handy!
`sudo apt-get install screen`

then listen on the `/dev/ttyS0` serial port at 9600 baudrate that your HAT communicates with.

`screen /dev/ttyS0 9600`

Activate and power your **RF-Craft HAT** in **EXT** mode with a **NODE** value of 1-15 and you will see the message `NODEID,MESSAGE` so `1,1` is `NODEID=1,On`

