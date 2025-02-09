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

    int m_;              // rows
    int n_;              // columns
    int mine_count_;     // count of mines
    int flagged_count_;  // count of flagged cells

    /**
     * @brief generate the mines
     */
    void generate();

    /**
     * @brief upddate the number of cells around the mine at (x, y)
     *
     * @param x x-coordinate of the mine
     * @param y y-coordinate of the mine
     */
    void update_num(int x, int y);

    /**
     * @brief sweep all cells around the space at (x, y)
     *
     * @param x x-coordinate of the space
     * @param y y-coordinate of the space
     */
    SweepResult sweep_around(int x, int y);

    /**
     * @brief auto sweep the rest of the cells when all mines are flagged
     *
     * @param x x-coordinate of the cell
     * @param y y-coordinate of the cell
     */
    SweepResult auto_sweep(int x, int y);

public:
    Grid() = default;
    Grid(int m, int n, int count);
    Grid(const Grid& rhs) = delete;
    Grid(Grid&& rhs) = default;
    ~Grid() = default;

    int m() const;
    int n() const;
    int mine_count() const;

    /**
     * @brief the count of flagged cells
     * @return the count
     */
    int flagged_count() const;

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
     * @brief sweep the cell at (x, y)
     * @param x x-coordinate
     * @param y y-coordinate
     * @return the result of sweeping
     */

    SweepResult sweep(int x, int y);
    /**
     * @brief flag the cell at (x, y)
     * @param x x-coordinate
     * @param y y-coordinate
     */
    void flag(int x, int y);

    /**
     * @brief sweep all cells when losing the game
     */
    void sweep_all();

    /**
     * @brief if the game is finished
     * @return the result
     */
    bool is_finished() const;
};

}  // namespace ms

#endif
