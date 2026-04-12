#include "Trilateration.h"
#include <cmath>
#include <random>
#include <ctime>
#include <chrono>
#include <algorithm>

// Global random engine (seed it once in your main setup)
std::default_random_engine generator(time(0));

double send_pulse(int sat_num) {
    // 1. Define the "True" distance (Where the car actually is)
    // Simulate a moving car and different satellite geometry so distances vary
    // over time and between satellites instead of being constant.
    double timeSeconds = std::chrono::duration<double>(
        std::chrono::system_clock::now().time_since_epoch()).count();

    // Base distance depends on satellite id so different sats report different
    // baseline distances. A sinusoidal term simulates movement over time.
    double base = 3.0 + (sat_num % 4) * 1.2; // 3.0, 4.2, 5.4, 6.6 ...
    double amplitude = 1.8; // how much the car moves back/forth
    double true_dist = base + amplitude * std::sin(0.5 * timeSeconds + sat_num);

    // 2. Add "Noise" (Interference)
    // Mean of 0, standard deviation of 0.5 meters
    std::normal_distribution<double> noise(0.0, 0.5);
    double interference = noise(generator);

    // 3. Environmental Path Loss (Signal Drop)
    // As sat_num changes, some sats have "weaker" antennas
    double signal_quality = (sat_num % 2 == 0) ? 1.0 : 1.15;

    double simulated_dist = (true_dist + interference) * signal_quality;

    // Safety check: distance can't be negative
    return std::max(0.1, simulated_dist);
}
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

    return { std::round(finalX), std::round(finalY) };
}