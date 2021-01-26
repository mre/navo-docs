---
layout: default
title: PID Controller
parent: Tutorials
nav_order: 5
---

In this section, let us explore and understand this 17th century idea on how we could effectively do a speed control for the DC Motor, the <a href="https://en.wikipedia.org/wiki/PID_controller" target="_blank">PID Controller</a> mechanism

## PID Control

We will try to debunk a PID controller from a functional perspective and later on converge on the P, the I and the D. The block diagram below shows the relation between a PID controller and a process that is optimized by using a PID controller. The process here could be anything, but here we assume that the process here is a water heater control system (WHCS). The WHCS works by receiving a desired value for the temperature and heats the water. For example., if we want the WHCS to heat the water to 40° C, we want it to exactly do that.

![pid-controller-1](../assets/images/motor/pid-controller-1.jpg)

From the image above, we have the Process which emits a Process Value (PV), the PID Contoller to which we give a Setpoint value (SP), the sensors that measure the actual Process Value (PV) which is then fed back into the PID controller, thus forming a closed loop. It can also be seen that the Process is also affected by external disturbances which makes it deviate from the Setpoint (SP). The PID controller's job is to account for these external disturnances and make the Process Value (PV) match the Setpoint (SP). For our case here where we want to do DC Motor speed control, we have something called a closed-loop controller, where we tell the controller how fast we want the motor to run. We call this the set point. The controller then measures the actual speed of the motor and calculates the difference between the actual speed and the set point which is called the error. The controller then adjusts the voltage to the motor to reduce the error which in turn makes the Motor run at the set point we gave it originally.

If the SP and the PV are the same – then there is no other thing in this world that is going to be much happy than our PID controller. It doesn’t have to do anything, it will set its output to zero, but in reality this is never going to be the case. So let us discuss further to understand the basics behind the PID controller.

We first need to understand what each of the term in the PID controller represent. The image below throws a bit of clarity on how each of the terms (Proportional, Integral & the Derivative) combine to get a smooth target output.

![pid-controller-2](../assets/images/motor/pid-controller-2.jpg) 

As we can see from the image above that the error is calculated by simply calculating the difference between the Setpoint (SV) and the Process Value (PV) or in other words, the error is simply the difference between the desired value and the actual value.

Let us now try to mathematically understand what each of the terms mean and how they influence in minimizing the error.

### Proportional Control

This is the most simplest of the control where the controller gives an output that is directly proportional to the current error (difference between SV and PV) times a proportional factor which is synonymous to the error value. 

![pid-controller-p](../assets/images/motor/pid-controller-p.png)

It can be seen from the equation above that with a small Kp the controller will make small attempts to minimize the error, while for a larger Kp, the controller will make a larger attempt to minimize the error. This is good, but this approach suffers from either an overshoot (if Kp is too large) or an undershoot (if Kp is too small). Both these effects, we do want to avoid. There is always a steady state residual error in the case of a proportional controller.

### Integral Control

By introducing a time component to the proportional controller, we can mitigate the overshoot and undershoot problems. The integral controller, is capable of handling errors that happen over a certain set time interval. With using an integral component, we can thus overcome the steady state residual error that occurs with the proportional controller.

![pid-controller-i](../assets/images/motor/pid-controller-i.png)

The equation above sums all the previous errors over a given time interval t and accouns for the error correction accordingly. If we have a larger value for the term Ki, it will result in an overshoot.

### Differential Control

The differential controller or the derivative (slope) controller is effectively used to predict the systems future behavior. The proportional and the integral controller both respond to past errors, the differential controller is capable of predicting future behavior of the error. As it can be seen from tnhe equation below that the output of the differential controller depends on the rate of change of error over time, multiplied by a derivative constant Kd.

![pid-controller-d](../assets/images/motor/pid-controller-d.png)

The output of the derivative this helps in reducing / minimizing the overshoot error. For example., a larger derivative or a larger slope indicates that the next error will be far away from the previous error but a small derivative or a smaller slope indicates that the next error will be likely close to the previous error. 

### PID Equation

With the controllers and their equations nailed down, we have the following equations for the PID controller.

![pid-controller-out](../assets/images/motor/pid-controller-out.png)

and by substituting the values, we get

![pid-controller-math](../assets/images/motor/pid-controller-math.png)

So what that equation basically mean in our context which is to control the speed of the DC motor is that, the controller calculates the speed of the motor (actual_speed), calculates the error between the current speed and the target speed, uses the equation above to determine how much more or less the motor's speed has to be adjusted so that the current speed matches the target speed.

Now one question might arise on what values to choose for the PID co-efficients. Luckily people have thought about this and the one that comes to mind is the <a href="https://en.wikipedia.org/wiki/Ziegler%E2%80%93Nichols_method" target="_blank">Ziegler–Nichols method</a> introduced by John G. Ziegler and Nathaniel B. Nichols in the 1940s. It is a <a href="https://en.wikipedia.org/wiki/Heuristic" target="_blank">heuristic technique</a> of tuning a PID controller. The basic idea here is that it starts out by setting the integral and the derivative gains (basically the co-efficients Ki and Kd) to zero. The proportional gain (Kp) is then increased from zero until it reaches the untimate gain Ku. This untimate gain is the gain where the control loop has acheived a stable and consistent oscillation. The Ku and the oscillation period is then used to set the P, I and the D gains effectively. Let us not dive more into this for now. 

Hope I was able to explain the PID controller mechanism! With this basic understanding, <a href="https://navo-org.github.io//navo-docs/docs/tutorials/dc-motor-rpm-ros.html">head over here</a> to see how we could combine all what we have learnt theoretically so far to a more practical example.