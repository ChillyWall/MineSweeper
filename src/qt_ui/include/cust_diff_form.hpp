#ifndef CUST_DIFF_FORM_HPP
#define CUST_DIFF_FORM_HPP

#include <QFormLayout>
#include <QLabel>
#include <QPushButton>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QWidget>

class CustDiffForm : public QWidget {
    Q_OBJECT

  public:
    CustDiffForm(QWidget* parent = nullptr);
    ~CustDiffForm() override = default;

  signals:
    void new_game();
    void start_game(int row, int col, int mine_count);

  private:
    QVBoxLayout* main_lay;
    QFormLayout* form_lay;
    QVBoxLayout* btns_lay;

    QLabel* row_label;
    QLabel* col_label;
    QLabel* mine_count_label;

    QSpinBox* row_spinbox;
    QSpinBox* col_spinbox;
    QSpinBox* mine_count_spinbox;

    QPushButton* start_btn;
    QPushButton* cancel_btn;

    void init_ui();
    void init_signal_slots();
};

#endif  // CUST_DIFF_FORM_HPP
