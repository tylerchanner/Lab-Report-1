#include "MPU9250.h"

MPU9250 mpu; // You can also use MPU9255 as is

void setup() {
    Serial.begin(115200);
    Wire.begin();
    delay(2000);

    mpu.setup(0x68);  // change to your own address

}
void loop() {
    if (mpu.update()) {
        int yaw = mpu.getPitch();
        Serial.println(yaw);
        
    }
}