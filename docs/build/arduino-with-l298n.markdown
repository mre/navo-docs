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

### Understanding DC Motor with Encoder

So we need to now effectively understand a little bit about the DC Motor and the need for an Encoder unit. A one liner - a DC Motor is a mechanical device that converts basically electrical energy to mechanical energy. Ok that's simple enough but that's enough. Why do we need an Encoder? With the target that we are trying to build, we need to be able to more precisely control the spped and direction of the motor which effectively translates to the navigability of the Navo. Encoders transform mechanical motion into electrical pulses that can then be used by a controller unit (like the Arduino) to make adjustments and fine tune the motor spped and direction. 

As a reference, we will use this DC Motor that I purchased <a href="https://tinyurl.com/ya3zlznr" target="_blank">from Amazon</a>, but every DC motor with an Encoder unit should behave the same. 

The image below shows the wiring definitions for the DC Motor model:

![dc-motor-wiring](../assets/images/motor/dc-motor-wiring.png)

There are different types of encoders available, such as liner encoder or rotary encoders. A DC Motor encoder basically has a rotary encoder which is often times mounted to the shaft of the motor. The rotary encoder used here is a 6 pole magnetic disc attached to the shaft of the motor, along with two <a href="https://en.wikipedia.org/wiki/Hall_effect" target="_blank">Hall effect</a> sensors. When the motor turns, the 6 pole magnetic disk rotates past the two sensors and when each time a magnetic pole passes one of the sensor, the encoder outputs a digital pulse. So here with the two hall effect sensors, we get two output signals separated by 90 dgrees. The sketch below shows the basic working principle behind a Rotary margnetic encoder. 

TODO.... draw sketch showing Rotary encoder

As it can be seen that the two sensing units (marked A & B) will emit a pulse signal as soon as they hit the underlying magnetic pin (6 of them as can be seen in the diagram above) and this pulse signal can be translated / understood in terms of the direction and speed of the motor. I will not explain more about this topic, but <a href="https://www.youtube.com/watch?v=dMBrR4gDi3s" target="_blank">here is a very descriptive video</a> on understanding DC Motor encoders in much detail. 

### Putting it all together - Arduino, L298N & the DC Motor

So for us, with this fundemental understanding, let us try this out by implementing a simple sketch and testing it out in the wild. Here is the fritzing schematic:

![arduino-h-bridge](../assets/images/arduino/arduino-h-bridge-motor.png)

