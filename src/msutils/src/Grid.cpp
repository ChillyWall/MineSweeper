#include <ms/Grid.hpp>
#include <random>

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

void Grid::reset_cells() {
    for (auto& cell : cells_) {
        cell.reset();
    }
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

void Grid::regenerate(int m, int n, int count) {
    if (!(m == m_ && n == n_)) {
        cells_.resize(m * n);
    }
    m_ = m;
    n_ = n;
    mine_count_ = count;

    reset_cells();
    generate();
}

}  // namespace ms
