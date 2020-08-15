#include <HX711.h>

const int sckPin = 11;
const int doutPin = 12;

float calibration_factor = 344.10;
int weight = 0;

HX711 scale(doutPin, sckPin);

void init_device()
{
	Serial.begin(9600);
	scale.set_scale();
	scale.tare();
	delay(50);
}

void setup()
{
	init_device();
	Serial.println("Load Cell Testing");
}

void loop()
{
	weight = read_weight();
	Serial.println("Weight: " + String(weight) + "grams");
	delay(1000);
}

int read_weight()
{
	scale.set_scale(calibration_factor);
	return (scale.get_units(), 4);
}