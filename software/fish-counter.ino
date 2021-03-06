// -----
// coded by 2black0
// -----

#include <HX711_ADC.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

const int sckPin = A0;
const int doutPin = A1;
const int trigPin = 2;
const int echoPin = 3;
const int servo1Pin = 9;
const int servo2Pin = 10;
const int ledPin = 13;

float calibrationValue = 1.0; // ganti dengan new calibration value
static boolean newDataReady = 0;
const int serialPrintInterval = 0;
long t;

float weight = 0;
int distance = 0;

int totalcounter = 0;
int smallcounter = 0;
int bigcounter = 0;

static boolean onStatus = 0;
bool weightStatus = false;

LiquidCrystal_I2C lcd(0x27, 16, 2);
HX711_ADC LoadCell(doutPin, sckPin);
Servo servo1;
Servo servo2;

void init_hx711() {
  LoadCell.begin();
  long stabilizingtime = 2000;
  boolean _tare = false;
  LoadCell.start(stabilizingtime, _tare);
  if (LoadCell.getTareTimeoutFlag() || LoadCell.getSignalTimeoutFlag()) {
    Serial.println("Check LoadCell");
    lcd_show(1, 0, "Check LoadCell", 500);
    while (1)
      ;
  } else {
    LoadCell.setCalFactor(calibrationValue);
    Serial.println("LoadCell OK");
    lcd_show(1, 0, "LoadCell OK", 500);
  }
}

void init_device() {
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();
  servo1.attach(servo1Pin, 600, 2300);
  servo2.attach(servo2Pin, 600, 2300);
  init_hx711();
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
  Serial.println("Fish Counter by 2black0");
  lcd_show(1, 0, "Fish Counter", 1);
  lcd_show(0, 1, "by 2black0", 1000);
}

void loop() {
  distance = read_ultrasonic();
  Serial.println("Distance:" + String(distance));
  if (distance <= 25) {
    onStatus = true;
    distance = 0;
    totalcounter++;
    // led_on();
    // servo1_on();
    Serial.println("Counter:" + String(totalcounter));
  } // else {
    // led_off();
    // servo1_off();
  //}

  if (LoadCell.update())
    newDataReady = true;

  if (newDataReady && onStatus) {
    if (millis() > t + serialPrintInterval) {
      weight = LoadCell.getData();
      newDataReady = 0;
      onStatus = 0;
      t = millis();

      if (weight < 8538676) {
        smallcounter++;
        led_on();
        servo2_on();
        Serial.println("Weight <= 200 gram");
        Serial.println("S Fish:" + String(smallcounter));
        led_off();
      } else if (weight >= 8538676) {
        bigcounter++;
        led_on();
        servo2_off();
        Serial.println("Weight > 200 gram");
        Serial.println("B Fish:" + String(bigcounter));
        led_off();
      }
    }
  }

  lcd_show(1, 0, "Total:" + String(totalcounter), 1);
  lcd_show(0, 1, "S:" + String(smallcounter) + " B:" + String(bigcounter), 100);
}

/*void on_process() {
  Serial.println("On Process");
  distance = read_ultrasonic();
  Serial.println("Distance:" + String(distance));
  lcd_show(1, 0, "Distance:" + String(distance), 1000);
  if (distance < 50) {
    onStatus = true;
    totalcounter++;
    Serial.println("Counter:" + String(totalcounter));
    lcd_show(1, 0, "Counter:" + String(totalcounter), 1000);
  } else {
    onStatus = false;
  }
}

void weight_process() {
  Serial.println("Weight Process");
  weight = read_weight();
  Serial.println("Weight:" + String(weight));
  lcd_show(1, 0, "Weight:" + String(weight), 1000);
  if (weight >= 100) {
    weightStatus = true;
    smallcounter++;
    Serial.println("S Fish:" + String(smallcounter));
    lcd_show(1, 0, "S Fish:" + String(smallcounter), 1000);
  } else {
    weightStatus = false;
    bigcounter++;
    Serial.println("B Fish:" + String(bigcounter));
    lcd_show(1, 0, "B Fish:" + String(bigcounter), 1000);
  }
}*/

int read_ultrasonic() {
  Serial.println("Read Distance");
  long duration;
  int distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  return distance;
}

/*int read_weight() {
  Serial.println("Read Weight");
  if (newDataReady) {
    if (millis() > t + serialPrintInterval) {
      float i = LoadCell.getData();
      newDataReady = 0;
      t = millis();
      return i;
    }
  }
}*/

void servo1_on() {
  Serial.println("Servo 1 ON");
  servo1.write(90);
  delay(1000);
}

void servo1_off() {
  Serial.println("Servo 1 OFF");
  servo1.write(45);
  delay(1000);
}

void servo2_on() {
  Serial.println("Servo 2 ON");
  servo2.write(90);
  delay(1000);
}

void servo2_off() {
  Serial.println("Servo 2 OFF");
  servo2.write(45);
  delay(1000);
}

void led_on() {
  Serial.println("Led ON");
  digitalWrite(ledPin, LOW);
  // delay(100);
}

void led_off() {
  Serial.println("Led OFF");
  digitalWrite(ledPin, HIGH);
  // delay(100);
}

void lcd_show(int clear, int lines, String text, int timedelay) {
  if (clear) {
    lcd.clear();
  }
  lcd.setCursor(0, lines);
  lcd.print(text);
  delay(timedelay);
}