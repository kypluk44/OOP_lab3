#include <iostream>
#include <memory>
#include <iomanip>
#include <typeinfo>

#include "include/Array.h"
#include "include/Trapezoid.h"
#include "include/Rectangle.h"
#include "include/Square.h"

std::string typeName(const Figure& f) {
    if (dynamic_cast<const Trapezoid*>(&f)) return "Трапеция";
    if (dynamic_cast<const Rectangle*>(&f)) return "Прямоугольник";
    if (dynamic_cast<const Square*>(&f))    return "Квадрат";
    return "Неизвестная фигура";
}

int main() {
    std::cout << std::fixed << std::setprecision(2);

    try {
        // 1. Создание контейнера фигур
        Array figures;

        // 2. Добавление трёх фигур разных типов
        figures.add(std::make_unique<Square>());
        figures.add(std::make_unique<Rectangle>());
        figures.add(std::make_unique<Trapezoid>());

        // 3. Ввод вершин для каждой фигуры
        std::cout << "=== Ввод координат вершин ===\n";
        for (size_t i =  0; i < figures.getSize(); ++i) {
            std::cout << "\nФигура " << i << " - " 
                      << typeName(figures[i]) << ":\n";
            std::cin >> figures[i];
        }

        // 4. Вывод всех фигур и их площадей
        std::cout << "\n=== Список фигур ===\n";
        figures.printSurfaces();

        // 5. Вывод центров фигур
        std::cout << "\n=== Геометрические центры ===\n";
        figures.printCenters();

        // 6. Общая площадь
        std::cout << "\n=== Общая площадь всех фигур ===\n";
        std::cout << "Суммарная площадь = " << figures.totalSurface() << std::endl;

        // 7. Проверка operator== и приведения к double
        std::cout << "\n=== Проверка операторов ===\n";
        if (figures[0] == figures[1])
            std::cout << "Фигура 0 равна фигуре 1\n";
        else
            std::cout << "Фигура 0 не равна фигуре 1\n";

        std::cout << "Площадь фигуры 0 = " 
                  << static_cast<double>(figures[0]) << std::endl;

        // 8. Проверка копирования и перемещения Trapezoid
        std::cout << "\n=== Проверка копирования и перемещения (Трапеция) ===\n";
        Trapezoid t1;
        std::cin >> t1;
        std::cout << "Исходная трапеция:\n" << t1 << std::endl;

        Trapezoid t2 = t1;
        std::cout << "После копирования (t2):\n" << t2 << std::endl;

        Trapezoid t3 = std::move(t1);
        std::cout << "После перемещения (t3):\n" << t3 << std::endl;

        // 9. Удаление фигуры
        std::cout << "\n=== Удаление фигуры 1 ===\n";
        figures.remove(1);
        figures.printSurfaces();

        // 10. Проверка обработки исключения
        std::cout << "\n=== Проверка выхода за границы массива ===\n";
        std::cout << "Пробуем обратиться к фигуре 10...\n";
        std::cout << figures[10]; // вызовет исключение

    } catch (const std::out_of_range& e) {
        std::cerr << "Ошибка: выход за границы массива - " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Исключение: " << e.what() << std::endl;
    }

    return 0;
}
