#include <iostream>
#include <vector>
#include <cmath>
#include <Arduino.h>
#include "Trilateration.h"
#include "SharedState.h"

void validateAndCorrectPosition(double sensor_dist) {
    // 1. Where do we think we are from Satellites?
    Satellite s1 = { 1, 10, 0, 0 }; Satellite s2 = { 2, 0, 10, 0 }; Satellite s3 = { 3, -10, 0, 0 };
    s1.updateDistance(); s2.updateDistance(); s3.updateDistance();
    Point satellite_pos = calculatePosition(s1, s2, s3);

    // 2. Fusing Satellite data with current Tracked Position (Dead Reckoning/Gyro)
    // We average them to smooth out GPS noise
    car_postion.x = (car_postion.x + satellite_pos.x) / 2.0;
    car_postion.y = (car_postion.y + satellite_pos.y) / 2.0;

    // 3. Where do we THINK the obstacle is based on car_postion?
    // We adjust the check based on the direction the car is facing
    Point expected_obs;
    if (current_heading == 0) expected_obs = { car_postion.x, car_postion.y + sensor_dist };
    else if (current_heading == 90) expected_obs = { car_postion.x + sensor_dist, car_postion.y };
    else if (current_heading == 180) expected_obs = { car_postion.x, car_postion.y - sensor_dist };
    else expected_obs = { car_postion.x - sensor_dist, car_postion.y };

    bool found_match = false;
    for (const auto& obs : obstacles) {
        float diffX = std::abs(expected_obs.x - obs.x);
        float diffY = std::abs(expected_obs.y - obs.y);

        if (diffX <= 0.8f && diffY <= 0.8f) {
            std::cout << "Position Verified via Sensor match." << std::endl;
            found_match = true;
            break;
        }
    }

    // 4. Correction Logic: If no obstacle is where we thought, assume the sensor caught
    // the NEAREST hardcoded obstacle and "Snap" our car_position to it.
    if (!found_match && sensor_dist < 2.0) {
        for (const auto& obs : obstacles) {
            // If facing North, correct Y based on the known wall
            if (current_heading == 0) {
                car_postion.y = obs.y - sensor_dist;
            }
            // If facing East, correct X based on the known wall
            else if (current_heading == 90) {
                car_postion.x = obs.x - sensor_dist;
            }
            std::cout << "Position Corrected based on known Obstacle Snapping!" << std::endl;
            break;
        }
    }
}