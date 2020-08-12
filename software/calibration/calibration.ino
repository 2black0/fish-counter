#include <HX711.h>

const int sckPin = 11;
const int doutPin = 12;

HX711 scale(doutPin, sckPin);

float calibration_factor = 650;
int GRAM;

void setup() {
  Serial.begin(9600);
  Serial.println(
      "tekan a,s,d,f untuk menaikan calibration_factor ke 10,100,1000,10000");
  Serial.println(
      "tekan z,x,c,v untuk menurunkan calibration_factor ke 10,100,1000,10000");
  Serial.println("Tekan T untuk Tare");
  scale.set_scale();
  scale.tare();
  long zero_factor = scale.read_average();
  Serial.print("Zero factor: ");
  Serial.println(zero_factor);
  delay(1000);
}

void loop() {
  scale.set_scale(calibration_factor);
  GRAM = scale.get_units(), 4;
  Serial.print("Reading: ");
  Serial.print(GRAM);
  Serial.print(" Gram");
  Serial.print(" calibration_factor: ");
  Serial.print(calibration_factor);
  Serial.println();

  if (Serial.available()) {
    char temp = Serial.read();
    if (temp == '+' || temp == 'a')
      calibration_factor += 0.1;
    else if (temp == '-' || temp == 'z')
      calibration_factor -= 0.1;
    else if (temp == 's')
      calibration_factor += 10;
    else if (temp == 'x')
      calibration_factor -= 10;
    else if (temp == 'd')
      calibration_factor += 100;
    else if (temp == 'c')
      calibration_factor -= 100;
    else if (temp == 'f')
      calibration_factor += 1000;
    else if (temp == 'v')
      calibration_factor -= 1000;
    else if (temp == 't')
      scale.tare();
  }
}

/*
Silahkan Upload programnya. Kemudian buka Serial Monitor. Nah disini kamu harus
siapkan beban yang kamu tau ukuran beratnya. Misalkan kamu pake Batu yang
beratnya 300 gram. Nah tinggal kamu simpan batunya. Kemudian cek di Serial
Monitor.

Jika ternyata beratnya kurang atau lebih dari 300 gram. Kamu tinggal turunkan
atau naikan Calibration Factor nya dengan mengirim a,s,d,f atau z,x,c,v lalu
Send. Jika sudah pas, simpan nilai Calibration Factor nya untuk nanti dimasukkan
ke program utama.
*/