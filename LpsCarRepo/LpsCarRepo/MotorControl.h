#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

void setupMotors();
void moveMotors(int direction);
void turnToAngle(float targetAngle);
void moveForwardOneUnit();

#endif