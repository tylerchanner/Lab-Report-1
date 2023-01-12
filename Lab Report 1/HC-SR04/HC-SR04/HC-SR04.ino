include <HCSRO4.h>
HCSR04 hc(5,18);

void setup(){
  Serial.begin(9600)
}

void loop(){
  Serial.println(hc.dist());
}