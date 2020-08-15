#include <HCSR04.h>

const int trigPin = 2;
const int echoPin = 3;

int distance = 0;

UltraSonicDistanceSensor Sensor(trigPin, echoPin);

void init_device()
{
	Serial.begin("9600");
	delay(50);
}

void setup()
{
	init_device();
	Serial.println("Ultrasonic Sensor Testing");
}

void loop()
{
	double distance = Sensor.measureDistanceCm();
	Serial.println("Distance: " + String(distance) + "cm");
	delay(500);
}