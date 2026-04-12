#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

// --- CONFIG ---
const float METERS_PER_UNIT = 0.1524; 
const float TILT_LIMIT = 0.85;       
const float ACCEL_DEADZONE = 0.35;    

float posX = 0, posY = 0, velX = 0, velY = 0;
float offsetX = 0, offsetY = 0;
unsigned long lastTime;

void setup() {
  Serial.begin(115200);
  Wire.begin(23, 22);
  if (!mpu.begin()) { while (1) yield(); }

  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
  mpu.setFilterBandwidth(MPU6050_BAND_44_HZ);

  Serial.println("CALIBRATING... STAY STILL");
  delay(1000);
  for(int i = 0; i < 200; i++) {
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);
    // We calibrate based on how the sensor is actually oriented
    offsetX += a.acceleration.y; // Swapping here too
    offsetY += a.acceleration.x; 
    delay(5);
  }
  offsetX /= 200; offsetY /= 200;
  
  pinMode(26, OUTPUT); pinMode(27, OUTPUT);
  pinMode(14, OUTPUT); pinMode(12, OUTPUT);
  
  lastTime = millis();
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  unsigned long currentTime = millis();
  float dt = (currentTime - lastTime) / 1000.0;
  lastTime = currentTime;

  // 1. TILT CHECK
  bool extremeTilt = (abs(g.gyro.x) > TILT_LIMIT || abs(g.gyro.y) > TILT_LIMIT);

  if (!extremeTilt) {
    // 2. SWAP X AND Y HERE
    // We assign sensor Y to our code's X, and sensor X to our code's Y
    float cleanX = a.acceleration.y - offsetX; 
    float cleanY = a.acceleration.x - offsetY;

    float filterX = (abs(cleanX) < ACCEL_DEADZONE) ? 0 : cleanX;
    float filterY = (abs(cleanY) < ACCEL_DEADZONE) ? 0 : cleanY;

    // Friction logic (stops the "race")
    if (filterX == 0) velX *= 0.8; else velX += filterX * dt;
    if (filterY == 0) velY *= 0.8; else velY += filterY * dt;

    posX += velX * dt;
    posY += velY * dt;
  } else {
    velX = 0; velY = 0; // Freeze on tilt
  }

  // 3. CONVERT TO 0.5 UNITS
  float displayX = round((posX / METERS_PER_UNIT) * 2.0) / 2.0;
  float displayY = round((posY / METERS_PER_UNIT) * 2.0) / 2.0;

  Serial.print("Units_X: "); Serial.print(displayX, 1);
  Serial.print(" | Units_Y: "); Serial.print(displayY, 1);
  if (extremeTilt) Serial.print(" [TILT]");
  Serial.println();

  // --- MOVEMENT CONTROL ---
  if (displayX < 1.0) { 
    digitalWrite(26, HIGH); digitalWrite(27, LOW);
    digitalWrite(14, HIGH); digitalWrite(12, LOW);
  } else {
    digitalWrite(26, LOW); digitalWrite(27, LOW);
    digitalWrite(14, LOW); digitalWrite(12, LOW);
  }

  delay(20);
}