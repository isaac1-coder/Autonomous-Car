#ifndef LPSCAR_TRILATERATION_H
#define LPSCAR_TRILATERATION_H

#include <cmath>

// Simulated radio pulse function (forward declaration must appear before use)
double send_pulse(int sat_num);

struct Point {
    double x;
    double y;
};

class Satellite {
public:
    int sat_num;
    double x;
    double y;
    double r; // The distance value used by the math logic

    // Updates 'r' based on the simulated pulse/signal strength
    void updateDistance() {
        this->r = send_pulse(this->sat_num);
    }
};

// The math logic
Point calculatePosition(Satellite s1, Satellite s2, Satellite s3);

#endif