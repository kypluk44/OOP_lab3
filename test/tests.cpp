#include <gtest/gtest.h>
#include <memory>
#include <sstream>
#include <typeinfo>
#include <stdexcept>

#include "../include/Figure.h"
#include "../include/Square.h"
#include "../include/Rectangle.h"
#include "../include/Trapezoid.h"
#include "../include/Array.h"

void inputFigure(Figure& fig, const std::string& input) {
    std::istringstream iss(input);
    iss >> fig;
}

// --- Тесты квадрата ---
TEST(SquareTest, ReadAndPrint) {
    Square s;
    inputFigure(s, "0 0  2 0  2 2  0 2");
    std::ostringstream oss;
    oss << s;
    EXPECT_EQ(oss.str(), "(0, 0) (2, 0) (2, 2) (0, 2) ");
}

TEST(SquareTest, AreaCalculation) {
    Square s;
    inputFigure(s, "1 1  3 1  3 3  1 3");
    EXPECT_DOUBLE_EQ(static_cast<double>(s), 4.0);
}

TEST(SquareTest, CenterCalculation) {
    Square s;
    inputFigure(s, "0 0  2 0  2 2  0 2");
    Point c = s.center();
    EXPECT_DOUBLE_EQ(c.x, 1.0);
    EXPECT_DOUBLE_EQ(c.y, 1.0);
}

TEST(SquareTest, InvalidSquareThrows) {
    Square s;
    EXPECT_THROW(inputFigure(s, "0 0  3 0  4 1  0 1"), std::invalid_argument);
}

TEST(SquareTest, EqualityOperator) {
    Square s1;
    Square s2;
    inputFigure(s1, "0 0  2 0  2 2  0 2");
    inputFigure(s2, "0 0  2 0  2 2  0 2");
    EXPECT_TRUE(s1 == s2);
}

// --- Тесты прямоугольника ---
TEST(RectangleTest, ReadAndPrint) {
    Rectangle r;
    inputFigure(r, "0 0  4 0  4 2  0 2");
    std::ostringstream oss;
    oss << r;
    EXPECT_EQ(oss.str(), "(0, 0) (4, 0) (4, 2) (0, 2) ");
}

TEST(RectangleTest, AreaCalculation) {
    Rectangle r;
    inputFigure(r, "1 1  6 1  6 4  1 4");
    EXPECT_DOUBLE_EQ(static_cast<double>(r), 15.0);
}

TEST(RectangleTest, CenterCalculation) {
    Rectangle r;
    inputFigure(r, "0 0  4 0  4 2  0 2");
    Point c = r.center();
    EXPECT_DOUBLE_EQ(c.x, 2.0);
    EXPECT_DOUBLE_EQ(c.y, 1.0);
}

TEST(RectangleTest, InvalidRectangleThrows) {
    Rectangle r;
    EXPECT_THROW(inputFigure(r, "0 0  4 0  5 2  0 3"), std::invalid_argument);
}

TEST(RectangleTest, EqualityOperator) {
    Rectangle r1;
    Rectangle r2;
    inputFigure(r1, "0 0  4 0  4 2  0 2");
    inputFigure(r2, "0 0  4 0  4 2  0 2");
    EXPECT_TRUE(r1 == r2);
}

// --- Тесты трапеции ---
TEST(TrapezoidTest, ReadAndPrint) {
    Trapezoid t;
    inputFigure(t, "0 0  4 0  3 2  1 2");
    std::ostringstream oss;
    oss << t;
    EXPECT_EQ(oss.str(), "(0, 0) (4, 0) (3, 2) (1, 2) ");
}

TEST(TrapezoidTest, AreaCalculation) {
    Trapezoid t;
    inputFigure(t, "0 0  5 0  4 3  1 3");
    EXPECT_DOUBLE_EQ(static_cast<double>(t), 12.0);
}

TEST(TrapezoidTest, CenterCalculation) {
    Trapezoid t;
    inputFigure(t, "0 0  4 0  3 2  1 2");
    Point c = t.center();
    EXPECT_NEAR(c.x, 2.0, 1e-6);
    EXPECT_NEAR(c.y, 8.0 / 9.0, 1e-6);
}

TEST(TrapezoidTest, InvalidTrapezoidThrows) {
    Trapezoid t;
    EXPECT_THROW(inputFigure(t, "0 0  2 1  3 4  1 5"), std::invalid_argument);
}

TEST(TrapezoidTest, EqualityOperator) {
    Trapezoid t1;
    Trapezoid t2;
    inputFigure(t1, "0 0  5 0  4 3  1 3");
    inputFigure(t2, "0 0  5 0  4 3  1 3");
    EXPECT_TRUE(t1 == t2);
}

TEST(TrapezoidTest, CopyAndMove) {
    Trapezoid t1;
    inputFigure(t1, "0 0  4 0  3 2  1 2");
    Trapezoid t2 = t1;
    EXPECT_TRUE(t1 == t2);
    Trapezoid t3 = std::move(t1);
    std::ostringstream oss;
    oss << t3;
    EXPECT_EQ(oss.str(), "(0, 0) (4, 0) (3, 2) (1, 2) ");
}

// --- Тесты контейнера ---
TEST(ArrayTest, AddAndSize) {
    Array arr;
    arr.add(std::make_unique<Square>());
    arr.add(std::make_unique<Rectangle>());
    EXPECT_EQ(arr.getSize(), 2);
}

TEST(ArrayTest, Remove) {
    Array arr;
    arr.add(std::make_unique<Square>());
    arr.add(std::make_unique<Rectangle>());
    arr.add(std::make_unique<Trapezoid>());

    arr.remove(1);
    EXPECT_EQ(arr.getSize(), 2);
    EXPECT_TRUE(dynamic_cast<Square*>(&arr[0]));
    EXPECT_TRUE(dynamic_cast<Trapezoid*>(&arr[1]));
}

TEST(ArrayTest, TotalSurface) {
    Array arr;

    auto square = std::make_unique<Square>();
    inputFigure(*square, "0 0  2 0  2 2  0 2"); // площадь = 4
    arr.add(std::move(square));

    auto rect = std::make_unique<Rectangle>();
    inputFigure(*rect, "0 0  6 0  6 1  0 1"); // площадь = 6
    arr.add(std::move(rect));

    EXPECT_NEAR(arr.totalSurface(), 10.0, 1e-6);
}

TEST(ArrayTest, PrintSurfaces) {
    Array arr;
    auto trapezoid = std::make_unique<Trapezoid>();
    inputFigure(*trapezoid, "0 0  4 0  3 2  1 2");
    arr.add(std::move(trapezoid));

    testing::internal::CaptureStdout();
    arr.printSurfaces();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Площадь"), std::string::npos);
}

TEST(ArrayTest, OutOfRangeThrows) {
    Array arr;
    arr.add(std::make_unique<Square>());
    EXPECT_THROW(arr[5], std::out_of_range);
}

TEST(ArrayTest, Polymorphism) {
    Array arr;
    arr.add(std::make_unique<Square>());
    arr.add(std::make_unique<Rectangle>());
    arr.add(std::make_unique<Trapezoid>());

    for (size_t i = 0; i < arr.getSize(); ++i) {
        Figure& fig = arr[i];
        EXPECT_NE(typeid(fig), typeid(Figure));
    }
}

// --- Базовый абстрактный класс ---
TEST(FigureTest, BaseClassIsAbstract) {
    static_assert(!std::is_constructible<Figure>::value, "Figure should not be instantiable");
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
