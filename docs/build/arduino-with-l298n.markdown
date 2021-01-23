---
layout: default
title: Arduino with L298N
parent: Build Steps
nav_order: 2
---

## Arduino with L298N

Let us see how we could integrate Arduino with the L298N which is our motor controller. Now, it you are unsure about why we need an L298N H bridge, here is some background information about this! 


With that being said, our sketch looks like this:

{% highlight c %}
/*
 * DC Motor Encoder Test Sketch
 * by Joesan [https://github.com/joesan]
 * 27.12.2020
 *
 * Records encoder ticks for each wheel
 * and prints the number of ticks for
 * each encoder every 500ms
 * 
 * WARNING: This is a throw away sketch, it is here
 * just for experimental purposes.
 *
 */
// pins for the encoder inputs for Motor M1
#define M1_ENCODER_A 3 // The yellow wire in the sketch above
#define M1_ENCODER_B 4 // The green wire in the sketch above

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

// encoder event for the interrupt call
/*void m1EncoderEvent() {
  if (digitalRead(M1_ENCODER_A) == HIGH) {
    if (digitalRead(M1_ENCODER_B) == LOW) {
      m1Count++;
    } else {
      m1Count--;
    }
  } else {
    if (digitalRead(M1_ENCODER_B) == LOW) {
      m1Count--;
    } else {
      m1Count++;
    }
  } */
}
{% endhighlight %}

That piece of code above deserves some basic explanation. Let us try to do that!

The important part to note about the code above is the use of the attachInterrput function. <a href="https://www.allaboutcircuits.com/technical-articles/using-interrupts-on-arduino/" target="_blank">Have a look here</a> for a very good explanation of the function parameters and its meaning!



