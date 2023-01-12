#include <Wire.h>
#define I2C_SLAVE_ADDR 0x08  // 4 in hexadecimal
int led_pin = 2;
void close_to_wall();
void goBackwards();

#include <Servo.h>  //include the servo library
#define servoPin 4
Servo myservo;        // create servo object to control a servo
float steeringAngle;  // variable to store the servo position

#define enA 5  //EnableA command line - should be a PWM pin
#define enB 6  //EnableB command line - should be a PWM pin

//name the motor control pins - replace the CHANGEME with your pin number, digital pins do not need the 'D' prefix whereas analogue pins need the 'A' prefix
#define INa A0  //Channel A direction
#define INb A1  //Channel A direction
#define INc A2  //Channel B direction
#define INd A3  //Channel B direction

byte speedSetting = 0;  //initial speed = 0
byte speedLeft = 0;
byte speedRight = 0;

int check_close_to_wall=0;

void setup() {
  Wire.begin(I2C_SLAVE_ADDR);    // join i2c bus #4 - on the Arduino NANO the default I2C pins are A4 (SDA), A5 (SCL)
  Wire.onReceive(receiveEvent);  // register event
  Serial.begin(9600);            // start serial for output
  pinMode(led_pin, OUTPUT);

  myservo.attach(servoPin);  //attach our servo object to pin D4
  //the Servo library takes care of defining the PinMode declaration (libraries/Servo/src/avr/Servo.cpp line 240)

  //configure the motor control pins as outputs
  pinMode(INa, OUTPUT);
  pinMode(INb, OUTPUT);
  pinMode(INc, OUTPUT);
  pinMode(INd, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);

  //initialise serial communication
  Serial.begin(9600);
  Serial.println("Arduino Nano is Running");  //sanity check

  speedSetting = 150;
  motors(speedSetting, speedSetting);  //make a call to the "motors" function and provide it with a value for each of the 2 motors - can be different for each motor - using same value here for expedience
  Serial.print("Motor Speeds: ");
  Serial.println(speedSetting);

  myservo.write(-20);
}

void receiveEvent() {

  check_close_to_wall = Wire.read();
  Serial.println(check_close_to_wall);
}

void goBackwardsFunction() {
  goBackwards();
}

void loop() {
  
  if (check_close_to_wall == 2) {  // remove int typecast and use == operator
    goBackwards();
    
  } 
  else if (check_close_to_wall == 1){
    stopMotors();
  }
 
}


// function to clear the I2C buffer
void emptyBuffer(void) {
  Serial.println("Error: I2C Byte Size Mismatch");
  while (Wire.available()) {
    Wire.read();
  }
}

void close_to_wall() {
  Serial.println("works to here");
  stopMotors();
  delay(1000);
}

void motors(int leftSpeed, int rightSpeed) {
  //set individual motor speed
  //direction is set separately

  analogWrite(enA, leftSpeed);
  analogWrite(enB, rightSpeed);
}

void moveSteering() {
  //you may need to change the maximum and minimum servo angle to have the largest steering motion
  int maxAngle = 120;
  int minAngle = -2;
  myservo.write(0);
  for (steeringAngle = minAngle; steeringAngle <= maxAngle; steeringAngle += 1) {  //goes from minAngle to maxAngle (degrees)
    //in steps of 1 degree
    myservo.write(steeringAngle);  //tell servo to go to position in variable 'steeringAngle'
    delay(15);                     //waits 15ms for the servo to reach the position
  }
  for (steeringAngle = maxAngle; steeringAngle >= minAngle; steeringAngle -= 1) {  // goes from maxAngle to minAngle (degrees)
    myservo.write(steeringAngle);                                                  //tell servo to go to position in variable 'steeringAngle'
    delay(15);                                                                     //waits 15 ms for the servo to reach the position
  }
  myservo.write(40);
}

void parking(){
  //FOrward for one second
  goForwards();
  delay(1000);

  //180 degree turn
  goAntiClockwise();
  delay(2000);
  
  //Go back until 10cm
  do{
    goBackwards();
  }while(check_close_to_wall !=1);
//90 degree turn
  goClockwise();
  delay(2000);
//go backwards until wall
  do{
    goBackwards();
  }while(check_close_to_wall !=1);

  return 0;
  



}


void goBackwards() {
  digitalWrite(INa, LOW);
  digitalWrite(INb, HIGH);
  digitalWrite(INc, LOW);
  digitalWrite(INd, HIGH);
}

void goForwards() {
  digitalWrite(INa, HIGH);
  digitalWrite(INb, LOW);
  digitalWrite(INc, HIGH);
  digitalWrite(INd, LOW);
}

void goClockwise() {
  digitalWrite(INa, HIGH);
  digitalWrite(INb, LOW);
  digitalWrite(INc, LOW);
  digitalWrite(INd, HIGH);
}

void goAntiClockwise() {
  digitalWrite(INa, LOW);
  digitalWrite(INb, HIGH);
  digitalWrite(INc, HIGH);
  digitalWrite(INd, LOW);
}

void stopMotors() {
  digitalWrite(INa, LOW);
  digitalWrite(INb, LOW);
  digitalWrite(INc, LOW);
  digitalWrite(INd, LOW);
}
