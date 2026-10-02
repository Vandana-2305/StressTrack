#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

// =====================================================
// StressTrack - ESP32 Wearable Stress & Posture Monitor
// =====================================================

// -------------------- Pin Definitions ----------------
#define SDA_PIN 21
#define SCL_PIN 22

#define GSR_PIN 34
#define LED_PIN 2
#define BUZZER_PIN 15

// -------------------- OLED Configuration --------------
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDRESS 0x3C

// -------------------- Sensor Objects ------------------
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
Adafruit_MPU6050 mpu;

// -------------------- Variables -----------------------
float heartRate = 72.0;
float spo2 = 98.0;

unsigned long lastUpdate = 0;
const unsigned long UPDATE_INTERVAL = 1000;

// =====================================================
// SETUP
// =====================================================

void setup() {

  Serial.begin(115200);

  // Initialize I2C
  Wire.begin(SDA_PIN, SCL_PIN);

  // Initialize pins
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  digitalWrite(LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  // Initialize OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {

    Serial.println("OLED initialization failed!");

    while (true);
  }

  // Initialize MPU6050
  if (!mpu.begin()) {

    Serial.println("MPU6050 not detected!");

    while (true);
  }

  // Configure MPU6050
  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  // ---------------- OLED Startup Screen ----------------

  display.clearDisplay();

  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);

  display.setCursor(15, 20);
  display.println("StressTrack");

  display.setCursor(15, 35);
  display.println("Initializing...");

  display.display();

  delay(2000);

  // ---------------- Serial Startup Message ------------

  Serial.println();
  Serial.println("======================================");
  Serial.println("       STRESSTRACK MONITOR");
  Serial.println("======================================");
  Serial.println("System initialized successfully.");
  Serial.println();
}

// =====================================================
// MAIN LOOP
// =====================================================

void loop() {

  // Update every 1 second
  if (millis() - lastUpdate >= UPDATE_INTERVAL) {

    lastUpdate = millis();

    // ---------------- Read GSR ----------------

    int gsrValue = analogRead(GSR_PIN);

    // ---------------- Read MPU6050 ------------

    sensors_event_t acceleration;
    sensors_event_t gyro;
    sensors_event_t temperature;

    mpu.getEvent(
      &acceleration,
      &gyro,
      &temperature
    );

    // Accelerometer values
    float ax = acceleration.acceleration.x;
    float ay = acceleration.acceleration.y;
    float az = acceleration.acceleration.z;

    // Gyroscope values
    float gx = gyro.gyro.x;
    float gy = gyro.gyro.y;
    float gz = gyro.gyro.z;

    // ---------------- Simulated HR & SpO2 ------

    // These values are currently simulated.
    // Replace with actual sensor readings when
    // a compatible heart-rate/SpO2 sensor is added.

    heartRate = 72.0 + random(-3, 4);
    spo2 = 98.0 + random(-1, 2);

    // ---------------- Detect Posture ------------

    String posture = detectPosture(
      ax,
      ay,
      az
    );

    // ---------------- Detect Stress -------------

    String stressStatus = detectStress(
      heartRate,
      gsrValue
    );

    // ---------------- Alert System -------------

    bool alert = false;

    if (
      stressStatus == "Condition Detected" ||
      posture == "Posture Deviation"
    ) {

      alert = true;
    }

    if (alert) {

      digitalWrite(LED_PIN, HIGH);

      digitalWrite(BUZZER_PIN, HIGH);

      delay(100);

      digitalWrite(BUZZER_PIN, LOW);

    } else {

      digitalWrite(LED_PIN, LOW);
      digitalWrite(BUZZER_PIN, LOW);
    }

    // ---------------- Serial Output ------------

    printSerialData(
      heartRate,
      spo2,
      gsrValue,
      ax,
      ay,
      az,
      gx,
      gy,
      gz,
      posture,
      stressStatus
    );

    // ---------------- OLED Output --------------

    updateOLED(
      heartRate,
      spo2,
      gsrValue,
      posture,
      stressStatus
    );
  }
}

// =====================================================
// POSTURE DETECTION
// =====================================================

String detectPosture(
  float ax,
  float ay,
  float az
) {

  float tilt = abs(ay);

  if (tilt > 7.0) {

    return "Posture Deviation";

  } else {

    return "Normal";
  }
}

// =====================================================
// STRESS DETECTION
// =====================================================

String detectStress(
  float hr,
  int gsr
) {

  if (
    hr > 100 &&
    gsr > 2500
  ) {

    return "Condition Detected";

  } else {

    return "Normal";
  }
}

// =====================================================
// SERIAL MONITOR OUTPUT
// =====================================================

void printSerialData(
  float hr,
  float oxygen,
  int gsr,
  float ax,
  float ay,
  float az,
  float gx,
  float gy,
  float gz,
  String posture,
  String stressStatus
) {

  Serial.println();
  Serial.println("======================================");

  Serial.print("Heart Rate: ");
  Serial.print(hr, 1);
  Serial.println(" BPM");

  Serial.print("SpO2: ");
  Serial.print(oxygen, 1);
  Serial.println(" %");

  Serial.print("GSR: ");
  Serial.println(gsr);

  Serial.print("Accel X: ");
  Serial.print(ax, 2);
  Serial.println(" m/s2");

  Serial.print("Accel Y: ");
  Serial.print(ay, 2);
  Serial.println(" m/s2");

  Serial.print("Accel Z: ");
  Serial.print(az, 2);
  Serial.println(" m/s2");

  Serial.print("Gyro X: ");
  Serial.print(gx, 2);
  Serial.println(" rad/s");

  Serial.print("Gyro Y: ");
  Serial.print(gy, 2);
  Serial.println(" rad/s");

  Serial.print("Gyro Z: ");
  Serial.print(gz, 2);
  Serial.println(" rad/s");

  Serial.print("Posture: ");
  Serial.println(posture);

  Serial.print("Stress Status: ");
  Serial.println(stressStatus);

  Serial.println("======================================");
}

// =====================================================
// OLED DISPLAY UPDATE
// =====================================================

void updateOLED(
  float hr,
  float oxygen,
  int gsr,
  String posture,
  String stressStatus
) {

  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  // Title
  display.setCursor(0, 0);
  display.println("STRESSTRACK");

  // Heart Rate
  display.print("HR: ");
  display.print(hr, 0);
  display.println(" BPM");

  // SpO2
  display.print("SpO2: ");
  display.print(oxygen, 0);
  display.println(" %");

  // GSR
  display.print("GSR: ");
  display.println(gsr);

  // Posture
  display.print("Posture: ");
  display.println(posture);

  // Stress
  display.print("Stress: ");
  display.println(stressStatus);

  display.display();
}
