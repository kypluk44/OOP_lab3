#include "../include/Rectangle.h"

#include <iostream>
#include <stdexcept>
#include <typeinfo>

#include "../include/Geometry.h"

using namespace geometry;

void Rectangle::print(std::ostream& os) const {
    for (const auto& vertex : vertices) {
        os << vertex << " ";
    }
}

void Rectangle::read(std::istream& is) {
    std::cout << "Введите 4 вершины прямоугольника через пробел (формат x y):\n";
    for (auto& vertex : vertices) {
        if (!(is >> vertex)) throw std::runtime_error("Не удалось прочитать вершины прямоугольника");
    }
    if (!validate()) throw std::invalid_argument("Указанные точки не образуют прямоугольник");
}

Point Rectangle::center() const {
    return polygonCentroid(vertices);
}

double Rectangle::surface() const {
    return polygonArea(vertices);
}

Rectangle::operator double() const {
    return surface();
}

bool Rectangle::operator==(const Rectangle& other) const {
    for (std::size_t i = 0; i < vertices.size(); ++i) {
        if (!pointsEqual(vertices[i], other.vertices[i])) return false;
    }
    return true;
}

bool Rectangle::operator==(const Figure& other) const {
    if (typeid(*this) != typeid(other)) return false;
    return *this == static_cast<const Rectangle&>(other);
}

bool Rectangle::validate() const {
    const double area = surface();
    if (area < EPS) return false;

    const auto v0 = makeVec(vertices[0], vertices[1]);
    const auto v1 = makeVec(vertices[1], vertices[2]);
    const auto v2 = makeVec(vertices[2], vertices[3]);
    const auto v3 = makeVec(vertices[3], vertices[0]);

    const double sideASq = lengthSq(v0);
    const double sideBSq = lengthSq(v1);
    if (sideASq < EPS || sideBSq < EPS) return false;

    if (!almostEqual(sideASq, lengthSq(v2))) return false;
    if (!almostEqual(sideBSq, lengthSq(v3))) return false;

    if (!almostEqual(dot(v0, v1), 0.0)) return false;
    if (!almostEqual(dot(v1, v2), 0.0)) return false;
    if (!almostEqual(dot(v2, v3), 0.0)) return false;
    if (!almostEqual(dot(v3, v0), 0.0)) return false;

    const double diag1Sq = lengthSq(makeVec(vertices[0], vertices[2]));
    const double diag2Sq = lengthSq(makeVec(vertices[1], vertices[3]));
    if (!almostEqual(diag1Sq, diag2Sq)) return false;

    return true;
}
