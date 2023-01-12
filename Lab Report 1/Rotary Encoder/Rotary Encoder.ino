#include <Encoder.h>

// Connect rotary encoder for motor 1 to digital pins 2 and 3
Encoder EncoderLeft(2,11);
Encoder EncoderRight(3, 12); //enable pins with interrupt capability


void setup() {
  Serial.begin(9600);
}

void loop() {
  // Measure the circumference of each wheel
  float circumference1 = 31.42;  // Replace with measured circumference of wheel 1
  float circumference2 = 31.42;  // Replace with measured circumference of wheel 2

  // Determine the number of pulses per revolution for each rotary encoder
  float pulsesPerRevolution1 = 24;  // Replace with number of pulses per revolution for rotary encoder 1
  float pulsesPerRevolution2 = 24;  // Replace with number of pulses per revolution for rotary encoder 2

  // Read the position of each rotary encoder
  long position1 = EncoderLeft.read();
  long position2 = EncoderRight.read();

  // Convert the number of pulses to a distance for each motor
  float distance1 = (position1 * circumference1) / pulsesPerRevolution1;
  float distance2 = (position2 * circumference2) / pulsesPerRevolution2;

  // Print the distance traveled by each motor
  Serial.print("Motor 1: ");
  Serial.print(distance1);
  Serial.print("  Motor 2: ");
  Serial.println(distance2);

  delay(100);
}