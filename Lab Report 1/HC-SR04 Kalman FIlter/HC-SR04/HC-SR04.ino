//define sound speed in cm/uS
#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701

const int trigPin = 5;
const int echoPin = 18;

// Define the moving average filter
const int MOV_AVG_LEN = 20;  // Length of the moving average filter
float moving_average[MOV_AVG_LEN];  // Array to store the moving average
int mov_avg_index = 0;  // Index for the moving average array

void setup()
{
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
}

void loop()
{
  long duration;
  float distanceCm;
  long total_distance = 0;  // Variable to store the total distance for averaging
  int num_readings = 20;  // Number of readings to average

  for (int i = 0; i < num_readings; i++) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);

    // Calculate the distance
    distanceCm = duration * SOUND_SPEED/2;
    total_distance += distanceCm;

    // Update the moving average filter using a circular buffer
    moving_average[mov_avg_index] = distanceCm;
    mov_avg_index = (mov_avg_index + 1) % MOV_AVG_LEN;
  }

  // Calculate the average distance
  float avg_distance = (float)total_distance / num_readings;

  // Calculate the filtered distance using the moving average filter
  float filtered_distance = 0;
  for (int i = 0; i < MOV_AVG_LEN; i++) {
    filtered_distance += moving_average[i];
  }
  filtered_distance /= MOV_AVG_LEN;

  // Display the filtered distance with 1 decimal place
  Serial.print(filtered_distance, 1);
  Serial.println(" cm");

  delay(500);
}
