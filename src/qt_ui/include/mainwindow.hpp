#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <cust_diff_form.hpp>
#include <diff_menu.hpp>
#include <game_field.hpp>
#include <QMainWindow>
#include <QStackedWidget>

class Main : public QStackedWidget {
    Q_OBJECT

  public:
    Main(QWidget* parent = nullptr);
    ~Main() override = default;

  private:
    DiffMenu* diff_menu;
    CustDiffForm* cust_diff_form;
    GameField* game_field;

    void init_ui();
    void init_signal_slots();

  private slots:
    void do_start_game(int row, int col, int mine_count);
    void do_cust_diff();
    void do_new_game();
};

#endif  // MAINWINDOW_HPP
