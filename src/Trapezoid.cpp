#include "../include/Trapezoid.h"

#include <iostream>
#include <stdexcept>
#include <typeinfo>

#include "../include/Geometry.h"

using namespace geometry;

void Trapezoid::print(std::ostream& os) const {
    for (const auto& vertex : vertices) {
        os << vertex << " ";
    }
}

void Trapezoid::read(std::istream& is) {
    std::cout << "Введите 4 вершины трапеции через пробел (формат x y):\n";
    for (auto& vertex : vertices) {
        if (!(is >> vertex)) throw std::runtime_error("Не удалось прочитать вершины трапеции");
    }
    if (!validate()) throw std::invalid_argument("Указанные точки не образуют трапецию");
}

Point Trapezoid::center() const {
    return polygonCentroid(vertices);
}

double Trapezoid::surface() const {
    return polygonArea(vertices);
}

Trapezoid::operator double() const {
    return surface();
}

bool Trapezoid::operator==(const Trapezoid& other) const {
    for (std::size_t i = 0; i < vertices.size(); ++i) {
        if (!pointsEqual(vertices[i], other.vertices[i])) return false;
    }
    return true;
}

bool Trapezoid::operator==(const Figure& other) const {
    if (typeid(*this) != typeid(other)) return false;
    return *this == static_cast<const Trapezoid&>(other);
}

bool Trapezoid::validate() const {
    const double area = surface();
    if (area < EPS) return false;

    const auto v0 = makeVec(vertices[0], vertices[1]);
    const auto v1 = makeVec(vertices[1], vertices[2]);
    const auto v2 = makeVec(vertices[2], vertices[3]);
    const auto v3 = makeVec(vertices[3], vertices[0]);

    if (lengthSq(v0) < EPS || lengthSq(v1) < EPS ||
        lengthSq(v2) < EPS || lengthSq(v3) < EPS) {
        return false;
    }

    const bool parallel01_23 = almostEqual(cross(v0, v2), 0.0);
    const bool parallel12_30 = almostEqual(cross(v1, v3), 0.0);

    if (!(parallel01_23 || parallel12_30)) return false;

    return true;
}
