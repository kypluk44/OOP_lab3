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

    const auto v01 = makeVec(vertices[0], vertices[1]);
    const auto v12 = makeVec(vertices[1], vertices[2]);
    const auto v23 = makeVec(vertices[2], vertices[3]);
    const auto v30 = makeVec(vertices[3], vertices[0]);

    if (lengthSq(v01) < EPS || lengthSq(v12) < EPS ||
        lengthSq(v23) < EPS || lengthSq(v30) < EPS) {
        return false;
    }

    const bool base01_23 = almostEqual(cross(v01, v23), 0.0);
    const bool base12_30 = almostEqual(cross(v12, v30), 0.0);

    if (base01_23 && base12_30) return false; // параллелограмм, а не трапеция
    if (!base01_23 && !base12_30) return false;

    if (base01_23) {
        const double leg1 = vertices[1].distanceTo(vertices[2]);
        const double leg2 = vertices[3].distanceTo(vertices[0]);
        if (!almostEqual(leg1, leg2)) return false;
        if (almostEqual(vertices[0].distanceTo(vertices[1]), vertices[2].distanceTo(vertices[3]))) return false;
    } else {
        const double leg1 = vertices[2].distanceTo(vertices[3]);
        const double leg2 = vertices[0].distanceTo(vertices[1]);
        if (!almostEqual(leg1, leg2)) return false;
        if (almostEqual(vertices[1].distanceTo(vertices[2]), vertices[3].distanceTo(vertices[0]))) return false;
    }

    return true;
}
