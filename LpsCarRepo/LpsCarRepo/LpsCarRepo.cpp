#include <Arduino.h>
#include "SharedState.h"
#include "MotorControl.h"

// Forward declarations from other files
void pathfind();
void validateAndCorrectPosition(double ultrasonic_dist);

void setup() {
    Serial.begin(115200);
    setupMotors();
    Serial.println("System Initialized...");
}

void loop() {
    if (!done) {
        // 1. Check sensors and fuse positioning
        // (Assuming an ultrasonic sensor on pin 32)
        double sensor_reading = 1.0; // Mock 6 inches
        validateAndCorrectPosition(sensor_reading);

        // 2. Decision making
        pathfind();

        // 3. Small delay to prevent loop thrashing
        delay(500);
    }
    else {
        moveMotors(0); // Stop
    }
}