#include "Trilateration.h"
#include <Arduino.h>

double send_pulse(int sat_num) {
    // Simulated radio signal for ESP32
    return 2.0 + (sat_num * 1.2) + (random(-10, 10) / 100.0);
}

Point calculatePosition(Satellite s1, Satellite s2, Satellite s3) {
    double A = 2 * s2.x - 2 * s1.x;
    double B = 2 * s2.y - 2 * s1.y;
    double C = pow(s1.r, 2) - pow(s2.r, 2) - pow(s1.x, 2) + pow(s2.x, 2) - pow(s1.y, 2) + pow(s2.y, 2);
    double D = 2 * s3.x - 2 * s2.x;
    double E = 2 * s3.y - 2 * s2.y;
    double F = pow(s2.r, 2) - pow(s3.r, 2) - pow(s2.x, 2) + pow(s3.x, 2) - pow(s2.y, 2) + pow(s3.y, 2);

    double det = (A * E) - (B * D);
    if (std::abs(det) < 1e-9) return { 0.0, 0.0 };

    double x = (C * E - F * B) / det;
    double y = (A * F - D * C) / det;
    return { x, y };
}

void Satellite::updateDistance() {
    this->r = send_pulse(this->sat_num);
}