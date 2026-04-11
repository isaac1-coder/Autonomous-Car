#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Forward Declaration updated to include the double parameter
void check_for_obsticals(double distance_to_obstacle);

struct Point {
    int x;
    int y;
};

Point car_postion = { 0, 0 };
Point endpoint = { 0, 3 };
Point obstacle_location;
vector<Point> obstacles = { {0, 1} };

int main() {
    // You need to define this variable before passing it
    double distance_to_obstacle = 1.5;

    // Call the file that uses the ultrasonic sensor to scan and have it return the things it detects and there distances from its currecnt postition
    // You will have to set up the file calling which isnt too hard
    // Next call the function that checks the hard coded obsticals
    check_for_obsticals(distance_to_obstacle);
    return 0;
}

void check_for_obsticals(double distance_to_obstacle) {
    Point obstical_difference;
    obstacle_location.x = car_postion.x;
    obstacle_location.y = car_postion.y + (int)distance_to_obstacle;
    for (int i = 0; i < obstacles.size(); i++) {
        // Calculate the absolute difference for both axes
        float diffX = std::abs(obstacle_location.x - obstacles[i].x);
        float diffY = std::abs(obstacle_location.y - obstacles[i].y);

        if (diffX <= 1.0f && diffY <= 1.0f) {
            // The obstacle is within 1 unit in both X and Y (a 2x2 square area)
            std::cout << "Obstacle " << i << " is close!" << std::endl;
        }
    }

    //obstical_difference.x = obstacle_location.x - obstacles


}