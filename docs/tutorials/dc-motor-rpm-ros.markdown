---
layout: default
title: Motor RPM with ROS
parent: Tutorials
nav_order: 5
---

## DC Motor Speed Control with ROS

We saw in the previous tutorial on how to measure the RPM of a DC Motor. In this totorial, let us see how we could do a basic speed control using commands from a ROS node. We are not yet talking about a <a href="https://en.wikipedia.org/wiki/PID_controller" target="_blank">PID speed control algorithm</a> yet, I will come to that later in this tutorial. But first we need to create the circuit. 

Our hardware components are based on the Arduino Uno, the L298N H bridge for controlling the motors, a Raspberry Pi. We start with a brief mention about the L298N H bridge.

### L298N H Bridge

The L298N is a DC Motor controller. The speed of the DC Motor could be controlled by regulating / changing the input voltage to the motor. This is done by using a technique called <a href="https://en.wikipedia.org/wiki/Pulse-width_modulation" target="_blank">Pulse Width Modulation (PWM)</a>.

Okay, so we can now control the speed of the motor with PWM, but what about the direction? Speed is not just about going forwards, but also going backwards. Fortunately this is very simple using a so called <a href="https://en.wikipedia.org/wiki/H-bridge" target="_blank">H bridge</a>.

Hence, by combinig the PWM with an H Bridge, we can acheive what we want which is to control the speed and direction. The L298N is exactly this. I have purchased a few of these L298N Driver units. Each one is capable of controlling upto 2 DC Motors within the 5V and 35V range with a peak current of 2A.

Here is a picture of my L298N H bridge. For the exact model, go here to find the [list of materials](../hardware/) that you need to source!

![l298n-h-bridge](../assets/images/arduino/l298n-h-bridge.png)

Now that we know about the L298N Driver and its intended usgae, let us wire it up with the Arduino and see how we could control the motor.

### Putting it all together - Arduino, L298N & the DC Motor

So for us, with this fundemental understanding, let us try this out by implementing a simple sketch and testing it out in the wild. Here is the fritzing schematic:

![arduino-h-bridge](../assets/images/arduino/arduino-h-bridge-motor.png)

I hope understanding the circuit is pretty straight forward. We just need to ensure that we have a common ground while the rest of the connections are self explanatory. We just have connected a single motor to the circuit, though a single L298N H bridge can take 2 Motors. If we use the L298N H bridge in our Navo robot is a discussion for later as there are much better motor controllers which we will consider when we talk about the actual build.

**Power Supply**

As it can also be seen from the schematic above is that, we are using a 12V external power supply from a battery pack. This is just about enough to also power the Arduino board.

## The Logic

We have already deduced how we could measure the RPM of the DC Motor that we are using. More information about the Arduino sketch can be found <a href="https://navo-org.github.io//navo-docs/docs/tutorials/dc-motor-rpm.html#dc-motor-speed-control-arduino-sketch"> here</a>. There is nothing ROS specific about that sketch. We will use that sketch as a starting point and make it respond to ROS messages from a ROS node, while at the same time, make that sketch send back messages to another ROS node with the RPM that the motor is currently running. Let's get our hands dirty!

Additionally, <a href="https://navo-org.github.io//navo-docs/docs/tutorials/pi-with-arduino.html" >have a look here</a> to understand how ROS works with the Arduino using ROS serial libraries.

We are about to tackle a speed control logic. Let me introduce you to a simple speed control mechanism called <a href="https://en.wikipedia.org/wiki/PID_controller" target="_blank">PID speed control </a>. Before we set out to write a PID control logic, let us understand a bit about PID controllers:

### PID Control

We will try to debunk a PID controller from a functional perspective and later on converge on the P, the I and the D. The block diagram below shows the relation between a PID controller and a process that is optimized by using a PID controller. The process here could be anything, but here we assume that the process here is a water heater control system (WHCS). The WHCS works by receiving a desired value for the temperature and heats the water. For example., if we want the WHCS to heat the water to 40° C, we want it to exactly do that.

![pid-controller-1](../assets/images/motor/pid-controller-1.jpg)

From the image above, we have the Process which emits a Process Value (PV), the PID Contoller to which we give a Setpoint value (SP), the sensors that measure the actual Process Value (PV) which is then fed back into the PID controller, thus forming a closed loop. It can also be seen that the Process is also affected by external disturbances which makes it deviate from the Setpoint (SP). The PID controller's job is to account for these external disturnances and make the Process Value (PV) match the Setpoint (SP).

If the SP and the PV are the same – then there is no other thing in this world that is going to be much happy than our PID controller. It doesn’t have to do anything, it will set its output to zero, but in reality this is never going to be the case. So let us discuss further to understand the basics behind the PID controller.

We first need to understand what each of the term in the PID controller represent. The image below throws a bit of clarity on how each of the terms (Proportional, Integral & the Derivative) combine to get a smooth target output.

TODO: Show the image.... 

![pid-controller-math](../assets/images/motor/pid-controller-math.png)






