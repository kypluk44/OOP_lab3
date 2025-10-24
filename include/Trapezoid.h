#ifndef TRAPEZOID_H
#define TRAPEZOID_H

#include <array>

#include "Figure.h"

class Trapezoid : public Figure {
public:
    Trapezoid() = default;
    Trapezoid(const Trapezoid& other) = default;
    Trapezoid(Trapezoid&& other) noexcept = default;

    Trapezoid& operator=(const Trapezoid& other) = default;
    Trapezoid& operator=(Trapezoid&& other) noexcept = default;

    void print(std::ostream& os) const override;
    void read(std::istream& is) override;

    Point center() const override;
    double surface() const override;

    operator double() const override;

    bool operator==(const Trapezoid& other) const;
    bool operator==(const Figure& other) const override;

    bool validate() const override;

    ~Trapezoid() override = default;

    const std::array<Point, 4>& getVertices() const { return vertices; }

private:
    std::array<Point, 4> vertices{};
};

#endif
