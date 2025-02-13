#include <mainwindow.hpp>

Main::Main(QWidget* parent) : QStackedWidget(parent) {
    init_ui();
    init_signal_slots();
}

void Main::init_ui() {
    diff_menu = new DiffMenu;
    cust_diff_form = new CustDiffForm;
    game_field = new GameField;

    addWidget(diff_menu);
    addWidget(cust_diff_form);
    addWidget(game_field);

    setCurrentWidget(diff_menu);
}

void Main::init_signal_slots() {
    connect(diff_menu, &DiffMenu::start_game, this, &Main::do_start_game);
    connect(diff_menu, &DiffMenu::cust_diff, this, &Main::do_cust_diff);

    connect(cust_diff_form, &CustDiffForm::start_game, this,
            &Main::do_start_game);
    connect(cust_diff_form, &CustDiffForm::new_game, this, &Main::do_new_game);

    connect(game_field, &GameField::change_diff, this, &Main::do_new_game);
}

void Main::do_start_game(int row, int col, int mine_count) {
    game_field->init_game(row, col, mine_count);
    setCurrentWidget(game_field);
}

void Main::do_cust_diff() {
    setCurrentWidget(cust_diff_form);
}

void Main::do_new_game() {
    setCurrentWidget(diff_menu);
}
