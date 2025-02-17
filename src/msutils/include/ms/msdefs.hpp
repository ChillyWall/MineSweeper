#ifndef MS_DEFS_HPP
#define MS_DEFS_HPP

#include <cstddef>
#include <stdexcept>

namespace ms {

/* the status of the cells
 * UNKNOWN for unswept cells
 * MARKED if the cell is marked as mine
 * OPEN if the cell is swept and not a mine */
enum CellStatus { UNKNOWN, FLAGGED, OPEN };

/* the result of sweeping a cell
 * MINE if the cell contains a mine
 * ZERO if there are no mines around the cell
 * NORMAL for other occasions */
enum SweepResult { MINE, SAFE };

enum CellType { SWEPT_MINE = -2, NORMAL_MINE = -1, NUMBER };

using size_t = std::size_t;

struct TooManyMines : public std::invalid_argument {
    TooManyMines()
        : std::invalid_argument(
              "Too many mines which are more than the cells.") {}
    using std::invalid_argument::invalid_argument;
};

struct NotMine : public std::runtime_error {
    NotMine() : std::runtime_error("This cell doesn't contain a mine.") {}
    using std::runtime_error::runtime_error;
};

}  // namespace ms

#endif
