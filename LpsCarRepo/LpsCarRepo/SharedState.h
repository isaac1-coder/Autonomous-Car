#ifndef SHARED_STATE_H
#define SHARED_STATE_H

#include "Trilateration.h"
#include <vector>

// Define variables globally so every file can see them
extern Point car_postion;
extern Point endpoint;
extern std::vector<Point> obstacles;
extern std::vector<Point> blocked;
extern double distance_to_end;
extern bool done;
extern float current_heading; // Track the car's angle (0-360)

#endif