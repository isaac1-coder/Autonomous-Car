#include <Arduino.h>
#include "SharedState.h"

const int L_FOR = 26;
const int L_BACK = 27;
const int R_FOR = 14;
const int R_BACK = 12;

void setupMotors() {
    pinMode(L_FOR, OUTPUT);
    pinMode(L_BACK, OUTPUT);
    pinMode(R_FOR, OUTPUT);
    pinMode(R_BACK, OUTPUT);
}

void turnToAngle(float targetAngle) {
    float angleDiff = targetAngle - current_heading;

    // Normalize angle
    while (angleDiff > 180) angleDiff -= 360;
    while (angleDiff < -180) angleDiff += 360;

    if (abs(angleDiff) < 5) return; // Close enough

    // If angle is positive, turn Right. If negative, turn Left.
    if (angleDiff > 0) {
        // Physical Turn Right Logic
        analogWrite(L_FOR, 200); digitalWrite(L_BACK, LOW);
        digitalWrite(R_FOR, LOW); analogWrite(R_BACK, 200);
    }
    else {
        // Physical Turn Left Logic
        digitalWrite(L_FOR, LOW); analogWrite(L_BACK, 200);
        analogWrite(R_FOR, 200); digitalWrite(R_BACK, LOW);
    }

    delay(abs(angleDiff) * 10); // Simulated time to reach angle
    digitalWrite(L_FOR, LOW); digitalWrite(R_FOR, LOW);
    current_heading = targetAngle;
}

void moveForwardOneUnit() {
    analogWrite(L_FOR, 210);
    analogWrite(R_FOR, 210);
    delay(1000); // Time to move one grid unit (6 inches)
    digitalWrite(L_FOR, LOW);
    digitalWrite(R_FOR, LOW);
}