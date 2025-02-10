#ifndef GAME_FIELD_HPP
#define GAME_FIELD_HPP

#include <ms/Sweeper.hpp>
#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
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

    void set(int x, int y, ms::Cell* cell);
    int x() const;
    int y() const;

    ms::Cell* cell() const;

  private:
    int x_;
    int y_;
    ms::Cell* cell_;

    void init_ui();
    void init_signal_slots();
};

class GameField : public QWidget {
    Q_OBJECT

  public:
    GameField(QWidget* parent = nullptr);
    ~GameField() override = default;

    void init_game(int row, int col, int mine_count);

  signals:
    void new_game();
    void update_cell(int x, int y);

  private slots:
    void do_update_cell(int x, int y);

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

    QVector<CellButton> cell_buttons;

    void init_ui();
    void init_signal_slots();

  protected:
    bool eventFilter(QObject* obj, QEvent* event) override;
};

#endif  // FIELD_HPP
