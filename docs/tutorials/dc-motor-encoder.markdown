---
layout: default
title: DC Motor with Encoder
parent: Tutorials
nav_order: 4
---
test
A DC Motor eqipped with a built in encoder is going to immensly help us in precisely controlling the spped at which the motor rotates. Let us go through the basics behind such an encoder and how it relates to the speed ot the motor.

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

It can be seen that the two sensing units (marked A & B) will emit a pulse signal as soon as they hit the underlying magnetic pin (6 of them as can be seen in the diagram above) and this pulse signal can be translated / understood in terms of the direction and speed of the motor. I will not explain more about this topic, but <a href="https://www.youtube.com/watch?v=dMBrR4gDi3s" target="_blank">here is a very descriptive video</a> on understanding DC Motor encoders in much detail.

CW  -> Clockwise Direction
CCW -> Counter-Clockwise Direction

we can now infer from the square wave pulse signals that binary combinations for the pulses A & B, we can infer that when we get a pulse signal that has a RISING for the pulse A and during this if we measure a LOW for pulse B, we know that the motor is in the forward direction (CW). If on the other hand when the pulse signal for A has a RISING and during this if we measure a HIGH for pulse B, we know that the motor is in the reverse direction (CCW).

Ok that's for the direction. Now let us see how we could leverage this information and with some additional data from the Motor's specification, determine the RPM which forms the basis for doing speed control. To do this we need to understand the motor's specification.

The <a href="https://www.pololu.com/product/4843" target="_blank"> DC Motor that we use </a> has a metal gearbox with a ratio of 20.4:1 and a shaft with a diameter of 25 mm. The resolution of the encoder that is assembled to the motor shaft is rated at 48 Cycles Per Revolution (CPR). What this exactly means is that if the motor shaft turns one round the output of the encoder counts up to 48. But it is important to notice that the gearbox shaft is different than the motor shaft and as mentioned before, the ratio of rotation between these shafts is 20.4:1. So if motor shaft turns 20.4 times, gearbox shaft turns just 1 time. So with this understanding, the cycles per revolution or pulses per revolution of the gearbox shaft can be calculated with the following formula:

![motor-cpr-formula](../assets/images/motor/motor-cpr-formula.png)

So with this formula at hand, we get the gearbox CPR = 20.4 * 48 = 979.62

The gearbox output resolution (979.62 CPR) is the only value that we will get from DC motor as feedback which when coupled with time hepls us do speed control. Now the formula to calculate the RPM (speed) is given by:

![motor-cpr-formula](../assets/images/motor/dc-motor-rpm-formula-1.png)

where revolutions per count or revolutions per pulse equates to 1 / 979.62 (we know that pulse per revolution PPR or CPR is 979.62), so if we plug in these values into the equation above, we end up with the following:

![motor-cpr-formula](../assets/images/motor/dc-motor-rpm-formula-2.png)

We then have to plug in this equation into the sketch below and measure the number of pulse counts every second. Let us see how the sketch looks like!

### DC Motor Speed Control Arduino Sketch

{% highlight c %}
/*
 * DC Motor Encoder Test Sketch
 * by Joesan [https://github.com/joesan]
 * 27.12.2020
 *
 * Records encoder pulses and computes the rpm
 * every second
 *
 */
// pins for the encoder inputs for Motor M1
#define M1_ENCODER_A 3 // The yellow wire in the sketch above
#define M1_ENCODER_B 4 // The white wire in the sketch above

int enA = 8;
int in1 = 9;
int in2 = 10;

// variable to record the number of encoder pulse
volatile unsigned long m1Count = 0;
double rpm = 0;
unsigned long lastmillis = 0;

void setup() {
  pinMode(M1_ENCODER_A, INPUT);
  pinMode(M1_ENCODER_B, INPUT);
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  
  // initialize hardware interrupt
  attachInterrupt(digitalPinToInterrupt(M1_ENCODER_A), m1EncoderEvent, RISING);
  
  Serial.begin(9600);
}

void loop() {
  // Turn on Motor A forward direction
  runForward(255);

  // Calculate the RPM every second
  if (millis() - lastmillis == 1000) {
    // Disable interrupt when calculating
    detachInterrupt(digitalPinToInterrupt(M1_ENCODER_A));
    // rpm = counts / second * seconds / minute * revolutions / count
    rpm = m1count * 60 / 979.62;      
    Serial.print("RPM =\t");
    Serial.println(rpm);  
    m1Count = 0;
    lastmillis = millis();
    // Enable interrupt
    attachInterrupt(digitalPinToInterrupt(M1_ENCODER_A), m1EncoderEvent, RISING);
  }
}

void runForward(int speed) { //speed 0-255
  analogWrite(enA, speed);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
}

void runBackward(int speed) { //speed 0-255
  analogWrite(enA, speed);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
}

void m1EncoderEvent() {
  m1Count++;
}
{% endhighlight %}

The important part to note about the code above is the use of the attachInterrput function. <a href="https://www.allaboutcircuits.com/technical-articles/using-interrupts-on-arduino/" target="_blank">Have a look here</a> for a very good explanation of the function parameters and its meaning! Here is a very basic explanation behind using interrupts.

**Hardware interrupts**

If you are a bit familiar with the pins on the standard <a href="https://www.arduino.cc/en/reference/board" target="_blank">Arduino board</a>, the pins 2 and 3 are classified as pins for hardware interrupts. Have a <a href="https://playground.arduino.cc/Code/Interrupts/" target="_blank">look here to understand what interrupts are</a> and how they can be useful. So in essence with hardware interrupts, your main program runs until the state of one of your interrupt pins change. The main program is stopped, a special interrupt method / function is called and then the main program resumes. For example., if your main program is about navigating your robot by avoiding obstacles, and if your robot recognizes an obstacle, the interrupt pin can be made to change its state from LOW to HIGH and this would trigger the interrupt function to be called, where you could then adjust the speed of the motor by slowing it down.

From the sketch above, we have connected the Encoder A pin is connected to the hardware interrupt pin 3 of the Arduino.
