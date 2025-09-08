//
// Created by Sebastian Apelgren on 2025-09-08.
//

#include <ostream>
#ifndef UNTITLED_POINT_H
#define UNTITLED_POINT_H


class Point {
public:
    double x;
    double y;
    Point() = default;
    Point(double x, double y);

    friend std::ostream& operator<<(std::ostream& os, const Point& pt);
};


#endif //UNTITLED_POINT_H