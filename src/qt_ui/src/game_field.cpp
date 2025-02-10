#include <qobject.h>
#include <game_field.hpp>
#include <ms/Sweeper.hpp>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QVector>

GameField::GameField(QWidget* parent) : QWidget(parent), sweeper() {
    init_ui();
    init_signal_slots();
}

void GameField::init_ui() {
    main_lay = new QHBoxLayout(this);
    board = new QGroupBox(this);
    board_lay = new QGridLayout(board);
    board->setLayout(board_lay);

    side_panel = new QGroupBox(this);
    side_panel_lay = new QVBoxLayout(side_panel);
    side_panel->setLayout(side_panel_lay);

    scores = new QLabel(this);
    change_diff_btn = new QPushButton("Change Difficulty", this);
    start_over_btn = new QPushButton("Start Over", this);

    side_panel_lay->addWidget(scores);
    side_panel_lay->addWidget(start_over_btn);
    side_panel_lay->addWidget(change_diff_btn);

    main_lay->addWidget(board);
    main_lay->addWidget(side_panel);
}

void GameField::init_signal_slots() {
    connect(this, &GameField::update_cell, this, &GameField::do_update_cell);
    connect(start_over_btn, &QPushButton::clicked, [this]() {
        sweeper.replay(sweeper.board().m(), sweeper.board().n(), sweeper.board().mine_count());
        for (int i = 0; i < sweeper.board().m(); i++) {
            for (int j = 0; j < sweeper.board().n(); j++) {
                emit update_cell(i, j);
            }
        }
    });
}

bool GameField::eventFilter(QObject* obj, QEvent* event) {
    return false;
}

void GameField::init_game(int row, int col, int mine_count) {
    if (!(row == sweeper.board().m() && col == sweeper.board().n())) {}

    sweeper.replay(row, col, mine_count);
    for (int i = 0; i < sweeper.board().m(); i++) {
        for (int j = 0; j < sweeper.board().n(); j++) {}
    }
}

CellButton::CellButton(QWidget* parent) : QPushButton(parent), x_(0), y_(0), cell_(nullptr) {
    init_ui();
    init_signal_slots();
}
