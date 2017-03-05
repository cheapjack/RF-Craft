## Getting Started with RF-Craft
#### AA Battery Pack - RF-Craft Button - Pi & Hat/Computer & UART - Serial - Command Line - Minecraft -  Simples!

<img src="https://cloud.githubusercontent.com/assets/128456/23589243/5fe819d4-01c1-11e7-8902-70254cff11d2.jpg" width="400">

**RF-Craft** is a *simple* messaging system to send serial messages by low power radio to a Raspberry Pi when attached as a HAT or any serial connection that uses a UART adaptor. Refer to Setup-RPi-Hat.md for setup instructions.

It comes in a receiver and transmitter pair. It's an expensive build and you would end up selling them for £39 cost. So we are not selling them but giving them to educators and artists and groups to play with. However you can build them yourself as all the details are in this repo. You'll need some time and experience so its not a quick start but going through that process will set you up for building almost anything; but it's beyond our scope to help you much with that. RF-Craft is essentially an experiment in designing physical IoT devices with young people to communicate with  Minecraft. Most of the learning here is about participatory ecosystems in the design process both for users and developers. 

But we wanted RF-Craft to let you do anything with these messages. So no Apps, complicated bluetooth pairing or custom software just open-source simplicity and `serial` communication the most basic and so univerally useful communication protocol. In our case we are using python-serial to parse `serial` messages into commands to `mcpi` a python API for the Raspberry Pi version of Minecraft because there is currently a community of young people and educators doing that. But equally they could move a robot, make a cup of tea or send a tweet

### Hardware

#### Out Of The Box

Your **receiver** is the **RF-Craft HAT** without battery flashed with the sketch `receiver.ino` 
Your **transmitter** is the **RF-Craft HAT** with a battery pack flashed with the sketch `button.ino` 

If you are within range of other transmitters you may want to change the `NETWORK_ID` and the `ENCRYPTKEY` in the Arduino code on both so messages from other people dont get confused with each other but we will cover that later. You will need a UART interface attached to the P1 UART jumpers next to the external power input [available here](http://start.shrimping.it/kit/cp2102.html)

You can still switch each HAT between transmitter & receiver mode when you are ignoring RaspberryPi and you want to use as an arduino radio. 

Look at the 2 RF Craft boards in your pack; you will see a sliding switch next to the tiny square ##ATMEGA328P## chip: set it to the **RPI** side and the board is a **receiver** ready to send the received serial commands through the HAT pins to a Raspberry Pi or over a UART interface (not included but [available here](http://start.shrimping.it/kit/cp2102.html)

**EXT** Pi is the **button** mode and lets you set an ID number with the set of 4 switches marked ON APEMS 1234. Set these switches off and on in binary to get `NODE_ID` numbers 1-15. 

So to get `NODE_ID 1` set switch 1 to *on* and 2-4 to *off* 
So to get `NODE_ID 2` set switch 2 to *on* and 1,3 & 4 to *off* 
To get `NODE_ID 3` set switch 1 & 2 to *on* and 3 & 4 to *off* and so on. 

Now you can use the button to send a message to your receiver.

## Software

### Simple setup and python Hello! sketches

RF-Craft works can work in a few ways 

 * Sending messages to a running Minecraft instance on board the Pi with a `receiver` HAT `Hello.py`
 * Sending messages to a local CanaryMod Server `HelloCanary.py`
 * Sending messages to the FACT Minecraft server at `mc.fact.co.uk:25565` `HelloCloudMaker.py`
 * Sending messages to each other, arduino to arduino and interacting with Serial on another computer using a UART serial adaptor for arduino
 * Sending & receiving serial messages with python to trigger text and other things. Check out Adventures-in-RFCraft.md

All minecraft options use the same python code using the `mcpi` API but we advise you stick with your Pi. Put it on the same wifi network and other RPi players could join and watch whats going on like we did for [RF-Rail-Craft](http://github.com/cheapjack/RF-Rail-Craft) for **Museum of Science & Industry Manchester** for the **Lever Prize** which [Cloudmaker](https://github.com/cheapjack/CloudMaker/) won kickstarting the **FACTLab** project Dr Mark Wright put together.

Its well worth reading Martin O'Hanlon's [Stuff About Code API Reference](http://www.stuffaboutcode.com/p/minecraft-api-reference.html), his [Tutorial](http://www.stuffaboutcode.com/2013/04/minecraft-pi-edition-api-tutorial.html). His work is the original inspiration for this project.

And if you want to interact with non-Pi servers read his notes on [Connecting to other servers](http://www.stuffaboutcode.com/2014/10/minecraft-raspberryjuice-and-canarymod.html) that all the code side is based on.

First get on the internet & clone this repo into your home directory and use the `Hello*.py` python programmes to receive the button messages over serial and then send commands to the minecraft server of your choice.  

Do this by opening a terminal window on the Pi and going `$ cd ~` then `$ ls` to list your files
Then either use `git` or `wget https://github.com/cheapjack/RF-Craft/archive/master.zip` then `unzip master.zip`

You can install git with `sudo apt-get install git-core`
Then `git clone https://github.com/cheapjack/RF-Craft.git` what's good about this is that you can get any future updates from this server with a simple `git pull`. Go [here for a git 101](https://rogerdudler.github.io/git-guide/) it's a useful thing to know and it really sets you up for open sourcing your work in the future. You can read about what Im interested in about git [here](https://gitlab.com/redock/critical-kits/blob/master/Why_Git.md)

Then you can run python code like this from the terminal 

`pi$ python HelloSerial.py`

To stop it press `ctrl` & `C`

Then you can edit it with a text editor like [vim](http://vim.rtorr.com/) Install **vim** with `pi$ sudo apt-get install vim` or edit and run the code with the built-in RPi IDLE Python IDE on the Pi.


#### Hello World!

Follow the guide at [Setup-RPi-Hat.md](Setup-RPi-Hat.md) in the Repo and run HelloSerial.py

`pi$ python HelloSerial.py` press your powered transmitter onboard button, watch the led flash morse code and you should receive the message "Got mail from Button 1"

#### Hello Minecraft World!

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
# In this case we refer to a file called server.py that specifies a server address
# Or you can just use:
# mc = minecraft.Minecraft.create()

```
Remember to have Minecraft running on the Pi before running HelloPi.py
Next you need to `import serial` at the top of the programme so we can receive our HAT messages

```
#########################
# Pi/PC/Mac/Linux  mode #
# RF-Craft HAT receiver #
#########################
# use the default serial port, 'COM1', '/dev/ttyAMA0' this will change platform to platform '/dev/tty.usbserial-A400f5sm'
# Please refer to Setup-RPi-Hat.md for help setting up serial ports on the pi.
# On windows the ports are usually COM1, COM2 etc but you will need to look into that. We are focussing on the Pi
# On UNIX sysems/Pi or Linux you can list your serial ports in Terminal
# Open a terminal window from the menu bar
# $ ls /dev/tty*
# It should show up a list with one port something like this '/dev/ttyAMA0', 9600
# So therefore define your serial object like this
ser = serial.Serial('/dev/ttyS0', 9600)
#ser = serial.Serial('/dev/ttyAMA0', 9600)
#ser = serial.Serial('COM1', 9600)
#ser = serial.Serial('/dev/tty.usbserial-A400f5sm', 9600)
#ser = serial.Serial('/dev/tty.SLAB_USBtoUART', 9600)
#########################################################
# The Button sends the serial message (node , action)   #
# node is the value in #define NODEID in Line 10 of the #
# Arduino code which you can change with the 1-4 NODE_ID#
# switches                                              #
# in ~/RF-Craft/arduino/button/button.ino               #
# It comes with the default node of 1 on the arduino HAT#
#                                                       #
# action "1", "ButtonPressed"                           #
# action "2", "Error"                                   #
# action "3", "OK"                                      #
#                                                       #
#########################################################
```

Then we can setup our button receive variable to listen for a button press

`button1_received = "1,1\r\n"`

Finally we make a simple loop to respond to the button1_received value as serial receives it

```
while True:
    # This reads the ser object you defined before, the serial connected to the HAT
    serialcommand = str(ser.readline())
    if serialcommand == button1_received:
        print "Got mail from Button 1"
        mc.postToChat("Got mail from Button 1 saying " + serialcommand)
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

CanaryMod and mcpi can't seem to agree on the coordinates of player positions and we've found you need to add -256 to x, add 64 to y and add -8 to z to make your coordinates match with the Minceraft client like this:

```
# translate mc coords on CanaryMod server for mcpi ones
# add this to x
mcx = -256
# - add this to y
mcy = 64
# - add this to z
mcz = -8
```


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

#### Multiple HATS & the Arduino IDE

If in the unlikey event you have a room full of receiver HATs then a button press message will be received by all receivers! To avoid this you can modify the arduino `button.ino` and `receiver.ino` NETWORKID value

Open the RF-Craft/arduino/button.ino sketch with your Arduino IDE

Download it [from here](https://www.arduino.cc/)

Connect the red FTDI cable adaptor to your button HAT and ensure that pins connect like this:
```
FTDI -> HAT
RST -> RST
RX -> RX
TX -> TX
VCC -> VIN
CTS -> NC #(NC stands for not Connected)
```

You can use any coloured combos of **female** to **female** jumper cable you like as long as they follow the wiring above

Now choose Tools/Board "Arduino/Genuino Uno" from the Arduino IDE menu
Choose Tools/Port "cu.usbserial-####" 
Choose Tools/Programmer "ArduinoISP"

Change line 9 from `#define NETWORKID   87` to a number of your choice:
`#define NETWORKID   88`

Now Upload your code to the HAT. As it's a button it's 3 jumpers are on the |External| side. Now you need to do the same process for your receiver HAT

Open RF-Craft/arduino/receiver/receiver.ino

Change line 9 from `#define NETWORKID   87` to a number of your choice, but the same number as your button ie::
`#define NETWORKID   88`

**REMEMBER** to move your receiver HAT jumpers to |--PI--| to |External| or the Arduino IDE cant see it. Then swap back over once you have uploaded successfully. 

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





