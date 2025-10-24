#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <array>

#include "Figure.h"

class Rectangle : public Figure {
public:
    Rectangle() = default;
    Rectangle(const Rectangle& other) = default;
    Rectangle(Rectangle&& other) noexcept = default;

    Rectangle& operator=(const Rectangle& other) = default;
    Rectangle& operator=(Rectangle&& other) noexcept = default;

    void print(std::ostream& os) const override;
    void read(std::istream& is) override;

    Point center() const override;
    double surface() const override;

    operator double() const override;

    bool operator==(const Rectangle& other) const;
    bool operator==(const Figure& other) const override;

    bool validate() const override;

    ~Rectangle() override = default;

    const std::array<Point, 4>& getVertices() const { return vertices; }

private:
    std::array<Point, 4> vertices{};
};

#endif
