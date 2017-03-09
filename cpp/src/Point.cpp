#include "Point.h"

//
// Created by alon on 15/11/16.
//
using namespace std;

/**
 * the c-tor of the Point.
 * @param x1
 * @param y2
 * @return nothing.
 */
Point::Point(int x1, int y2) {
    x = x1;
    y = y2;
}

/**
 * the second c-tor of the Point.
 * @param p1
 * @return nothing.
 */
Point::Point(Point *p1) {
    x = p1->getX();
    y = p1->getY();
}

/**
 * return the x value of the Point.
 * @return x.
 */
int Point::getX() const {
    return this->x;
}

/**
 * return the y value of the Point.
 * @return y.
 */
int Point::getY() const {
    return this->y;
}

/**
 * operator for check of 2 points are equal.
 * @param point2.
 * @return bool.
 */
bool Point::operator==(const Point &point2) {
    return (x == point2.getX() && y == point2.getY());
}

/**
 * operator for print a point.
 * @param os.
 * @param p.
 * @return the x and y of the point.
 */
ostream &operator<<(std::ostream &os, const Point &p) {
    return os << "(" << p.x << "," << p.y << ")";
}

Point::Point() {
    this->x=0;
    this->y=0;
}
