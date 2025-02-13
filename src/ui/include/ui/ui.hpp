#ifndef MS_UI_HPP
#define MS_UI_HPP

#include <ms/Grid.hpp>

namespace ui {

/**
 * @brief show the grid of cells
 * @param grid the Grid object
 */
void show_board(const ms::Grid& grid);

void print_cell(const ms::Cell& cell);

void print_number(int num);

}  // namespace ui

#endif
