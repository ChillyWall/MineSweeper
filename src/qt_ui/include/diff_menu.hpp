#ifndef DIFF_MENU_HPP
#define DIFF_MENU_HPP

#include <QGridLayout>
#include <QPushButton>
#include <QWidget>

class DiffMenu : public QWidget {
    Q_OBJECT

  public:
    DiffMenu(QWidget* parent = nullptr);
    ~DiffMenu() override = default;

  signals:
    void start_game(int row, int col, int mine_count);
    void cust_diff();

  private:
    QGridLayout* diffs_layout;

    QPushButton* easy_diff_btn;
    QPushButton* medium_diff_btn;
    QPushButton* hard_diff_btn;
    QPushButton* cust_diff_btn;

    void init_ui();
    void init_signal_slots();
};

#endif  // DIFF_MENU_HPP
