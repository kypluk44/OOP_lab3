#ifndef FIGURE_H
#define FIGURE_H

#include <iostream>
#include <string.h>
#include <string_view>

#include "Point.h"

class Figure
{
    friend std::ostream& operator<<(std::ostream& os, const Figure& f);
    friend std::istream& operator>>(std::istream& is, Figure& f);

protected:
    Figure() = default;

    virtual void print(std::ostream& os) const = 0;
    virtual void read(std::istream& is) = 0;
    virtual bool validate() const = 0;

public:
    virtual ~Figure() = default;

    virtual Point center() const = 0;
    virtual double surface() const = 0;

    virtual operator double() const = 0;
    virtual bool operator==(const Figure& other) const = 0;
};

inline std::ostream& operator<<(std::ostream& os, const Figure& fig) {
    fig.print(os);
    return os;
}

inline std::istream& operator>>(std::istream& is, Figure& fig) {
    fig.read(is);
    return is;
}

#endif