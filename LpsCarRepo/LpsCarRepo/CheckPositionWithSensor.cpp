#include <iostream>
#include <vector>
#include <cmath>
#include "Trilateration.h"
#include "SharedState.h"

void validateAndCorrectPosition(double sensor_dist) {
    // 1. Get position from satellites
    Satellite s1 = { 1, 10, 0, 0 }; Satellite s2 = { 2, 0, 10, 0 }; Satellite s3 = { 3, -10, 0, 0 };
    s1.updateDistance(); s2.updateDistance(); s3.updateDistance();
    Point satellite_pos = calculatePosition(s1, s2, s3);

    // 2. Fuse Satellite with internal position (Average them)
    car_postion.x = (car_postion.x + satellite_pos.x) / 2.0;
    car_postion.y = (car_postion.y + satellite_pos.y) / 2.0;

    // 3. Check Ultrasonic Sensor
    // Assume sensor is on the front. Based on current_heading, where is the obstacle?
    Point expected_obs = { car_postion.x, car_postion.y + sensor_dist };

    bool found_match = false;
    for (const auto& obs : obstacles) {
        float diffX = std::abs(expected_obs.x - obs.x);
        float diffY = std::abs(expected_obs.y - obs.y);

        if (diffX <= 0.5f && diffY <= 0.5f) {
            std::cout << "Position Verified via Obstacle Detection." << std::endl;
            found_match = true;
            break;
        }
    }

    // 4. Correct position if we found a known obstacle but we were off
    if (!found_match && sensor_dist < 2.0) {
        for (const auto& obs : obstacles) {
            // If we see something close, assume it's the closest known obstacle
            // and shift our car_position to match reality.
            car_postion.y = obs.y - sensor_dist;
            std::cout << "Position Corrected based on Sensor Data!" << std::endl;
            break;
        }
    }
}