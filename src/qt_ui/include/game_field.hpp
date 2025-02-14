#ifndef GAME_FIELD_HPP
#define GAME_FIELD_HPP

#include <functional>
#include <ms/Sweeper.hpp>
#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QIcon>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QVector>
#include <QWidget>
#include "ms/Cell.hpp"

class CellButton : public QPushButton {
    Q_OBJECT

  public:
    CellButton(QWidget* parent = nullptr);
    ~CellButton() override = default;

    void set(int i, int j, ms::Cell* cell);
    int x() const;
    int y() const;

    ms::Cell* cell() const;

  private:
    int x_;
    int y_;
    ms::Cell* cell_;
};

class GameField : public QWidget {
    Q_OBJECT

  public:
    GameField(QWidget* parent = nullptr);
    ~GameField() override;

    void init_game(int row, int col, int mine_count);

  signals:
    void change_diff();

    void update_cell(int x, int y);

    void sweep(int x, int y);
    void auto_sweep(int x, int y);
    void flag(int x, int y);

    void win_game();
    void lose_game();

  private slots:
    void do_update_cell(int x, int y);

    void do_sweep(int x, int y);
    void do_auto_sweep(int x, int y);
    void do_flag(int x, int y);

    void do_win_game();
    void do_lose_game();

  private:
    QHBoxLayout* main_lay;
    QGroupBox* board;
    QGroupBox* side_panel;
    QGridLayout* board_lay;
    QVBoxLayout* side_panel_lay;
    QLabel* scores;
    QPushButton* change_diff_btn;
    QPushButton* start_over_btn;

    ms::Sweeper sweeper;

    QVector<CellButton*> cell_buttons;

    void init_ui();
    void init_signal_slots();
    void init_board();
    void refresh_board();
    void update_score();
    void check_sweep(ms::SweepResult);

    std::function<void(int, int)> update_callback;

    QIcon icon_closed;
    QIcon icon_flag;
    QIcon icon_mine;
    QIcon icon_red_mine;
    QVector<QIcon> icon_nums;

  protected:
    bool eventFilter(QObject* obj, QEvent* event) override;
};

#endif  // FIELD_HPP
