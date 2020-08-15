#include <Servo.h>

const int servo1Pin = 9;
const int servo2Pin = 10;

Servo servo1;
Servo servo2;

void init_device()
{
	Serial.begin(9600);
	servo1.attach(servo1Pin, 600, 2300);
	servo2.attach(servo2Pin, 600, 2300);
}

void setup()
{
	init_device();
	Serial.println("Servo Testing");
}

void loop()
{
	servo1_on();
	servo1_off();
	servo2_on();
	servo2_off();
}

void servo1_on()
{
	Serial.println("Servo 1 ON");
	servo1.write(90);
	delay(2500);
}

void servo1_off()
{
	Serial.println("Servo 1 OFF");
	servo1.write(45);
	delay(2500);
}

void servo2_on()
{
	Serial.println("Servo 2 ON");
	servo2.write(90);
	delay(2500);
}

void servo2_off()
{
	Serial.println("Servo 2 OFF");
	servo2.write(45);
	delay(2500);
}