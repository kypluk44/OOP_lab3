#ifndef POINT_H
#define POINT_H

#include <iostream>

class Point
{
    friend std::ostream& operator<<(std::ostream& os, const Point& p);
    friend std::istream& operator>>(std::istream& is, Point& p);

public:
    double x{0.0}, y{0.0};

    Point() = default;
    Point(double x, double y);

    double distanceTo(const Point& other) const;

    ~Point() = default;
};

inline std::ostream& operator<<(std::ostream& os, const Point& p) {
    return os << "(" << p.x << ", " << p.y << ")";
}

inline std::istream& operator>>(std::istream& is, Point& p) {
    return is >> p.x >> p.y;
}

#endif