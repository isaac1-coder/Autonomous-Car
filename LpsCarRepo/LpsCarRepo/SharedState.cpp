#include "SharedState.h"

Point car_postion = { 0, 0 };
Point endpoint = { 0, 3 };
std::vector<Point> obstacles = { {0,1}, {2, 0} };
std::vector<Point> blocked;
double distance_to_end = 3.0;
bool done = false;
float current_heading = 0.0;