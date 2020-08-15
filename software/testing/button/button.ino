#include <ezButton.h>

const int btnPin = 13;
bool startStatus = false;

ezButton button(btnPin);

void init_device() {
  Serial.begin(9600);
  button.setDebounceTime(50);
  delay(50);
}

void init_pin() { pinMode(btnPin, INPUT); }

void setup() {
  init_device();
  init_pin();
  Serial.println("Button Testing");
}

void loop() {
  button.loop();
  if (button.isPressed())
    Serial.println("The button is pressed");

  if (button.isReleased())
    Serial.println("The button is released");
}