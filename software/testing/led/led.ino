const int ledPin = 13;

bool ledStatus = false;

void init_device()
{
	Serial.begin(9600);
}

void init_pin()
{
	pinMode(ledPin, OUTPUT);
	delay(50);
}

void setup()
{
	init_device();
	init_pin();
	Serial.println("Led Testing");
}

void loop()
{
	digitalWrite(ledPin, ledStatus);
	delay(1000);
	ledStatus = !ledStatus;
}