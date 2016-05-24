## Getting Started with RF-Craft

![CloudMaker](https://github.com/cheapjack/cheapjack.github.io/blob/master/tumblr_files/Cloudmaker.png)

Welcome to a teacher focussed workshop on using (and testing) RF-Craft!

### Simple setup and python Hello! sketch

We are going to cover 3 ways of using RF-Craft:

 * Sending messages to a built in Minecraft instance on board the Pi with a `receiver` HAT `Hello.py`
 * Sending messages to a local CanaryMod Server `HelloCanary.py`
 * Sending messages to the FACT Minecraft server at `mc.fact.co.uk:25565` `HelloCloudMaker.py`

They all use the same python code using the `mcpi` API 

Its well worth reading Martin O'Hanlon's [Stuff About Code API Reference](http://www.stuffaboutcode.com/p/minecraft-api-reference.html), his [Tutorial](http://www.stuffaboutcode.com/2013/04/minecraft-pi-edition-api-tutorial.html) and notes on [Connecting to other servers](http://www.stuffaboutcode.com/2014/10/minecraft-raspberryjuice-and-canarymod.html) that all the code side is based on.

### Out Of The Box

![RF-Craft v1.1](https://cloud.githubusercontent.com/assets/128456/11501525/b5ac718a-982c-11e5-957e-e393b6b7c2ae.png)

Your receiver and transmitter already have receiver.ino and button.ino uploaded to them but if your in the first workshop you need to change the group ID in the Arduino code so messages from other people dont get confused with each other but we will cover that later.

Look at the 2 RF Craft boards in your pack; you will see some plastic jumpers next to the long ATMEGA328 chip: one will be connected to the `|--PI--|` side, and another connected to `|External|`. Pi is the `receiver` and External is the `button` and they have the associated code on there.

All you need to do is get the receiver HAT on your Pi header, ensure the jumpers are set to `|--PI--|`, start the PI up, get it into Desktop mode `startx`, start a minecraft game and then power up the battery pack on the button HAT, the one with jumpers set to `|External|`.

You then need to clone this repo into your home directory and use the `Hello*.py` python programmes to receive the button messages over serial and then send commands to the minecraft server of your choice.  

Do this by opening a terminal window on the Pi and going `$ cd ~` then `$ ls` to list your files
Then either use `git` or `wget https://github.com/cheapjack/RF-Craft/archive/master.zip` then `unzip master.zip`

You can install git with `sudo apt-get install git-core`
Then `git clone https://github.com/cheapjack/RF-Craft.git`

Then you can run python code like this from the terminal 

`$ python Hello.py`

To stop it press `ctrl` & `C`

Then you can edit it with a text editor or edit and run the code with the IDLE Python IDE on the Pi

We are going to run you through the basic useage today and will provide further reading to experiment with other servers

#### Hello World!

We are going to start with a HAT receiver on board the PI: You generally talk to the server with the API like this:

```
    from mcpi import minecraft
    mc = minecraft.Minecraft.create()

    mc.postToChat("Hello World!")
```

You can specify an exact server address and port in the `.create()` call like this

```
mc = minecraft.Minecraft.create("127.0.0.1")
# This is the server running on your computer, the localhost address
# or mc =minecraft.Minecraft.create("mc.fact.co.uk") 
# or mc = minecraft.Minecraft.create(server.address)
# In this case we refer to a file called server.py that specifies a server address
# Or you can just use:
# mc = minecraft.Minecraft.create()
# By default the server will be a local instance of the CanaryMod server

```

Next you need to `import serial` at the top of the programme so we can receive our HAT messages

```
#########################
# Pi/PC/Mac/Linux  mode #
# RF-Craft HAT receiver #
#########################
# use the default serial port, 'COM1', '/dev/ttyAMA0' this will change platform to platform '/dev/tty.usbserial-A400f5sm'
# You can list your serial ports in Terminal
# Open a terminal window from the menu bar
# $ ls /dev
# It should show something like this '/dev/ttyAMA0', 9600
# So therefore define your serial object like this
# Or use the serial id that shows up on the Arduino IDE
ser = serial.Serial('/dev/ttyAMA0', 9600)
#ser = serial.Serial('COM1', 9600)
#ser = serial.Serial('/dev/tty.usbserial-A400f5sm', 9600)
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
```

Then we can setup our button receive message

`button1_received = "1,1\r\n"`

Finally we make a simple loop to respond to the button1_received value as serial receives it

```
while True:
    # This reads the ser object you defined before, the serial connected to the HAT
    serialcommand = str(ser.readline())
    if serialcommand == button5_received:
        print "Got mail from Button 5"
        mc.postToChat("Got mail from Button 5 saying " + serialcommand)
        mc.entity.setTilePos(4, 76,20, -64)
        sleep(1)
        mc.camera.setFollow()
```
### CanaryMod
We may not get to this in the workshop but another way of working is to run a server on a bigger computer and send messages to that.
Weve provided a server from the [CanaryMod Jenkins Repo](https://ci.visualillusionsent.net/) with a compatible plugin called Raspberry Juice and a CanaryMod server to send similar messages to a much more up to date world you can play with PC/Mac/Linux Minecraft running version `1.8`

You need to `$ cd ~/RF-Craft-master/CanaryForDistro/`
then `$ ls` to check whats there and `$ ./start.bat`
If you have JAVA installed all should be well, server will start and quit then edit the text file eula.txt  and change eula=false to eula=true and save the file. Then restart and you should be able to send messages to this server at the localhost address.

More details from Martin at his [Raspberry Juice Page](http://www.stuffaboutcode.com/2014/10/minecraft-raspberryjuice-and-canarymod.html)

CanaryMod and mcpi can't seem to agree on the coordinates of player positions and we've found you need to add -256 to x, add 64 to y and add -8 to z to make your coordinates match with the Minceraft client

Likewise the FACT server can be equally confused and we ususally have to:

```
# translate mc coords on CloudMaker server for mcpi ones
# add this to x
mcx = 177
# - this from y
mcy = 64
# - this from z
mcz = 135
```

What you can also do is use your Pi as the bridge to sending messages to any minecraft server with the Raspberry Juice plugin installed like the FACT server at `mc.fact.co.uk`

You can play with all of the code in Martin O'Hanlon and David Whale's excellent book **Adventures in Minecraft** which you can get from [the Wiley publishers website](http://eu.wiley.com/WileyCDA/Section/id-823690.html) and experiment with things like [this](https://github.com/martinohanlon/minecraft-demos)

### Basic Tools

#### Command Line

Behind every application on your computer is a command line where you can control it without the mouse.

 * `ls` - list where we are and what files we can look at 
 * `cd` - change directory go somewhere; we will stay here: ~/MoT/mcpi but if you get lost just type `cd ~/MoT-master`
 * `vim <file name.py>` - open a python file in vim 
 * `python HelloWorld.py` - runs the file HelloWorld.py to send a message to minecraft

#### Vim

[Vim](http://vim.rtorr.com/) (a version of Vi) is a text editor that lives pretty much on every server on the internet 

So you can edit things by typing `$ vi Hello.py` without needing the IDLE Python IDE editor.

Basically you move with the cursor keys and if you want to type something press `i` and you can type and delete as normal. When you're finished hit escape `esc` and if you want to `write` your changes type `:wq`  

 * `i` - insert text
 * `cursor keys` - move in the text
 * `esc` - stop inserting text
 * `:w` - write your changes
 * `:wq` - write your changes and quit vim

### Requirements

If you are running python code from a PC/Mac/Linux you will need to install `Python v2.7` from [here](https://www.python.org/about/gettingstarted/) and then you can follow the tutorials at [Raspberry Pi here](https://www.raspberrypi.org/learning/getting-started-with-minecraft-pi/worksheet/)

Id recommend looking at the [Hitchhiker's Guide To Python](http://docs.python-guide.org/en/latest/) for extensive tips on installing `Python 2.7` (much of what we use is transferable to `Python 3` but we stick with the Pi 2.7 for the time being) and although you can run from the command line you might want to use the Idle IDE. I'd also consider using Virtual Environments  [virtualenv](http://docs.python-guide.org/en/latest/dev/virtualenvs/).

Other useful stuff you can install are

`$ sudo apt-get install vim`
`$ sudo apt-get install screen`
`$ sudo apt-get install wicd-curse`s

### Shrimps

We've also used mcpi with the *brilliant* **Shrimped Arduino kits** from [Shrimping.it](http://shrimping.it/blog/) at its core and used prototype methods for visualising raw temperature and turbdiity data on onboard LED flashers, in Processing and in Minecraft. We used this method for the [ShrimpCraft](https://github.com/cheapjack/ShrimpCraft) project 





