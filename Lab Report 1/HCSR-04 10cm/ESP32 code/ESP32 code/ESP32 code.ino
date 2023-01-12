#include <Wire.h>
#include <HCSR04.h>

HCSR04 hc(5, 18); //initialisation class HCSR04 (trig pin , echo pin)

void setup() {
  Serial.begin(9600);
  Wire.begin();
}

void loop() {

  int distance = hc.dist();
  Serial.println(distance);
  
  Wire.beginTransmission(0x08);  // transmit to slave device address 8
  if (distance < 10) {
    Wire.write(1);           // send five bytes, one for each character
    Wire.endTransmission();  // end transmission
  }else{
    Wire.write(2);           // send five bytes, one for each character
    Wire.endTransmission();  // end transmission
  } 
  delay(60); 
}
  
  

