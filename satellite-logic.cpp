#include "Trilateration.h"
#include <cmath>

Point calculatePosition(Satellite s1, Satellite s2, Satellite s3) {
    double A = 2 * s2.x - 2 * s1.x;
    double B = 2 * s2.y - 2 * s1.y;
    double C = pow(s1.r, 2) - pow(s2.r, 2) - pow(s1.x, 2) + pow(s2.x, 2) - pow(s1.y, 2) + pow(s2.y, 2);

    double D = 2 * s3.x - 2 * s2.x;
    double E = 2 * s3.y - 2 * s2.y;
    double F = pow(s2.r, 2) - pow(s3.r, 2) - pow(s2.x, 2) + pow(s3.x, 2) - pow(s2.y, 2) + pow(s3.y, 2);

    double determinant = (A * E) - (B * D);

    if (std::abs(determinant) < 1e-9) {
        return { 0.0, 0.0 };
    }

    double finalX = (C * E - F * B) / determinant;
    double finalY = (A * F - D * C) / determinant;

    return { finalX, finalY };
}