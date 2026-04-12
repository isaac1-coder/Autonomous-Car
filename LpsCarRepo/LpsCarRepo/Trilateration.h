#ifndef TRILATERATION_H
#define TRILATERATION_H

#include <vector>
#include <cmath>

struct Point {
    double x;
    double y;
};

class Satellite {
public:
    int sat_num;
    double x;
    double y;
    double r;
    void updateDistance();
};

double send_pulse(int sat_num);
Point calculatePosition(Satellite s1, Satellite s2, Satellite s3);

#endif