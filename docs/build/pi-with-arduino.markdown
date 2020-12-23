---
layout: default
title: Pi with Arduino
parent: Build Steps
nav_order: 1
---

## Pi with Arduino

So, our very first integration attempt is to integrate the Raspberry Pi with Arduino. We will use the Raspberry Pi 4. Let us break this down into the following steps:

1. ROS on the Raspberry Pi 4
2. Serial libraries on the Pi and Arduino

### Raspberry Pi 4 Setup

It is pretty easy to get your hands on the Pi, so just go grab one and follow along. 

The very first step with setting up your Pi is to install the base OS. You have many choices, but two of them stand out which is installing either Raspbian or Ubuntu. I prefer to run Ubuntu and ROS is very much compatible with Ubuntu, so why not!

Head over [here](https://ubuntu.com/download/raspberry-pi) and make sure to download the Ubuntu server 20.04 64 bit LTS version (we will use ROS Noetic which is based on Ubuntu 20.04 LTS)

After you have downloaded the image, head over [here](https://ubuntu.com/tutorials/how-to-install-ubuntu-on-your-raspberry-pi#1-overview) for a comprehensive installation instruction. It is pretty easy and straightforward!

Once you have your Raspberry Pi ready with Ubuntu 20.04, it is time to set up / install ROS!

TODO....


### Serial libraries set up

First let us setup Arduino. Now you could do this on your Raspberry Pi 4 or any other computer. You need to install the Arduino IDE.

The idea here is that you need to be able to make your Arduino serial communication capable and for this you will have to install a few ros based libraries. There is nothing nore specific to the Raspberry Pi 4. You could do the below steps from the Raspberry Pi 4, but assume that your Raspberry Pi 4 will be the server (probably running in your NAVO) and you do not want to have any IDE running on your production server, so I would set up my Arduino IDE on my Ubuntu machine.

Get the Arduino IDE from [here](https://ubuntu.com/tutorials/install-the-arduino-ide#1-overview). Make sure to download the appropriate Arduino IDE version for your Ubuntu version (For me it is Ubuntu 20.04). Get it installed as per the instructions!

The next step is to prepare and install the serial libraries that is required to make Arduino communicate with the Raspberry Pi. So for this, you need to open a terminal window on your Ubuntu machine and run the following commands one after the other.


```
sudo apt-get install ros-noetic-rosserial-arduino
```

```
sudo apt-get install ros-noetic-rosserial
```

Make sure to replace the ROS version appropriately. Here we base our discussion on the noetic version of ROS!

After this, fire up the Arduino IDE, by type arduino from a termincal window (see the screenshot below)

![arduino-ide-ubuntu](../assets/images/arduino-ide-ubuntu.png)

After this, open a new terminal window and cd into the arduino folder, and then cd into libraries directory. From that libraries directory, run the following command below. This command should build the needed libraries that will be used by ROS.


```
joesan@joesan-InfinityBook-S-14-v5:~/Arduino/libraries$ rosrun rosserial_arduino make_libraries.py .
```

Now after this, if you type the dir command, you should see the following:


```
joesan@joesan-InfinityBook-S-14-v5:~/Arduino/libraries$ dir
readme.txt  ros_lib
```

As you can see that there is a new folder called ros_lib


### Integration and test