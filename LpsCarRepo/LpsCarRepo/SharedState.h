#ifndef SHARED_STATE_H
#define SHARED_STATE_H

#include "Trilateration.h"
#include <vector>

// Global variables shared across all files
extern Point car_postion;
extern Point endpoint;
extern std::vector<Point> obstacles;
extern std::vector<Point> history;
extern std::vector<Point> blocked;
extern double distance_to_end;
extern bool done;
extern float current_heading; // 0 = North, 90 = East, 180 = South, 270 = West

#endif