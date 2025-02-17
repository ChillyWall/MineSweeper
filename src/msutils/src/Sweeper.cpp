#include <ms/Grid.hpp>
#include <ms/Sweeper.hpp>
#include "ms/Cell.hpp"
#include "ms/msdefs.hpp"

namespace ms {

Sweeper::Sweeper() : grid_(), flagged_count_(0), is_ended_(false) {}

Sweeper::Sweeper(int row, int col, int mine_count)
    : grid_(row, col, mine_count), flagged_count_(0) {}

const Grid& Sweeper::board() const {
    return grid_;
}

Grid& Sweeper::board() {
    return const_cast<Grid&>(static_cast<const Sweeper*>(this)->board());
}

int Sweeper::flagged_count() const {
    return flagged_count_;
}

void Grid::update_num(int x, int y) {
    for (int i = x - 1; i <= x + 1; ++i) {
        for (int j = y - 1; j <= y + 1; ++j) {
            if (i < 0 || i >= m_ || j < 0 || j >= n_ || (i == x && j == y)) {
                continue;
            }

            auto& tmp_cell = cells_.at(i * n_ + j);
            if (tmp_cell.type() == NORMAL_MINE) {
                continue;
            }

            tmp_cell.set_num(tmp_cell.num() + 1);
        }
    }
}

SweepResult Sweeper::sweep(int x, int y, CellFunc callback) {
    auto& tmp_cell = grid_.get_cell(x, y);
    SweepResult res;
    switch (tmp_cell.status()) {
        case UNKNOWN: {
            res = tmp_cell.sweep();
            if (res == SAFE && tmp_cell.num() == 0) {
                sweep_around(x, y, callback);
            } else if (res == MINE && !is_ended_) {
                tmp_cell.set_mine_swept();
                is_ended_ = true;
            }
            break;
        }
        case FLAGGED: {
            res = SAFE;
            break;
        }
        case OPEN: {
            res = auto_sweep(x, y, callback);
            break;
        }
    }
    if (callback) {
        callback(x, y);
    }

    return res;
}

SweepResult Sweeper::sweep_around(int x, int y, CellFunc callback) {
    SweepResult res = SAFE;
    for (int i = x - 1; i <= x + 1; ++i) {
        for (int j = y - 1; j <= y + 1; ++j) {
            if (i < 0 || i >= grid_.m() || j < 0 || j >= grid_.n() ||
                (i == x && j == y)) {
                continue;
            }

            auto& tmp_cell = grid_.get_cell(i, j);
            if (tmp_cell.status() == UNKNOWN) {
                if (sweep(i, j, callback) == MINE) {
                    res = MINE;
                }
            }
        }
    }
    return res;
}

SweepResult Sweeper::auto_sweep(int x, int y, CellFunc callback) {
    auto& cell = grid_.get_cell(x, y);
    int count = 0;
    for (int i = x - 1; i <= x + 1; ++i) {
        for (int j = y - 1; j <= y + 1; ++j) {
            if (i < 0 || i >= grid_.m() || j < 0 || j >= grid_.n() ||
                (i == x && j == y)) {
                continue;
            }

            if (grid_.get_cell(i, j).status() == FLAGGED) {
                ++count;
            }
        }
    }

    if (count == cell.num()) {
        return sweep_around(x, y, callback);
    }

    return SAFE;
}

void Sweeper::flag(int x, int y, CellFunc callback) {
    auto& tmp_cell = grid_.get_cell(x, y);
    if (tmp_cell.status() == UNKNOWN) {
        tmp_cell.flag();
        ++flagged_count_;
    } else if (tmp_cell.status() == FLAGGED) {
        tmp_cell.unflag();
        --flagged_count_;
    }

    if (callback) {
        callback(x, y);
    }
}

void Sweeper::sweep_all_mines(CellFunc callback) {
    for (int i = 0; i < grid_.m(); ++i) {
        for (int j = 0; j < grid_.n(); ++j) {
            auto& tmp_cell = grid_.get_cell(i, j);
            if (tmp_cell.status() != OPEN && tmp_cell.type() == NORMAL_MINE) {
                tmp_cell.set_status(OPEN);
                if (callback) {
                    callback(i, j);
                }
            }
        }
    }
}

bool Sweeper::is_won() const {
    if (flagged_count_ != grid_.mine_count()) {
        return false;
    }
    for (int i = 0; i < grid_.m(); ++i) {
        for (int j = 0; j < grid_.n(); ++j) {
            if (grid_.get_cell(i, j).status() == UNKNOWN) {
                return false;
            }
        }
    }
    return true;
}

bool Sweeper::is_ended() const {
    return is_ended_;
}

void Sweeper::end_game() {
    is_ended_ = true;
}

void Sweeper::replay(int row, int col, int mine_count) {
    grid_.regenerate(row, col, mine_count);
    flagged_count_ = 0;
    is_ended_ = false;
}

}  // namespace ms
