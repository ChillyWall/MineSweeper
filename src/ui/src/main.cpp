#include <iostream>
#include <ms/Grid.hpp>
#include <string>
#include <ui/ui.hpp>

using std::cin;
using std::cout;

void game_loop();

int main() {
    game_loop();
    return 0;
}

void game_loop() {
    while (true) {
        cout << "Please input the size of the grid and the count of mines: ";
        int x, y, z, count;
        cin >> x >> y >> count;

        ms::Grid grid(x, y, count);
        do {
            ui::show_grid(grid);
            cout << "input the coordinates: ";
            cin >> x >> y;
            cout << "sweep(0) or flag(1): ";
            cin >> z;
            if (z == 0) {
                auto res = grid.sweep(x, y);
                if (res == ms::MINE) {
                    break;
                }
            } else if (z == 1) {
                grid.flag(x, y);
            }
        } while (!grid.is_finished());

        grid.sweep_all();
        ui::show_grid(grid);

        if (grid.flagged_count() == grid.mine_count()) {
            cout << "Congratulations! You win!" << std::endl;
        } else {
            cout << "Sorry, you lose!" << std::endl;
        }

        cout << "whether to continue the game? (y/n): ";
        std::string choice;
        cin >> choice;
        if (choice.compare("y") != 0) {
            break;
        }
    }
}
