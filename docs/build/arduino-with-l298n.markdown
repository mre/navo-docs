---
layout: default
title: Arduino with L298N
parent: Build Steps
nav_order: 2
---

## Arduino with L298N

Let us see how we could integrate Arduino with the L298N which is our motor controller. Now, it you are unsure about why we need an L298N H bridge, here is some background information about this!

### L298N H Bridge

The L298N is a DC Motor controller. The speed of the DC Motor could be controlled by regulating / changing the input voltage to the motor. This is done by using a technique called <a href="https://en.wikipedia.org/wiki/Pulse-width_modulation" target="_blank">Pulse Width Modulation (PWM)</a>.

Okay, so we can now control the speed of the motor with PWM, but what about the direction? Speed is not just about going forwards, but also going backwards. Fortunately this is very simple using a so called <a href="https://en.wikipedia.org/wiki/H-bridge" target="_blank">H bridge</a>.

Hence, by combinig the PWM with an H Bridge, we can acheive what we want which is to control the speed and direction. The L298N is exactly this. I have purchased a few of these L298N Driver unit. Each one is capable of controlling 2 DC Motors within the 5V and 35V range with a peak current of 2A.

Here is a picture of my L298N H bridge. For the exact model, go here to find the [list of materials](../hardware/) that you need to source!

TODO.... add an image of the L298N that I purchased

Now that we know about the L298N Driver and its intended usgae, let us wire it up with the Arduino and see how we could control the motor.

### Connecting Arduino with L298N


![arduino-h-bridge](../assets/images/arduino/arduino-h-bridge.png)

