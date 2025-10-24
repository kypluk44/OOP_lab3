#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <array>
#include <cmath>
#include <cstddef>
#include <numeric>

#include "Point.h"

namespace geometry {

inline constexpr double EPS = 1e-6;

struct Vec {
    double x;
    double y;
};

inline Vec makeVec(const Point& from, const Point& to) {
    return Vec{to.x - from.x, to.y - from.y};
}

inline double dot(const Vec& a, const Vec& b) {
    return a.x * b.x + a.y * b.y;
}

inline double cross(const Vec& a, const Vec& b) {
    return a.x * b.y - a.y * b.x;
}

inline double lengthSq(const Vec& v) {
    return dot(v, v);
}

inline bool almostEqual(double a, double b, double eps = EPS) {
    return std::fabs(a - b) <= eps;
}

inline bool pointsEqual(const Point& a, const Point& b, double eps = EPS) {
    return almostEqual(a.x, b.x, eps) && almostEqual(a.y, b.y, eps);
}

template <std::size_t N>
double polygonArea(const std::array<Point, N>& pts) {
    double sum = 0.0;
    for (std::size_t i = 0; i < N; ++i) {
        std::size_t j = (i + 1) % N;
        sum += pts[i].x * pts[j].y - pts[j].x * pts[i].y;
    }
    return std::fabs(sum) * 0.5;
}

template <std::size_t N>
Point polygonCentroid(const std::array<Point, N>& pts) {
    double crossSum = 0.0;
    double cx = 0.0;
    double cy = 0.0;

    for (std::size_t i = 0; i < N; ++i) {
        std::size_t j = (i + 1) % N;
        double crossVal = pts[i].x * pts[j].y - pts[j].x * pts[i].y;
        crossSum += crossVal;
        cx += (pts[i].x + pts[j].x) * crossVal;
        cy += (pts[i].y + pts[j].y) * crossVal;
    }

    if (std::fabs(crossSum) < EPS) {
        double avgX = 0.0;
        double avgY = 0.0;
        for (const auto& p : pts) {
            avgX += p.x;
            avgY += p.y;
        }
        return Point{avgX / static_cast<double>(N), avgY / static_cast<double>(N)};
    }

    double factor = 1.0 / (3.0 * crossSum);
    return Point{cx * factor, cy * factor};
}

}

#endif
