# 🐟 Fish Counter – Arduino-based Smart Classifier

A smart **fish counting and classification system** using **Arduino**, capable of:

- Detecting passing fish using an ultrasonic sensor
- Measuring fish weight using a load cell (HX711)
- Automatically classifying fish as **small** or **big**
- Operating servo arms for sorting
- Displaying status on an **I2C LCD 16x2**
- Visual feedback using an onboard **LED**

---

## 📦 Project Structure

```

fish-counter/
├── hardware/
│   ├── fish-counter-circuit\_bb.png    # Breadboard layout (Fritzing)
│   └── fish-counter-circuit.fzz        # Fritzing source file
├── software/
│   ├── calibration/                    # HX711 calibration sketch
│   │   └── calibration.ino
│   ├── fish-counter.ino                # Main program
│   ├── library/                        # Arduino libraries (ZIP)
│   │   ├── HX711\_ADC-master.zip
│   │   ├── HX711-master.zip
│   │   ├── button-master.zip
│   │   ├── arduino-lib-hc-sr04-master.zip
│   │   └── Arduino-LiquidCrystal-I2C-library-master.zip
│   └── testing/                        # Component-wise testing sketches
│       ├── button/             └── button.ino
│       ├── i2c-scan/           └── i2c-scan.ino
│       ├── lcd/                └── lcd.ino
│       ├── led/                └── led.ino
│       ├── loadcell/           └── loadcell.ino
│       ├── loadcell-t/         └── loadcell-t.ino
│       ├── servo/              └── servo.ino
│       └── ultrasonic/         └── ultrasonic.ino
├── LICENSE
└── README.md

```

---

## 🛠️ Hardware Requirements

| Component             | Function                               |
|----------------------|----------------------------------------|
| Arduino Uno / Nano   | Main microcontroller                   |
| HX711 Load Cell Amp  | Measures fish weight                   |
| Load Cell 1kg/5kg    | Sensing fish load                      |
| Ultrasonic Sensor    | Detect fish presence (entry trigger)   |
| Servo Motor x2       | Control sorting gates                  |
| I2C LCD 16x2         | Visual display for counters & status   |
| Push Button (optional)| Calibration/testing interface         |
| LED                  | Activity indicator                     |
| Resistors, jumpers, breadboard or PCB |

---

## 🔌 Pin Mapping

| Arduino Pin  | Connected To           | Description                |
|--------------|------------------------|----------------------------|
| A0           | HX711 SCK              | Load cell clock            |
| A1           | HX711 DOUT             | Load cell data             |
| 2            | Ultrasonic TRIG        | Trigger for distance       |
| 3            | Ultrasonic ECHO        | Echo input for distance    |
| 9            | Servo Motor 1          | For gate/arm movement      |
| 10           | Servo Motor 2          | For gate/arm movement      |
| 13           | LED                    | Onboard or external LED    |
| I2C (A4/A5)  | LCD 16x2               | I2C lines for display      |

---

## 🧠 Features

- 🧮 **Fish Counter**: Increments total count when fish passes ultrasonic sensor
- ⚖️ **Classification**:
  - If weight `< threshold` → counted as **small fish**
  - If weight `>= threshold` → counted as **big fish**
- 🐟 **Servo Sorting**:
  - Activates servo motors to sort small vs big fish
- 🖥️ **LCD Output**:
  - First line: total count
  - Second line: S: small count, B: big count
- 💡 **LED Feedback**: LED blinks when fish is classified

---

## 🔧 Calibration

1. Run `calibration/calibration.ino`
2. Follow serial monitor instructions to get raw HX711 value
3. Replace this line in `fish-counter.ino` with your calibration factor:

```cpp
float calibrationValue = YOUR_VALUE; // Replace with real calibration
```

---

## 🧪 Sample Serial Monitor Output

```txt
Fish Counter by 2black0
Distance: 12
Counter: 1
Weight <= 200 gram
S Fish: 1
---
Distance: 11
Counter: 2
Weight > 200 gram
B Fish: 1
```

---

## 📋 Libraries Used

Make sure to install or extract the following Arduino libraries:

* **HX711_ADC**
* **LiquidCrystal_I2C**
* **Servo**
* **button** (if used)
* **Ultrasonic**

All are available in `/software/library/` as `.zip` files.

---

## 🎯 How It Works

1. **Fish passes** under ultrasonic → counted
2. **Load cell** measures the fish weight
3. **If small**, servo2 opens (small bin)
4. **If big**, servo2 remains default (big bin)
5. **LCD** shows updated counts in real time

---

## 🧑‍💻 Author

Created by **2black0 (Ardy Seto)**
For automation and embedded systems education.

---

## 📜 License

This project is licensed under the MIT License – see the [LICENSE](LICENSE) file for details.