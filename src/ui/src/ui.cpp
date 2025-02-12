#include <cstdlib>
#include <iostream>
#include <ui/ui.hpp>

namespace ui {

void show_board(const ms::Grid& grid) {
#if defined(__WIN32)
    std::system("cls");
#elif defined(__linux__)
    std::system("clear");
#endif

    std::cout << "   ";
    for (int i = 0; i < grid.n(); ++i) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < grid.m(); ++i) {
        std::cout << i << " |";
        for (int j = 0; j < grid.n(); ++j) {
            auto& cell = grid.get_cell(i, j);
            switch (cell.status()) {
                case ms::UNKNOWN:
                    std::cout << "_";
                    break;
                case ms::FLAGGED:
                    std::cout << "*";
                    break;
                case ms::OPEN:
                    if (cell.num() == -1) {
                        std::cout << "x";
                    } else {
                        std::cout << cell.num();
                    }
                    break;
            }
            std::cout << "|";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

}  // namespace ui
