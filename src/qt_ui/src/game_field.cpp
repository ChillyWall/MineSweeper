#include <qsize.h>
#include <game_field.hpp>
#include <ms/Sweeper.hpp>
#include <QEvent>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMouseEvent>
#include <QPushButton>
#include <QVBoxLayout>
#include <QVector>
#include "ms/msdefs.hpp"

GameField::GameField(QWidget* parent)
    : QWidget(parent), sweeper(), icon_nums(9) {
    init_ui();
    init_signal_slots();

    update_callback = [this](int x, int y) { emit update_cell(x, y); };

    QString prefix(":/resources/%1.svg");
    icon_closed = QIcon(prefix.arg("closed"));
    icon_flag = QIcon(prefix.arg("flag"));
    icon_mine = QIcon(prefix.arg("mine"));
    icon_red_mine = QIcon(prefix.arg("red_mine"));
    icon_nums[0] = QIcon(prefix.arg("pressed"));

    for (int i = 1; i < 9; ++i) {
        icon_nums[i] = QIcon(prefix.arg(QString("type%1").arg(i)));
    }
}

GameField::~GameField() {
    auto& grid = sweeper.board();
    size_t btn_num = grid.m() * grid.n();
    size_t capacity = cell_buttons.size();
    for (int i = 0; i < capacity - btn_num; ++i) {
        delete cell_buttons[btn_num + i];
    }
}

void GameField::init_ui() {
    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    main_lay = new QHBoxLayout(this);

    board = new QGroupBox;
    board_lay = new QGridLayout(board);
    board_lay->setContentsMargins(0, 0, 0, 0);
    board_lay->setSpacing(0);

    side_panel = new QGroupBox;
    side_panel_lay = new QVBoxLayout(side_panel);

    scores = new QLabel;
    change_diff_btn = new QPushButton("Change Difficulty");
    start_over_btn = new QPushButton("Start Over");

    side_panel_lay->addWidget(scores);
    side_panel_lay->addWidget(start_over_btn);
    side_panel_lay->addWidget(change_diff_btn);

    main_lay->addWidget(board);
    main_lay->addWidget(side_panel);
}

void GameField::init_signal_slots() {
    connect(start_over_btn, &QPushButton::clicked, this, [this]() {
        auto& grid = sweeper.board();
        init_game(grid.m(), grid.n(), grid.mine_count());
    });
    connect(change_diff_btn, &QPushButton::clicked, this,
            [this]() { emit change_diff(); });

    connect(this, &GameField::update_cell, this, &GameField::do_update_cell);
    connect(this, &GameField::sweep, this, &GameField::do_sweep);
    connect(this, &GameField::auto_sweep, this, &GameField::do_auto_sweep);
    connect(this, &GameField::flag, this, &GameField::do_flag);

    connect(this, &GameField::win_game, this, &GameField::do_win_game);
    connect(this, &GameField::lose_game, this, &GameField::do_lose_game);
}

void GameField::init_game(int row, int col, int mine_count) {
    auto& grid = sweeper.board();
    bool shape_changed = !(row == grid.m() && col == grid.n());
    sweeper.replay(row, col, mine_count);
    if (shape_changed) {
        init_board();
    }
    refresh_board();
    update_score();
}

void GameField::init_board() {
    auto& grid = sweeper.board();
    size_t btn_num = grid.m() * grid.n();
    size_t capacity = cell_buttons.size();
    if (btn_num > capacity) {
        cell_buttons.resize(btn_num);
        for (int i = 0; i < btn_num - capacity; ++i) {
            cell_buttons[capacity + i] = new CellButton;
        }
    }

    for (auto btn : cell_buttons) {
        btn->setParent(nullptr);
        btn->set(-1, -1, nullptr);
    }

    for (int i = 0; i < grid.m(); ++i) {
        for (int j = 0; j < grid.n(); ++j) {
            auto& cell = grid.get_cell(i, j);
            auto btn = cell_buttons[i * grid.n() + j];
            btn->set(i, j, &cell);
            btn->installEventFilter(this);
            board_lay->addWidget(btn, i, j);
        }
    }
}

void GameField::refresh_board() {
    auto& grid = sweeper.board();
    for (int i = 0; i < grid.m(); ++i) {
        for (int j = 0; j < grid.n(); ++j) {
            emit update_cell(i, j);
        }
    }
}

void GameField::do_update_cell(int x, int y) {
    auto& grid = sweeper.board();
    auto& cell = grid.get_cell(x, y);
    auto btn = cell_buttons[x * grid.n() + y];
    switch (cell.status()) {
        case ms::UNKNOWN: {
            btn->setIcon(icon_closed);
            break;
        }
        case ms::FLAGGED: {
            btn->setIcon(icon_flag);
            break;
        }
        case ms::OPEN: {
            switch (cell.type()) {
                case ms::NORMAL_MINE:
                    btn->setIcon(icon_mine);
                    break;
                case ms::SWEPT_MINE:
                    btn->setIcon(icon_red_mine);
                    break;
                case ms::NUMBER:
                    btn->setIcon(icon_nums[cell.num()]);
                    break;
            }
        }
    }
}

void GameField::update_score() {
    scores->setText(QString("Score: %1/%2")
                        .arg(sweeper.flagged_count())
                        .arg(sweeper.board().mine_count()));
}

void GameField::check_sweep(ms::SweepResult result) {
    if (result == ms::SweepResult::MINE) {
        sweeper.sweep_all_mines(update_callback);
        emit lose_game();
    }
    if (sweeper.is_won()) {
        emit win_game();
    }
}

void GameField::do_sweep(int x, int y) {
    auto result = sweeper.sweep(x, y, update_callback);
    check_sweep(result);
}

void GameField::do_auto_sweep(int x, int y) {
    auto result = sweeper.auto_sweep(x, y, update_callback);
    check_sweep(result);
}

void GameField::do_flag(int x, int y) {
    sweeper.flag(x, y);
    update_score();
    emit update_cell(x, y);
    if (sweeper.is_won()) {
        emit win_game();
    }
}

void GameField::do_win_game() {
    scores->setText("You Win!");
    sweeper.end_game();
}
void GameField::do_lose_game() {
    scores->setText("You Lose!");
    sweeper.end_game();
}

bool GameField::eventFilter(QObject* obj, QEvent* event) {
    if (sweeper.is_ended()) {
        return QWidget::eventFilter(obj, event);
    }
    switch (event->type()) {
        case QEvent::MouseButtonPress: {
            auto* btn = qobject_cast<CellButton*>(obj);
            if (!btn) {
                break;
            }
            auto* mouse_event = static_cast<QMouseEvent*>(event);
            switch (mouse_event->button()) {
                case Qt::LeftButton: {
                    if (btn->cell()->status() != ms::UNKNOWN) {
                        break;
                    }
                    emit sweep(btn->x(), btn->y());
                    break;
                }
                case Qt::RightButton: {
                    if (btn->cell()->status() == ms::OPEN) {
                        break;
                    }
                    emit flag(btn->x(), btn->y());
                    break;
                }
                default: {
                }
            }
            break;
        }
        case QEvent::MouseButtonDblClick: {
            auto* btn = qobject_cast<CellButton*>(obj);
            if (!btn) {
                break;
            }
            if (btn->cell()->status() != ms::OPEN) {
                break;
            }
            emit auto_sweep(btn->x(), btn->y());
            break;
        }
        default: {
        }
    }
    return QWidget::eventFilter(obj, event);
}

CellButton::CellButton(QWidget* parent)
    : QPushButton(parent), x_(-1), y_(-1), cell_(nullptr) {
    setIconSize(QSize(24, 24));
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    setContentsMargins(0, 0, 0, 0);
}

int CellButton::x() const {
    return x_;
}

int CellButton::y() const {
    return y_;
}

ms::Cell* CellButton::cell() const {
    return cell_;
}

void CellButton::set(int i, int j, ms::Cell* cell) {
    cell_ = cell;
    x_ = i;
    y_ = j;
}
