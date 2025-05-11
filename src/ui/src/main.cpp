#include <iostream>
#include <ms/Sweeper.hpp>
#include <string>
#include <ui.hpp>

using std::cin;
using std::cout;

void game_loop();

int main() {
    game_loop();
    return 0;
}

void game_loop() {
    ms::Sweeper sweeper;
    while (true) {
        cout << "Please input the size of the grid and the count of mines: ";
        int x, y, z, count;
        cin >> x >> y >> count;
        if (x * y < count) {
            cout << "The number of mines is greater than the number of cells."
                 << std::endl;
            continue;
        }
        sweeper.replay(x, y, count);
        do {
            ui::show_board(sweeper.board());
            cout << sweeper.flagged_count() << "/"
                 << sweeper.board().mine_count() << std::endl;
            cout << "input the coordinates: ";
            cin >> x >> y;
            cout << "sweep(0) or flag(1): ";
            cin >> z;
            if (z == 0) {
                auto res = sweeper.sweep(x, y);
                if (res == ms::MINE) {
                    break;
                }
            } else if (z == 1) {
                sweeper.flag(x, y);
            }
        } while (!sweeper.is_won());

        sweeper.sweep_all_mines();
        ui::show_board(sweeper.board());

        if (sweeper.flagged_count() == sweeper.board().mine_count()) {
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
