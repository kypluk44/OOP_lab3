#include "../include/Square.h"

#include <iostream>
#include <stdexcept>
#include <typeinfo>

#include "../include/Geometry.h"

using namespace geometry;

void Square::print(std::ostream& os) const {
    for (const auto& vertex : vertices) {
        os << vertex << " ";
    }
}

void Square::read(std::istream& is) {
    std::cout << "Введите 4 вершины квадрата через пробел (формат x y):\n";
    for (auto& vertex : vertices) {
        if (!(is >> vertex)) throw std::runtime_error("Не удалось прочитать вершины квадрата");
    }
    if (!validate()) throw std::invalid_argument("Указанные точки не образуют квадрат");
}

Point Square::center() const {
    return polygonCentroid(vertices);
}

double Square::surface() const {
    return polygonArea(vertices);
}

Square::operator double() const {
    return surface();
}

bool Square::operator==(const Square& other) const {
    for (std::size_t i = 0; i < vertices.size(); ++i) {
        if (!pointsEqual(vertices[i], other.vertices[i])) return false;
    }
    return true;
}

bool Square::operator==(const Figure& other) const {
    if (typeid(*this) != typeid(other)) return false;
    return *this == static_cast<const Square&>(other);
}

bool Square::validate() const {
    const double area = surface();
    if (area < EPS) return false;

    const auto v0 = makeVec(vertices[0], vertices[1]);
    const auto v1 = makeVec(vertices[1], vertices[2]);
    const auto v2 = makeVec(vertices[2], vertices[3]);
    const auto v3 = makeVec(vertices[3], vertices[0]);

    const double sideSq = lengthSq(v0);
    if (sideSq < EPS) return false;

    if (!almostEqual(sideSq, lengthSq(v1))) return false;
    if (!almostEqual(sideSq, lengthSq(v2))) return false;
    if (!almostEqual(sideSq, lengthSq(v3))) return false;

    if (!almostEqual(dot(v0, v1), 0.0)) return false;
    if (!almostEqual(dot(v1, v2), 0.0)) return false;
    if (!almostEqual(dot(v2, v3), 0.0)) return false;
    if (!almostEqual(dot(v3, v0), 0.0)) return false;

    const double diag1Sq = lengthSq(makeVec(vertices[0], vertices[2]));
    const double diag2Sq = lengthSq(makeVec(vertices[1], vertices[3]));
    if (!almostEqual(diag1Sq, diag2Sq)) return false;
    if (!almostEqual(diag1Sq, 2.0 * sideSq)) return false;

    return true;
}
