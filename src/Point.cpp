#include "../include/Point.h"
#include <cmath>

Point::Point(double x, double y) : x(x), y(y) {}

double Point::distanceTo(const Point& other) const {
    return std::sqrt((x - other.x)*(x - other.x) + (y - other.y)*(y - other.y));
}