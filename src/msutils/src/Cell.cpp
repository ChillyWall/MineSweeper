#include <ms/Cell.hpp>
#include <stdexcept>

namespace ms {

Cell::Cell() : stat_(ms::UNKNOWN), num_(0) {}

int Cell::num() const {
    if (num_ < 0 || num_ > 8) {
        throw std::invalid_argument(
            "invalid number, the number should be 0 ~ 8");
    }
    return num_;
}

void Cell::set_num(int number) {
    if (num_ < 0 || num_ > 8) {
        throw std::invalid_argument(
            "invalid number, the number should be 0 ~ 8");
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
        return num_ < 0 ? MINE : SAFE;
    }
    return SAFE;
}

void Cell::reset() {
    num_ = 0;
    stat_ = UNKNOWN;
}

void Cell::set_mine() {
    num_ = -1;
}

void Cell::set_mine_swept() {
    if (num_ != -1) {
        throw NotMine();
    }
    num_ = -2;
}

CellType Cell::type() const {
    switch (num_) {
        case -2:
            return SWEPT_MINE;
        case -1:
            return NORMAL_MINE;
        default:
            return NUMBER;
    }
}

}  // namespace ms
