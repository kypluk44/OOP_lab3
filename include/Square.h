#ifndef SQUARE_H
#define SQUARE_H

#include <array>

#include "Figure.h"

class Square : public Figure {
public:
    Square() = default;
    Square(const Square& other) = default;
    Square(Square&& other) noexcept = default;

    Square& operator=(const Square& other) = default;
    Square& operator=(Square&& other) noexcept = default;

    void print(std::ostream& os) const override;
    void read(std::istream& is) override;

    Point center() const override;
    double surface() const override;

    operator double() const override;

    bool operator==(const Square& other) const;
    bool operator==(const Figure& other) const override;

    bool validate() const override;

    ~Square() override = default;

    const std::array<Point, 4>& getVertices() const { return vertices; }

private:
    std::array<Point, 4> vertices{};
};

#endif
