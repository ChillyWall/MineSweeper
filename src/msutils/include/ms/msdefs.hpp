#ifndef MS_DEFS_HPP
#define MS_DEFS_HPP

#include <cstddef>

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

using size_t = std::size_t;

}  // namespace ms

#endif
