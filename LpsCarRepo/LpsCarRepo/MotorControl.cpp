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

    // Normalize to -180 to 180
    while (angleDiff > 180) angleDiff -= 360;
    while (angleDiff < -180) angleDiff += 360;

    if (abs(angleDiff) < 5) return;

    // Turn right or left depending on shortest path
    if (angleDiff > 0) {
        // Turn Right
        analogWrite(L_FOR, 200); digitalWrite(L_BACK, LOW);
        digitalWrite(R_FOR, LOW); analogWrite(R_BACK, 200);
    }
    else {
        // Turn Left
        digitalWrite(L_FOR, LOW); analogWrite(L_BACK, 200);
        analogWrite(R_FOR, 200); digitalWrite(R_BACK, LOW);
    }

    // Time based on how many degrees we need to turn
    delay(abs(angleDiff) * 10);

    // Stop
    digitalWrite(L_FOR, LOW); digitalWrite(L_BACK, LOW);
    digitalWrite(R_FOR, LOW); digitalWrite(R_BACK, LOW);

    current_heading = targetAngle;
}

void moveForwardOneUnit() {
    // Move Forward
    analogWrite(L_FOR, 210); digitalWrite(L_BACK, LOW);
    analogWrite(R_FOR, 210); digitalWrite(R_BACK, LOW);

    delay(1000); // Time to move 6 inches

    // Stop
    digitalWrite(L_FOR, LOW); digitalWrite(R_FOR, LOW);
}