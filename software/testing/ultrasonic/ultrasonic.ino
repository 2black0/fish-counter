#include <HCSR04.h>

const int trigPin = 2;
const int echoPin = 3;

int distance = 0;

UltraSonicDistanceSensor Sensor(trigPin, echoPin);

void init_device() {
  Serial.begin("9600");
  delay(50);
}

void init_pin() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void setup() {
  init_device();
  init_pin();
  Serial.println("Ultrasonic Sensor Testing");
}

void loop() {
  int distance = read_ultrasonic();
  Serial.println("Distance: " + String(distance) + "cm");
  delay(500);
}

int read_ultrasonic() {
  Serial.println("Read Sensor Ultrasonic");
  long duration = 0;
  int distance = 0;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  return distance;
}