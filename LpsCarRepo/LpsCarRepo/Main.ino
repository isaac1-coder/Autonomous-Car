#include <Arduino.h>
#include "SharedState.h"
#include "MotorControl.h"

// Forward declarations
int move(); 
void validateAndCorrectPosition(double sensor_dist);

void setup() {
    Serial.begin(115200);
    setupMotors();
    
    // Initial Sensor Check
    validateAndCorrectPosition(1.0); 
    
    // Start Pathfinding
    move();
}

void loop() {
    // Everything is handled in move()
}