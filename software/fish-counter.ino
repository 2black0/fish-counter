#include <HX711.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <ezButton.h>

const int btnPin = A3;
const int trigPin = 2;
const int echoPin = 3;
const int servo1Pin = 9;
const int servo2Pin = 10;
const int sckPin = 11;
const int doutPin = 12;
const int ledPin = 13;

float calibration_factor = 344.10; // ganti dengan nilai kalibrasi
int weight = 0;
int distance = 0;

int totalcounter = 0;
int smallcounter = 0;
int bigcounter = 0;

bool startStatus = false;
bool resetStatus = false;
bool onStatus = false;
bool weightStatus = false;

LiquidCrystal_I2C lcd(0x27, 16, 2);
HX711 scale(doutPin, sckPin);
ezButton button(btnPin);
Servo servo1;
Servo servo2;

void init_device() {
  Serial.begin(9600);
  lcd.init();
  button.setDebounceTime(50);
  scale.set_scale();
  scale.tare();
  servo1.attach(servo1Pin, 600, 2300);
  servo2.attach(servo2Pin, 600, 2300);
  delay(50);
}

void init_pin() {
  pinMode(btnPin, INPUT);
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
  button.loop();
  if (button.isReleased()) {
    startStatus = !startStatus;
  }

  if (startStatus) {
    on_process();
    if (onStatus) {
      onStatus = false;
      servo1_on();
    } else {
      servo1_off();
    }
    weight_process();
    if (weightStatus) {
      weightStatus = false;
      servo2_on();
    } else {
      servo2_off();
    }
  } else {
    stop_process();
  }
}

void reset_var() {
  if (!resetStatus) {
    lcd_show(1, 0, "Clear All Var", 500);
    totalcounter = 0;
    smallcounter = 0;
    bigcounter = 0;

    startStatus = false;
    resetStatus = true;
    onStatus = false;
    weightStatus = false;
  }
}

void on_process() {
  reset_var();
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
    delay(2500);
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

int read_weight() {
  scale.set_scale(calibration_factor);
  return (scale.get_units(), 4);
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

void lcd_show(int clear, int lines, String text, int timedelay) {
  if (clear) {
    lcd.clear();
  }
  lcd.setCursor(0, lines);
  lcd.print(text);
  Serial.println(text);
  delay(timedelay);
}

void stop_process() {
  resetStatus = false;
  lcd_show(1, 0, "Press Button", 1);
  lcd_show(0, 1, "to Start", 2000);

  lcd_show(1, 0, "S Fish:" + String(smallcounter), 1);
  lcd_show(0, 1, "B Fish:" + String(bigcounter), 1000);
}