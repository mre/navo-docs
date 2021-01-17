---
layout: default
title: DC Motor Speed Control
parent: Tutorials
nav_order: 3
---

## DC Motor

In this tutorial, we will look at how to do speed control using a DC Motor that has a quadrature shaft encoder. I will be using this <a href="https://www.pololu.com/product/4843" target="_blank">DC Motor with Encoder</a> as a reference. The main reason being that it has a very good specification documentation. The instructions here will be the same for any similiar motor with a quadrature encoder attached to the shaft of the motor.

I will refuse to talk about DC Motors in general as that is not the focus for us, but rather to understand how to make use of the Encoder pulses with which we could measure the RPM and thus control the speed.

### Understanding DC Motor with Encoder

So we need to now effectively understand a little bit about the DC Motor and the need for an Encoder unit. A one liner - a DC Motor is a mechanical device that converts basically electrical energy to mechanical energy. Ok that's simple enough but that's enough. Why do we need an Encoder? With the target that we are trying to build, we need to be able to more precisely control the speed and direction of the motor which effectively translates to the navigability of the Navo. Encoders transform mechanical motion into electrical pulses that can then be used by a controller unit (like the Arduino) to make adjustments and fine tune the motor spped and direction. 

As mentioned before, we will use <a href="https://www.pololu.com/product/4843" target="_blank">DC Motor with Encoder</a>. The table and the image below clarifies the wiring definitions.

<table style="width:100%; border: 1px solid black;">
  <tr>
    <th align="left" style="border: 1px solid black;">Color</th>
    <th align="left" style="border: 1px solid black;">Function</th> 
  </tr>
  <tr>
    <td style="border: 1px solid black;">Red</td>
    <td style="border: 1px solid black;">motor power (connects to one motor terminal)</td>
  </tr>
   <tr>
    <td style="border: 1px solid black;">Black</td>
    <td style="border: 1px solid black;">motor power (connects to the other motor terminal)</td>
  </tr>
   <tr>
    <td style="border: 1px solid black;">Green</td>
    <td style="border: 1px solid black;">encoder GND</td>
  </tr>
   <tr>
    <td style="border: 1px solid black;">Blue</td>
    <td style="border: 1px solid black;">encoder Vcc (3.5 V to 20 V)</td>
  </tr>
   <tr>
    <td style="border: 1px solid black;">Yellow</td>
    <td style="border: 1px solid black;">encoder A output</td>
  </tr>
   <tr>
    <td style="border: 1px solid black;">White</td>
    <td style="border: 1px solid black;">encoder B output</td>
  </tr>
</table> 

![dc-motor-wiring](../assets/images/motor/dc-motor-wiring-pololu-25d.png)

There are different types of encoders available, such as liner encoder or rotary encoders. A DC Motor encoder basically has a rotary encoder which is often times mounted to the shaft of the motor. The rotary encoder used here is a 6 pole magnetic disc attached to the shaft of the motor, along with two <a href="https://en.wikipedia.org/wiki/Hall_effect" target="_blank">Hall effect</a> sensors. When the motor turns, the 6 pole magnetic disk rotates past the two sensors and when each time a magnetic pole passes one of the sensor, the encoder outputs a digital pulse. So here with the two hall effect sensors, we get two output signals separated by 90 dgrees. The sketch below shows the basic working principle behind a Rotary margnetic encoder. 

![rotary-encoder](../assets/images/motor/encoder.jpg)
![rotary-encoder-pulse](../assets/images/motor/square-wave.png)

As it can be seen that the two sensing units (marked A & B) will emit a pulse signal as soon as they hit the underlying magnetic pin (6 of them as can be seen in the diagram above) and this pulse signal can be translated / understood in terms of the direction and speed of the motor. I will not explain more about this topic, but <a href="https://www.youtube.com/watch?v=dMBrR4gDi3s" target="_blank">here is a very descriptive video</a> on understanding DC Motor encoders in much detail.

CW  -> Clockwise Direction
CCW -> Counter-Clockwise Direction

As wwe can infer from the square wave pulse signals that binary combinations for the pulses A & B, we can infer that when we get a pulse signal that has a RISING for the pulse A and during this if we measure a LOW for pulse B, we know that the motor is in the forward direction (CW). If on the other hand when the pulse signal for A has a RISING and during this if we measure a HIGH for pulse B, we know that the motor is in the reverse direction (CCW).

Ok that's for the direction. Now let us see how we could leverage this information and with some additional data from the Motor's specification, determine the RPM which forms the basis for doing speed control.