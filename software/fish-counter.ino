#include <HX711.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

const int sckPin = A0;
const int doutPin = A1;
const int trigPin = 2;
const int echoPin = 3;
const int servo1Pin = 9;
const int servo2Pin = 10;
const int ledPin = 13;

float calibration_factor = 300;
int weight = 0;
int distance = 0;

int totalcounter = 0;
int smallcounter = 0;
int bigcounter = 0;

bool onStatus = false;
bool weightStatus = false;

LiquidCrystal_I2C lcd(0x27, 16, 2);
HX711 scale(doutPin, sckPin);
Servo servo1;
Servo servo2;

void init_device() {
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();
  scale.set_scale(calibration_factor);
  scale.tare();
  servo1.attach(servo1Pin, 600, 2300);
  servo2.attach(servo2Pin, 600, 2300);
  delay(50);
}

void init_pin() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  delay(50);
}

void setup() {
  init_device();
  init_pin();
  lcd_show(1, 0, "Fish Counter", 1);
  lcd_show(0, 1, "by 2black0", 1000);
}

void loop() {
  on_process();
  if (onStatus) {
    onStatus = false;
    led_on();
    servo1_on();
  } else {
    led_off();
    servo1_off();
  }

  weight_process();
  if (weightStatus) {
    weightStatus = false;
    led_on();
    servo2_on();
  } else {
    led_off();
    servo2_off();
  }

  lcd_show(1, 0, "S Fish:" + String(smallcounter), 1);
  lcd_show(0, 1, "B Fish:" + String(bigcounter), 1000);
}

void on_process() {
  distance = read_ultrasonic();
  if (distance < 50) {
    onStatus = true;
    totalcounter++;
    lcd_show(1, 0, "Counter:" + String(totalcounter), 1000);
  } else {
    onStatus = false;
  }
}

void weight_process() {
  weight = read_weight();
  if (weight > 10) {
    delay(1000);
    weight = read_weight();
    if (weight >= 100) {
      weightStatus = true;
      smallcounter++;
      lcd_show(1, 0, "S Fish:" + String(smallcounter), 1000);
    } else {
      weightStatus = false;
      bigcounter++;
      lcd_show(1, 0, "B Fish:" + String(bigcounter), 1000);
    }
  }
}

int read_ultrasonic() {
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

int read_weight() {
  // scale.set_scale(calibration_factor);
  return (scale.get_units(), 1);
}

void servo1_on() {
  servo1.write(90);
  delay(1000);
}

void servo1_off() {
  servo1.write(45);
  delay(1000);
}

void servo2_on() {
  servo2.write(90);
  delay(1000);
}

void servo2_off() {
  servo2.write(45);
  delay(1000);
}

void led_on() {
  digitalWrite(ledPin, LOW);
  delay(100);
}

void led_off() {
  digitalWrite(ledPin, HIGH);
  delay(100);
}

void lcd_show(int clear, int lines, String text, int timedelay) {
  if (clear) {
    lcd.clear();
  }
  lcd.setCursor(0, lines);
  lcd.print(text);
  Serial.println(text);
  delay(timedelay);
}