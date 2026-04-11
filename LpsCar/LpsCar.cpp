#include "Trilateration.h"
#include <iostream>

void updateCarMovement() {
    Satellite s1 = { -5, 0, 12.04 };
    Satellite s2 = { 0, 10, 13.04 };
    Satellite s3 = { 5, 0, 2.24 };

    // This file can use calculatePosition because it includes the .h
    Point carPos = calculatePosition(s1, s2, s3);

    std::cout << "Moving car to: " << carPos.x << ", " << carPos.y << std::endl;
}

int main() {
    updateCarMovement();
    return 0;
}
