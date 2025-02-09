#ifndef MS_CELL_HPP
#define MS_CELL_HPP

#include <ms/msdefs.hpp>

namespace ms {

class Cell {
private:
    /* the status of this cell. */
    CellStatus stat_;

    /* represents how many mines are around this cell.
     * -1 if there is a mine in this cell */
    int num_;

public:
    Cell();
    ~Cell() = default;
    Cell(const Cell& rhs) = default;

    /**
     * @brief the number of mines around this cell
     * @return the number
     */
    int num() const;

    /**
     * @brief set the number to a new value
     * @param number the number
     */
    void set_num(int number);

    /**
     * @brief the status of this cell
     * @return the status
     */
    CellStatus status() const;

    /**
     * @brief flag this cell
     */
    void flag();

    /**
     * @brief unflag this cell
     */
    void unflag();

    /**
     * @brief to sweep this cell
     * @return the result
     */
    SweepResult sweep();
};

}  // namespace ms

#endif
