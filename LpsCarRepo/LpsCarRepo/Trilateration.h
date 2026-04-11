#ifndef LPSCAR_TRILATERATION_H
#define LPSCAR_TRILATERATION_H

struct Point {
    double x;
    double y;
};

struct Satellite {
    double x;
    double y;
    double r;
};

// Function declaration only; implementation is in satellite-logic.cpp
Point calculatePosition(Satellite s1, Satellite s2, Satellite s3);

#endif // LPSCAR_TRILATERATION_H
