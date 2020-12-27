/*
 * DC Motor Encoder Test Sketch
 * by Joesan [https://github.com/joesan]
 * 27.12.2020
 *
 * Records encoder ticks for each wheel
 * and prints the number of ticks for
 * each encoder every 500ms
 *
 */

// pins for the encoder inputs for Motor M1
#define M1_ENCODER_A 3 // The yellow wire in the sketch above
#define M1_ENCODER_B 4 // The green wire in the sketch above

// variable to record the number of encoder pulse
volatile unsigned long m1Count = 0;

void setup() {
  pinMode(M1_ENCODER_A, INPUT);
  pinMode(M1_ENCODER_B, INPUT);
  
  // initialize hardware interrupt
  attachInterrupt(0, m1EncoderEvent, CHANGE);
  
  Serial.begin(9600);
}

void loop() {
  Serial.print("M1 Count: ");
  Serial.println(m1Count);
  Serial.println();
  delay(500); // time in ms
}

// encoder event for the interrupt call
void m1EncoderEvent() {
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
  }
}
