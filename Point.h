//
// Created by alon on 15/11/16.
//
#include <iostream>

#ifndef EX1_TIHNUT_POINT_H
#define EX1_TIHNUT_POINT_H

using namespace std;

/**
 * class Point have a cordinations and functions of Point.
 */
class Point {
private:
    int x;
    int y;
public:

    Point(int x=0, int y=0);

    Point(Point *p1);

    int getX() const;

    int getY() const;

    bool operator==(const Point &point2);

    friend ostream &operator<<(std::ostream &os, const Point &p);
};

#endif //EX1_TIHNUT_POINT_H
