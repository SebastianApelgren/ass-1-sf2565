//
// Created by Sebastian Apelgren on 2025-09-08.
//

#include "Point.h"
#include <ostream>

Point::Point(double x, double y) {
    this->x = x;
    this->y = y;
}

std::ostream& operator<<(std::ostream& os, const Point& pt){
    os << "(" << pt.x << "," << pt.y << ")";
    return os;
}

Point Point::operator+(const Point& rhs) const {
    return Point{x + rhs.x, y + rhs.y};
}

Point Point::operator-(const Point &rhs) const {
    return {x - rhs.x, y - rhs.y};
}

Point Point::operator*(double rhs) const {
    return {x*rhs,y*rhs};
}
