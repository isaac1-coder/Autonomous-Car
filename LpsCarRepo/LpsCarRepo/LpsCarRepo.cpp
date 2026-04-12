#include "Trilateration.h"
#include <iostream>

void updateCarMovement() {
    Satellite s1 = { 6, 0, -1 };
    Satellite s2 = { 0, 21, -1 };
    Satellite s3 = { -7, 0, -1 };
    s1.updateDistance();
    s2.updateDistance();
    s3.updateDistance();
    // This file can use calculatePosition because it includes the .h
    Point carPos = calculatePosition(s1, s2, s3);

    std::cout << " car : " << carPos.x << ", " << carPos.y << std::endl;
}

int main() {
    updateCarMovement();
    return 0;
}
