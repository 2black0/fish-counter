#include <ezButton.h>

const int btnPin = A3;
bool startStatus = false;

ezButton button(btnPin);

void init_device()
{
	Serial.begin(9600);
	button.setDebounceTime(50);
	delay(50);
}

void init_pin()
{
	pinMode(btnPin, INPUT);
}

void setup()
{
	init_device();
	init_pin();
	Serial.println("Button Testing");
}

void loop()
{
	button.loop();
	if (button.isReleased())
	{
		startStatus = !startStatus;
	}
	Serial.println("Button Status: " + String(startStatus));
}