#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void init_device()
{
	Serial.begin(9600);
	lcd.begin();
	delay(50);
}

void setup()
{
	init_device();
	lcd_show(1, 0, "LCD Testing", 1000);
}

void loop()
{
	for (int i = 0; i < 10; i++)
	{
		lcd_show(1, 0, "Counter:", 1);
		lcd_show(0, 1, String(i), 1000);
	}
}

void lcd_show(int clear, int lines, String text, int timedelay)
{
	if (clear)
	{
		lcd.clear();
	}
	lcd.setCursor(0, lines);
	lcd.print(text);
	Serial.println(text);
	delay(timedelay);
}
