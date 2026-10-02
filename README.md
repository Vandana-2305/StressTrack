# StressTrack – Wearable Stress & Posture Monitoring System

StressTrack is an **ESP32-based wearable monitoring system** designed to monitor physiological and physical parameters associated with user stress and posture.

The system collects data from a **GSR sensor** and **MPU6050 accelerometer/gyroscope**, processes the readings using the ESP32, and provides real-time feedback through an **OLED display, LED indicator, and buzzer**.

---

## 🎯 Aim

The aim of StressTrack is to develop a compact wearable system capable of:

* Monitoring changes in skin conductance using a GSR sensor
* Detecting posture deviations using an MPU6050
* Evaluating stress-related conditions based on sensor readings
* Providing real-time alerts when an abnormal condition is detected
* Displaying monitored parameters through an OLED display

---

## ✨ Features

* 🧠 Stress-related condition detection
* 🖐️ GSR-based skin conductance monitoring
* 🧍 Posture deviation detection
* 📊 Real-time sensor monitoring
* 📺 128 × 64 OLED display
* 🚨 LED and buzzer alerts
* ⚡ ESP32-based processing
* 📡 Serial Monitor output for debugging and analysis
* 🔄 Continuous monitoring at one-second intervals

---

## 🏗️ System Architecture

```text
                    ┌──────────────────────┐
                    │        ESP32         │
                    │   Main Controller    │
                    └──────────┬───────────┘
                               │
              ┌────────────────┼────────────────┐
              │                │                │
              ▼                ▼                ▼
        ┌──────────┐     ┌──────────┐    ┌──────────┐
        │ GSR      │     │ MPU6050  │    │ OLED     │
        │ Sensor   │     │ Sensor   │    │ Display  │
        └────┬─────┘     └────┬─────┘    └──────────┘
             │                │
             ▼                ▼
       Skin Conductance   Movement &
                           Posture Data
             │                │
             └───────┬────────┘
                     ▼
              ┌───────────────┐
              │ Data Analysis  │
              │ & Detection    │
              └───────┬───────┘
                      │
             ┌────────┴────────┐
             ▼                 ▼
        ┌──────────┐      ┌──────────┐
        │   LED    │      │  Buzzer  │
        │  Alert   │      │  Alert   │
        └──────────┘      └──────────┘
```

---

## 🔧 Hardware Components

| Component            | Purpose                                   |
| -------------------- | ----------------------------------------- |
| ESP32                | Main microcontroller                      |
| GSR Sensor           | Measures skin conductance                 |
| MPU6050              | Measures acceleration and gyroscope data  |
| OLED Display         | Displays real-time monitoring information |
| LED                  | Visual alert                              |
| Buzzer               | Audible alert                             |
| Jumper Wires         | Circuit connections                       |
| Power Supply/Battery | Portable power source                     |

---

## 💻 Software & Libraries

### Development Environment

* Arduino IDE
* ESP32 Board Package
* C/C++ (Arduino framework)

### Required Libraries

Install the following libraries through the Arduino IDE Library Manager:

```text
Adafruit GFX Library
Adafruit SSD1306
Adafruit MPU6050
Adafruit Unified Sensor
```

The following Arduino libraries are also used:

```text
Wire.h
```

---

## 🔌 Pin Configuration

| Component        | ESP32 Pin |
| ---------------- | --------: |
| GSR Sensor       |   GPIO 34 |
| LED              |    GPIO 2 |
| Buzzer           |   GPIO 15 |
| I²C SDA          |   GPIO 21 |
| I²C SCL          |   GPIO 22 |
| OLED I²C Address |      0x3C |

The MPU6050 and OLED communicate with the ESP32 using the **I²C communication protocol**.

---

## 🧠 Stress Detection

The current prototype uses GSR and heart-rate values to identify a stress-related condition.

The current detection logic is:

```text
IF Heart Rate > 100 BPM
AND
GSR > 2500

        ↓

Condition Detected
```

Otherwise:

```text
Normal
```

> **Note:** The current prototype uses simulated heart-rate and SpO₂ values for demonstration. Actual physiological measurements require a compatible heart-rate/SpO₂ sensor to be connected to the system.

---

## 🧍 Posture Detection

The MPU6050 provides acceleration data along the X, Y, and Z axes.

The current prototype uses the Y-axis acceleration to identify significant posture deviation.

```text
IF |Acceleration Y| > 7.0 m/s²

        ↓

Posture Deviation

ELSE

        ↓

Normal
```

This threshold can be calibrated experimentally based on the intended wearable placement and user posture.

---

## 🚨 Alert System

An alert is activated when either of the following conditions occurs:

```text
Stress Condition Detected
            OR
Posture Deviation Detected
```

When an alert occurs:

* LED turns ON
* Buzzer produces an alert signal

When the system returns to normal:

* LED turns OFF
* Buzzer remains OFF

---

## 📺 OLED Display

The OLED displays:

```text
STRESSTRACK
HR: XX BPM
SpO2: XX %
GSR: XXXX
Posture: Normal
Stress: Normal
```

The display is refreshed approximately every **1 second**.

---

## 📊 Serial Monitor

The ESP32 also sends detailed sensor information through the Serial Monitor at:

```text
Baud Rate: 115200
```

The output includes:

* Heart rate
* SpO₂
* GSR value
* Accelerometer X, Y and Z
* Gyroscope X, Y and Z
* Posture status
* Stress status

---

## 📁 Project Structure

```text
StressTrack/
│
├── firmware/
│   └── StressTrack.ino
│
├── hardware/
│   └── circuit_diagram.png
│
├── docs/
│   └── project_report.pdf
│
└── README.md
```

---

## 🚀 Getting Started

### 1. Clone the Repository

```bash
git clone <repository-url>
```

### 2. Open the Firmware

Open:

```text
firmware/StressTrack.ino
```

using the Arduino IDE.

### 3. Install Required Libraries

Install:

* Adafruit GFX Library
* Adafruit SSD1306
* Adafruit MPU6050
* Adafruit Unified Sensor

### 4. Select the ESP32 Board

In Arduino IDE:

```text
Tools → Board → ESP32 → ESP32 Dev Module
```

### 5. Connect the Hardware

Connect the sensors according to the pin configuration provided above.

### 6. Upload the Code

Select the appropriate COM port and upload the firmware to the ESP32.

### 7. Open Serial Monitor

Set the baud rate to:

```text
115200
```

The system will begin monitoring the connected sensors.

---

## 🔮 Future Enhancements

The current prototype can be extended with:

* Real heart-rate sensor integration
* Real SpO₂ sensor integration
* Improved stress classification using multiple physiological parameters
* Sensor calibration and personalized thresholds
* Machine-learning-based stress classification
* Bluetooth/Wi-Fi connectivity
* Mobile or web dashboard
* Cloud-based data storage
* Historical stress analysis
* Battery-level monitoring
* Data logging and visualization
* Personalized posture monitoring

---

## ⚠️ Current Prototype Limitations

* Heart-rate values are currently simulated.
* SpO₂ values are currently simulated.
* Stress detection uses threshold-based logic.
* Posture detection currently relies primarily on the Y-axis acceleration.
* Sensor thresholds may require calibration for different users and wearable placements.

Therefore, this prototype is intended for **educational and research purposes** and should not be considered a medical diagnostic device.

---

## 🛠️ Project Status

**Current Status:** Prototype / Working Demonstration

The ESP32 firmware successfully integrates:

* GSR monitoring
* MPU6050 motion sensing
* OLED display
* LED indication
* Buzzer alert
* Serial monitoring
* Basic stress-condition detection
* Basic posture-deviation detection

---

## 👩‍💻 Technologies Used

```text
ESP32
Arduino
C/C++
GSR Sensor
MPU6050
OLED
I²C
Embedded Systems
IoT
Sensor Data Processing
```

---

## 📜 License

This project is developed for **academic and educational purposes**.

You may modify and extend the project for learning and research purposes.
