#include <ms/Cell.hpp>
#include <stdexcept>

namespace ms {

Cell::Cell() : stat_(ms::UNKNOWN), num_(0) {}

int Cell::num() const {
    return num_;
}

void Cell::set_num(int number) {
    if (num_ < -2 || num_ > 8) {
        throw std::invalid_argument("invalid number");
    }
    num_ = number;
}

void Cell::set_status(CellStatus status) {
    stat_ = status;
}

CellStatus Cell::status() const {
    return stat_;
}

void Cell::flag() {
    if (stat_ == UNKNOWN) {
        stat_ = FLAGGED;
    }
}

void Cell::unflag() {
    if (stat_ == FLAGGED) {
        stat_ = UNKNOWN;
    }
}

SweepResult Cell::sweep() {
    if (stat_ == UNKNOWN) {
        stat_ = OPEN;
        return num_ == -1 ? MINE : SAFE;
    }
    return SAFE;
}

void Cell::reset() {
    num_ = 0;
    stat_ = UNKNOWN;
}

}  // namespace ms
