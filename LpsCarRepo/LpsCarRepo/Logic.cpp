#include <iostream>
#include <vector>
#include <cmath>
#include "SharedState.h"
#include "MotorControl.h"

using namespace std;

// This helper function handles the 180-degree turns, 45-degree turns, etc.
// before moving the motors forward.
void physical_move(int target_x, int target_y) {
    float dx = target_x - car_postion.x;
    float dy = target_y - car_postion.y;

    // Calculate angle: 0 is Up (+Y), 90 is Right (+X), 180 is Down (-Y), -90 is Left (-X)
    float target_angle = atan2(dx, dy) * 180.0 / 3.14159;

    // 1. Turn the car to face the target point
    turnToAngle(target_angle);

    // 2. Move forward after turning
    moveForwardOneUnit();
}

bool is_obstacle(int x, int y)
{
    for (int i = 0; i < obstacles.size(); i++)
    {
        if (obstacles[i].x == x && obstacles[i].y == y)
        {
            return true;
        }
    }
    return false;
}

bool is_blocked(int x, int y)
{
    for (int i = 0; i < blocked.size(); i++)
    {
        if (blocked[i].x == x && blocked[i].y == y)
        {
            return true;
        }
    }
    return false;
}

int move()
{
    bool can_move_away = true;
    while (done != true)
    {
        if (car_postion.x == endpoint.x && car_postion.y == endpoint.y)
        {
            done = true;
            break;
        }

        if (!is_obstacle(car_postion.x + 1, car_postion.y) && // 1
            sqrt(pow(car_postion.x + 1 - endpoint.x, 2) + pow(car_postion.y - endpoint.y, 2)) < distance_to_end &&
            !is_blocked(car_postion.x + 1, car_postion.y) && sqrt(pow(car_postion.x + 1 - endpoint.x, 2) + pow(car_postion.y - endpoint.y, 2)) < sqrt(pow(car_postion.x + 1 - endpoint.x, 2) + pow(car_postion.y + 1 - endpoint.y, 2)))
        {
            cout << "car moved from(" << car_postion.x << "," << car_postion.y << ") to(" << car_postion.x + 1 << "," << car_postion.y << ")" << endl;
            physical_move(car_postion.x + 1, car_postion.y);
            distance_to_end = sqrt(pow(car_postion.x + 1 - endpoint.x, 2) + pow(car_postion.y - endpoint.y, 2));
            car_postion.x += 1;
            can_move_away = true;
        }
        else if (!is_obstacle(car_postion.x + 1, car_postion.y + 1) && // 1 diagnol
            sqrt(pow(car_postion.x + 1 - endpoint.x, 2) + pow(car_postion.y + 1 - endpoint.y, 2)) < distance_to_end &&
            !is_blocked(car_postion.x + 1, car_postion.y + 1))
        {
            cout << "car moved from(" << car_postion.x << "," << car_postion.y << ") to(" << car_postion.x + 1 << "," << car_postion.y + 1 << ")" << endl;
            physical_move(car_postion.x + 1, car_postion.y + 1);
            distance_to_end = sqrt(pow(car_postion.x + 1 - endpoint.x, 2) + pow(car_postion.y + 1 - endpoint.y, 2));
            car_postion.x += 1;
            car_postion.y += 1;
            can_move_away = true;
        }

        else if (!is_obstacle(car_postion.x, car_postion.y + 1) && // 2
            sqrt(pow(car_postion.x - endpoint.x, 2) + pow(car_postion.y + 1 - endpoint.y, 2)) < distance_to_end &&
            !is_blocked(car_postion.x, car_postion.y + 1) && sqrt(pow(car_postion.x - endpoint.x, 2) + pow(car_postion.y + 1 - endpoint.y, 2)) < sqrt(pow(car_postion.x - 1 - endpoint.x, 2) + pow(car_postion.y + 1 - endpoint.y, 2)))
        {
            cout << "car moved from(" << car_postion.x << "," << car_postion.y << ") to(" << car_postion.x << "," << car_postion.y + 1 << ")" << endl;
            physical_move(car_postion.x, car_postion.y + 1);
            distance_to_end = sqrt(pow(car_postion.x - endpoint.x, 2) + pow(car_postion.y + 1 - endpoint.y, 2));
            car_postion.y += 1;
            can_move_away = true;
        }
        else if (!is_obstacle(car_postion.x - 1, car_postion.y + 1) && // 2 diagnol
            sqrt(pow(car_postion.x - 1 - endpoint.x, 2) + pow(car_postion.y + 1 - endpoint.y, 2)) < distance_to_end &&
            !is_blocked(car_postion.x - 1, car_postion.y + 1))
        {
            cout << "car moved from(" << car_postion.x << "," << car_postion.y << ") to(" << car_postion.x - 1 << "," << car_postion.y + 1 << ")" << endl;
            physical_move(car_postion.x - 1, car_postion.y + 1);
            distance_to_end = sqrt(pow(car_postion.x - 1 - endpoint.x, 2) + pow(car_postion.y + 1 - endpoint.y, 2));
            car_postion.x -= 1;
            car_postion.y += 1;
            can_move_away = true;
        }
        else if (!is_obstacle(car_postion.x - 1, car_postion.y) && // 3
            sqrt(pow(car_postion.x - 1 - endpoint.x, 2) + pow(car_postion.y - endpoint.y, 2)) < distance_to_end &&
            !is_blocked(car_postion.x - 1, car_postion.y) && sqrt(pow(car_postion.x - 1 - endpoint.x, 2) + pow(car_postion.y - endpoint.y, 2)) < sqrt(pow(car_postion.x - 1 - endpoint.x, 2) + pow(car_postion.y - 1 - endpoint.y, 2)))
        {
            cout << "car moved from(" << car_postion.x << "," << car_postion.y << ") to(" << car_postion.x - 1 << "," << car_postion.y << ")" << endl;
            physical_move(car_postion.x - 1, car_postion.y);
            distance_to_end = sqrt(pow(car_postion.x - 1 - endpoint.x, 2) + pow(car_postion.y - endpoint.y, 2));
            car_postion.x -= 1;
            can_move_away = true;
        }
        else if (!is_obstacle(car_postion.x - 1, car_postion.y - 1) && // 3 diagnol
            sqrt(pow(car_postion.x - 1 - endpoint.x, 2) + pow(car_postion.y - 1 - endpoint.y, 2)) < distance_to_end &&
            !is_blocked(car_postion.x - 1, car_postion.y - 1))
        {
            cout << "car moved from(" << car_postion.x << "," << car_postion.y << ") to(" << car_postion.x - 1 << "," << car_postion.y - 1 << ")" << endl;
            physical_move(car_postion.x - 1, car_postion.y - 1);
            distance_to_end = sqrt(pow(car_postion.x - 1 - endpoint.x, 2) + pow(car_postion.y - 1 - endpoint.y, 2));
            car_postion.x -= 1;
            car_postion.y -= 1;
            can_move_away = true;
        }
        else if (!is_obstacle(car_postion.x, car_postion.y - 1) && // 4
            sqrt(pow(car_postion.x - endpoint.x, 2) + pow(car_postion.y - 1 - endpoint.y, 2)) < distance_to_end &&
            !is_blocked(car_postion.x, car_postion.y - 1) && sqrt(pow(car_postion.x - endpoint.x, 2) + pow(car_postion.y - 1 - endpoint.y, 2)) < sqrt(pow(car_postion.x + 1 - endpoint.x, 2) + pow(car_postion.y - 1 - endpoint.y, 2)))
        {
            cout << "car moved from(" << car_postion.x << "," << car_postion.y << ") to(" << car_postion.x << "," << car_postion.y - 1 << ")" << endl;
            physical_move(car_postion.x, car_postion.y - 1);
            distance_to_end = sqrt(pow(car_postion.x - endpoint.x, 2) + pow(car_postion.y - 1 - endpoint.y, 2));
            car_postion.y -= 1;
            can_move_away = true;
        }
        else if (!is_obstacle(car_postion.x + 1, car_postion.y - 1) && // 4 diagnol
            sqrt(pow(car_postion.x + 1 - endpoint.x, 2) + pow(car_postion.y - 1 - endpoint.y, 2)) < distance_to_end &&
            !is_blocked(car_postion.x + 1, car_postion.y - 1))
        {
            cout << "car moved from(" << car_postion.x << "," << car_postion.y << ") to(" << car_postion.x + 1 << "," << car_postion.y - 1 << ")" << endl;
            physical_move(car_postion.x + 1, car_postion.y - 1);
            distance_to_end = sqrt(pow(car_postion.x + 1 - endpoint.x, 2) + pow(car_postion.y - 1 - endpoint.y, 2));
            car_postion.x += 1;
            car_postion.y -= 1;
            can_move_away = true;
        }

        else
        {
            if (!is_obstacle(car_postion.x + 1, car_postion.y) && !is_blocked(car_postion.x + 1, car_postion.y) &&
                sqrt(pow(car_postion.x + 1 - endpoint.x, 2) + pow(car_postion.y - endpoint.y, 2)) < sqrt(pow(car_postion.x - endpoint.x, 2) + pow(car_postion.y + 1 - endpoint.y, 2)))
            {
                blocked.push_back({ car_postion.x, car_postion.y });
                cout << "car moved from(" << car_postion.x << "," << car_postion.y
                    << ") to(" << car_postion.x + 1 << "," << car_postion.y << ")" << endl;
                physical_move(car_postion.x + 1, car_postion.y);
                distance_to_end = sqrt(pow(car_postion.x + 1 - endpoint.x, 2) + pow(car_postion.y - endpoint.y, 2));
                car_postion.x += 1;
                can_move_away = true;
            }
            else if (!is_obstacle(car_postion.x, car_postion.y + 1) && !is_blocked(car_postion.x, car_postion.y + 1))
            {
                blocked.push_back({ car_postion.x, car_postion.y });
                cout << "car moved from(" << car_postion.x << "," << car_postion.y
                    << ") to(" << car_postion.x << "," << car_postion.y + 1 << ")" << endl;
                physical_move(car_postion.x, car_postion.y + 1);
                distance_to_end = sqrt(pow(car_postion.x - endpoint.x, 2) + pow(car_postion.y + 1 - endpoint.y, 2));
                car_postion.y += 1;
                can_move_away = true;
            }
            else if (!is_obstacle(car_postion.x - 1, car_postion.y) && !is_blocked(car_postion.x - 1, car_postion.y) &&
                sqrt(pow(car_postion.x - 1 - endpoint.x, 2) + pow(car_postion.y - endpoint.y, 2)) < sqrt(pow(car_postion.x - endpoint.x, 2) + pow(car_postion.y - 1 - endpoint.y, 2)))
            {
                blocked.push_back({ car_postion.x, car_postion.y });
                cout << "car moved from(" << car_postion.x << "," << car_postion.y
                    << ") to(" << car_postion.x - 1 << "," << car_postion.y << ")" << endl;
                physical_move(car_postion.x - 1, car_postion.y);
                distance_to_end = sqrt(pow(car_postion.x - 1 - endpoint.x, 2) + pow(car_postion.y - endpoint.y, 2));
                car_postion.x -= 1;
                can_move_away = true;
            }
            else if (!is_obstacle(car_postion.x, car_postion.y - 1) && !is_blocked(car_postion.x, car_postion.y - 1))
            {
                blocked.push_back({ car_postion.x, car_postion.y });
                cout << "car moved from(" << car_postion.x << "," << car_postion.y
                    << ") to(" << car_postion.x << "," << car_postion.y - 1 << ")" << endl;
                physical_move(car_postion.x, car_postion.y - 1);
                distance_to_end = sqrt(pow(car_postion.x - endpoint.x, 2) + pow(car_postion.y - 1 - endpoint.y, 2));
                car_postion.y -= 1;
                can_move_away = true;
            }
            else if (!is_obstacle(car_postion.x + 1, car_postion.y + 1) && !is_blocked(car_postion.x + 1, car_postion.y + 1) &&
                sqrt(pow(car_postion.x + 1 - endpoint.x, 2) + pow(car_postion.y + 1 - endpoint.y, 2)) < sqrt(pow(car_postion.x - 1 - endpoint.x, 2) + pow(car_postion.y + 1 - endpoint.y, 2)))
            {
                blocked.push_back({ car_postion.x, car_postion.y });
                cout << "car moved from(" << car_postion.x << "," << car_postion.y
                    << ") to(" << car_postion.x + 1 << "," << car_postion.y + 1 << ")" << endl;
                physical_move(car_postion.x + 1, car_postion.y + 1);
                distance_to_end = sqrt(pow(car_postion.x + 1 - endpoint.x, 2) + pow(car_postion.y + 1 - endpoint.y, 2));
                car_postion.x += 1;
                car_postion.y += 1;
                can_move_away = true;
            }
            else if (!is_obstacle(car_postion.x - 1, car_postion.y + 1) && !is_blocked(car_postion.x - 1, car_postion.y + 1))
            {
                blocked.push_back({ car_postion.x, car_postion.y });
                cout << "car moved from(" << car_postion.x << "," << car_postion.y
                    << ") to(" << car_postion.x - 1 << "," << car_postion.y + 1 << ")" << endl;
                physical_move(car_postion.x - 1, car_postion.y + 1);
                distance_to_end = sqrt(pow(car_postion.x - 1 - endpoint.x, 2) + pow(car_postion.y + 1 - endpoint.y, 2));
                car_postion.x -= 1;
                car_postion.y += 1;
                can_move_away = true;
            }
            else if (!is_obstacle(car_postion.x - 1, car_postion.y - 1) && !is_blocked(car_postion.x - 1, car_postion.y - 1) &&
                sqrt(pow(car_postion.x - 1 - endpoint.x, 2) + pow(car_postion.y - 1 - endpoint.y, 2)) < sqrt(pow(car_postion.x + 1 - endpoint.x, 2) + pow(car_postion.y - 1 - endpoint.y, 2)))
            {
                blocked.push_back({ car_postion.x, car_postion.y });
                cout << "car moved from(" << car_postion.x << "," << car_postion.y
                    << ") to(" << car_postion.x - 1 << "," << car_postion.y - 1 << ")" << endl;
                physical_move(car_postion.x - 1, car_postion.y - 1);
                distance_to_end = sqrt(pow(car_postion.x - 1 - endpoint.x, 2) + pow(car_postion.y - 1 - endpoint.y, 2));
                car_postion.x -= 1;
                car_postion.y -= 1;
                can_move_away = true;
            }
            else if (!is_obstacle(car_postion.x + 1, car_postion.y - 1) && !is_blocked(car_postion.x + 1, car_postion.y - 1))
            {
                blocked.push_back({ car_postion.x, car_postion.y });
                cout << "car moved from(" << car_postion.x << "," << car_postion.y
                    << ") to(" << car_postion.x + 1 << "," << car_postion.y - 1 << ")" << endl;
                physical_move(car_postion.x + 1, car_postion.y - 1);
                distance_to_end = sqrt(pow(car_postion.x + 1 - endpoint.x, 2) + pow(car_postion.y - 1 - endpoint.y, 2));
                car_postion.x += 1;
                car_postion.y -= 1;
                can_move_away = true;
            }
        }
    }

    distance_to_end = sqrt(pow(car_postion.x - endpoint.x, 2) + pow(car_postion.y - endpoint.y, 2));
    return 0;
}

int main()
{
    move();
    return 0;
}