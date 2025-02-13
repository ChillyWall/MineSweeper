#include <cstdio>
#include <cstdlib>
#include <ui/ui.hpp>

namespace ui {

void show_board(const ms::Grid& grid) {
#if defined(__WIN32)
    std::system("cls");
#elif defined(__linux__)
    std::system("clear");
#endif
    // print the column numbers
    printf("  ");
    for (int i = 0; i < grid.n(); ++i) {
        printf("  %-2d", i);
    }
    printf("\n");

    // print the top border
    printf("  ");
    printf("\u250C");
    for (int i = 1; i < grid.n(); ++i) {
        printf("\u2500\u2500\u2500\u252C");
    }
    printf("\u2500\u2500\u2500\u2510\n");

    // print the rows
    for (int i = 0; i < grid.m() - 1; ++i) {
        printf("%2d", i);
        printf("\u2502");
        for (int j = 0; j < grid.n(); ++j) {
            printf(" ");
            print_cell(grid.get_cell(i, j));
            printf(" \u2502");
        }
        printf("\n");

        printf("  \u251c");
        for (int j = 0; j < grid.n() - 1; ++j) {
            printf("\u2500\u2500\u2500\u253c");
        }
        printf("\u2500\u2500\u2500\u2524\n");
    }

    // print the last row
    int i = grid.m() - 1;
    printf("%2d", i);
    printf("\u2502");
    for (int j = 0; j < grid.n(); ++j) {
        printf(" ");
        print_cell(grid.get_cell(i, j));
        printf(" \u2502");
    }
    printf("\n");

    // print the bottom border
    printf("  ");
    printf("\u2514");
    for (int j = 0; j < grid.n() - 1; ++j) {
        printf("\u2500\u2500\u2500\u2534");
    }
    printf("\u2500\u2500\u2500\u2518\n");
}

void print_cell(const ms::Cell& cell) {
    switch (cell.status()) {
        case ms::UNKNOWN:
            printf("\033[47m ");
            break;
        case ms::FLAGGED:
            printf("\033[31m\uf024");
            break;
        case ms::OPEN:
            print_number(cell.num());
            break;
    }

    printf("\033[0m");
}

void print_number(int num) {
    switch (num) {
        case 0:
            printf(" ");
            break;
        case 1:
            printf("\033[38;2;0;0;247m1");
            break;
        case 2:
            printf("\033[38;2;0;119;0m2");
            break;
        case 3:
            printf("\033[38;2;236;0;0m3");
            break;
        case 4:
            printf("\033[38;2;0;0;128m4");
            break;
        case 5:
            printf("\033[38;2;128;0;0m5");
            break;
        case 6:
            printf("\033[38;2;0;128;1m6");
            break;
        case 7:
            printf("\033[38;2;0;0;01m7");
            break;
        case 8:
            printf("\033[38;2;128;128;128m8");
            break;
        case -1:
            printf("\033[38;2;255;255;255m\U000f0dda");
            break;
    }
    printf("\033[39m");
}

}  // namespace ui
