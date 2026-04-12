#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

void setupMotors();
void moveMotors(int direction); // 1: For, 2: Back, 3: Left, 4: Right, 0: Stop
void turnToAngle(float targetAngle);
void moveForwardOneUnit();

#endif