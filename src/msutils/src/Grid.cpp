#include <ms/Grid.hpp>
#include <random>
#include "ms/msdefs.hpp"

namespace ms {

Grid::Grid(int m, int n, int count) : cells_(m * n), m_(m), n_(n), mine_count_(count) {
    generate();
}

const Cell& Grid::get_cell(int m, int n) const {
    return cells_.at(m * n_ + n);
}

Cell& Grid::get_cell(int m, int n) {
    return const_cast<Cell&>(static_cast<const Grid*>(this)->get_cell(m, n));
}

int Grid::m() const {
    return m_;
}

int Grid::n() const {
    return n_;
}

int Grid::mine_count() const {
    return mine_count_;
}

int Grid::flagged_count() const {
    return flagged_count_;
}

void Grid::generate() {
    std::random_device rd;
    std::default_random_engine e(rd());
    std::uniform_int_distribution<int> xgen(0, m_ - 1);
    std::uniform_int_distribution<int> ygen(0, n_ - 1);

    int count = 0;
    while (count < mine_count_) {
        int x = xgen(e);
        int y = ygen(e);

        auto& tmp_cell = cells_.at(x * n_ + y);
        if (tmp_cell.num() != -1) {
            ++count;
            tmp_cell.set_num(-1);
            update_num(x, y);
        }
    }
}

void Grid::update_num(int x, int y) {
    for (int i = x - 1; i <= x + 1; ++i) {
        for (int j = y - 1; j <= y + 1; ++j) {
            if (i < 0 || i >= m_ || j < 0 || j >= n_ || (i == x && j == y)) {
                continue;
            }

            auto& tmp_cell = cells_.at(i * n_ + j);
            if (tmp_cell.num() == -1) {
                continue;
            }

            tmp_cell.set_num(tmp_cell.num() + 1);
        }
    }
}

SweepResult Grid::sweep(int x, int y) {
    auto& tmp_cell = get_cell(x, y);
    SweepResult res;
    switch (tmp_cell.status()) {
        case UNKNOWN: {
            res = tmp_cell.sweep();
            if (res == SAFE && tmp_cell.num() == 0) {
                sweep_around(x, y);
            }
            break;
        }
        case FLAGGED: {
            res = SAFE;
            break;
        }
        case OPEN: {
            res = auto_sweep(x, y);
            break;
        }
    }
    return res;
}

SweepResult Grid::sweep_around(int x, int y) {
    SweepResult res = SAFE;
    for (int i = x - 1; i <= x + 1; ++i) {
        for (int j = y - 1; j <= y + 1; ++j) {
            if (i < 0 || i >= m_ || j < 0 || j >= n_ || (i == x && j == y)) {
                continue;
            }

            auto& tmp_cell = get_cell(i, j);
            if (tmp_cell.status() == UNKNOWN) {
                if (sweep(i, j) == MINE) {
                    res = MINE;
                }
            }
        }
    }
    return res;
}

SweepResult Grid::auto_sweep(int x, int y) {
    auto& cell = get_cell(x, y);
    int count = 0;
    for (int i = x - 1; i <= x + 1; ++i) {
        for (int j = y - 1; j <= y + 1; ++j) {
            if (i < 0 || i >= m_ || j < 0 || j >= n_ || (i == x && j == y)) {
                continue;
            }

            if (get_cell(i, j).status() == FLAGGED) {
                ++count;
            }
        }
    }

    if (count == cell.num()) {
        return sweep_around(x, y);
    }

    return SAFE;
}

void Grid::flag(int x, int y) {
    auto& tmp_cell = get_cell(x, y);
    if (tmp_cell.status() == UNKNOWN) {
        tmp_cell.flag();
        ++flagged_count_;
    } else {
        tmp_cell.unflag();
        --flagged_count_;
    }
}

void Grid::sweep_all() {
    for (int i = 0; i < m_; ++i) {
        for (int j = 0; j < n_; ++j) {
            auto& tmp_cell = get_cell(i, j);
            if (tmp_cell.status() == UNKNOWN) {
                tmp_cell.sweep();
            }
        }
    }
}

bool Grid::is_finished() const {
    if (flagged_count_ != mine_count_) {
        return false;
    }
    for (int i = 0; i < m_; ++i) {
        for (int j = 0; j < n_; ++j) {
            if (get_cell(i, j).status() == UNKNOWN) {
                return false;
            }
        }
    }
    return true;
}

}  // namespace ms
