#ifndef MS_SWEEPER_HPP
#define MS_SWEEPER_HPP

#include <functional>
#include <ms/Grid.hpp>

namespace ms {

using CellFunc = std::function<void(int, int)>;

class Sweeper {
  private:
    Grid grid_;
    int flagged_count_;  // count of flagged cells
    bool is_ended_;

  public:
    Sweeper();
    Sweeper(const Sweeper& rhs) = delete;
    Sweeper(Sweeper&& rhs) = default;
    Sweeper(int row, int col, int mine_count);

    ~Sweeper() = default;

    const Grid& board() const;
    Grid& board();

    /**
     * @brief the count of flagged cells
     * @return the count
     */
    int flagged_count() const;

    /**
     * @brief sweep the cell at (x, y)
     * @param x x-coordinate
     * @param y y-coordinate
     * @param callback the callback function operatoed on the cell after
     * sweeping
     * @return the result of sweeping
     */
    SweepResult sweep(int x, int y, CellFunc callback = nullptr);

    /**
     * @brief sweep all cells around the space at (x, y)
     * @param x x-coordinate of the space
     * @param y y-coordinate of the space
     * @param callback the callback function when calling sweep
     */
    SweepResult sweep_around(int x, int y, CellFunc callback = nullptr);

    /**
     * @brief auto sweep the rest of the cells when all mines are flagged
     * @param x x-coordinate of the cell
     * @param y y-coordinate of the cell
     * @param callback the callback function when calling sweep
     */
    SweepResult auto_sweep(int x, int y, CellFunc callback = nullptr);

    /**
     * @brief flag the cell at (x, y)
     * @param x x-coordinate
     * @param y y-coordinate
     * @param callback the callback function operated on the cell after flagging
     */
    void flag(int x, int y, CellFunc callback = nullptr);

    /**
     * @brief sweep all mines when losing the game
     */
    void sweep_all_mines(CellFunc callback = nullptr);

    /**
     * @brief if the game is finished
     * @return the result
     */
    bool is_won() const;

    bool is_ended() const;
    void end_game();

    /**
     * @brief replay the game
     *
     * @param x rows of the board
     * @param y columns of the borad
     * @param mine_count the count of mines
     */
    void replay(int x, int y, int mine_count);
};

}  // namespace ms
#endif  // MS_SWEEPER_HPP
