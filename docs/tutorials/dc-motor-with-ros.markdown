---
layout: default
title:DC Motor with ROS
parent: Tutorials
nav_order: 4
---

## DC Motor Speed Control with ROS

We saw in the previous tutorial on how to measure the RPM of a DC Motor. In this totorial, let us see how we could do a basic speed control using commands from a ROS node. We are not yet talking about a <a href="https://en.wikipedia.org/wiki/PID_controller" target="_blank">PID spped control algorithm</a> yet, but just a very basic spped manipulation using commands from a ROS node. But first we need to create the circuit. 

Our hardware components are based on the Arduino Uno, the L298N H bridge for controlling the motors, a Raspberry Pi. We start with a brief mention about the L298N H bridge.

### L298N H Bridge

The L298N is a DC Motor controller. The speed of the DC Motor could be controlled by regulating / changing the input voltage to the motor. This is done by using a technique called <a href="https://en.wikipedia.org/wiki/Pulse-width_modulation" target="_blank">Pulse Width Modulation (PWM)</a>.

Okay, so we can now control the speed of the motor with PWM, but what about the direction? Speed is not just about going forwards, but also going backwards. Fortunately this is very simple using a so called <a href="https://en.wikipedia.org/wiki/H-bridge" target="_blank">H bridge</a>.

Hence, by combinig the PWM with an H Bridge, we can acheive what we want which is to control the speed and direction. The L298N is exactly this. I have purchased a few of these L298N Driver units. Each one is capable of controlling upto 2 DC Motors within the 5V and 35V range with a peak current of 2A.

Here is a picture of my L298N H bridge. For the exact model, go here to find the [list of materials](../hardware/) that you need to source!

TODO.... add an image of the L298N that I purchased

Now that we know about the L298N Driver and its intended usgae, let us wire it up with the Arduino and see how we could control the motor.

### Putting it all together - Arduino, L298N & the DC Motor

So for us, with this fundemental understanding, let us try this out by implementing a simple sketch and testing it out in the wild. Here is the fritzing schematic:

![arduino-h-bridge](../assets/images/arduino/arduino-h-bridge-motor.png)

A few points to mention about the sketch:

**Hardware interrupts**

If you are a bit familiar with the pins on the standard <a href="https://www.arduino.cc/en/reference/board" target="_blank">Arduino board</a>, the pins 2 and 3 are classified as pins for hardware interrupts. Have a <a href="https://playground.arduino.cc/Code/Interrupts/" target="_blank">look here to understand what interrupts are</a> and how they can be useful. So in essence with hardware interrupts, your main program runs until the state of one of your interrupt pins change.The main program is stopped, a special interrupt method / function is called and then the main program resumes. For example., if your main program is about navigating your robot by avoiding obstacles, and if your robot recognizes an obstacle, the interrupt pin can be made to change its state from LOW to HIGH and this would trigger the interrupt function to be called, where you could then adjust the speed of the motor by slowing it down.

From the sketch above, we have connected the Encoder A pin is connected to the hardware interrupt pin 3 of the Arduino.

TODO.... Note about adding the second motor!

**Power Supply**

As it can also be seen from the schematic above is that, we are using a 12V external power supply from a battery pack. This is just about enough to also power the Arduino board.

