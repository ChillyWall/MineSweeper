#ifndef MS_GRID_HPP
#define MS_GRID_HPP

#include <ms/Cell.hpp>
#include <ms/msdefs.hpp>
#include <vector>

namespace ms {

class Grid {
  private:
    using CellArray = std::vector<Cell>;
    CellArray cells_;

    int m_;           // rows
    int n_;           // columns
    int mine_count_;  // count of mines

    /**
     * @brief generate the mines
     */
    void generate();

    /**
     * @brief upddate the number of cells around the mine at (x, y)
     * @param x x-coordinate of the mine
     * @param y y-coordinate of the mine
     */
    void update_num(int x, int y);

    /**
     * @brief reset all cells to 0
     */
    void reset_cells();

  public:
    Grid() = default;
    Grid(const Grid& rhs) = delete;
    Grid(Grid&& rhs) = default;
    ~Grid() = default;

    Grid(int m, int n, int count);

    int m() const;
    int n() const;
    int mine_count() const;

    /**
     * @brief get the cell at (m, n)
     * @param m x-coordinate
     * @param n y-coordinate
     * @return the cell
     */
    const Cell& get_cell(int m, int n) const;

    /**
     * @brief get the cell at (m, n)
     * @param m x-coordinate
     * @param n y-coordinate
     * @return the cell
     */
    Cell& get_cell(int m, int n);

    /**
     * @brief regenerate the grid of cells, the cells won't be destroyed if m and n are the same
     * @param m new m
     * @param n new n
     * @param count new count
     */
    void regenerate(int m, int n, int count);
};

}  // namespace ms

#endif
