#include <diff_menu.hpp>
#include <QPushButton>
#include <QString>

DiffMenu::DiffMenu(QWidget* parent) : QWidget(parent) {
    init_ui();
    init_signal_slots();
}

void DiffMenu::init_ui() {
    QString style("QPushButton { text-align: center }");

    easy_diff_btn = new QPushButton;
    easy_diff_btn->setText(QString::fromUtf8("8 \u00D7 8\n10mines"));
    easy_diff_btn->setStyleSheet(style);

    medium_diff_btn = new QPushButton;
    medium_diff_btn->setText(QString::fromUtf8("16 \u00D7 16\n40mines"));
    medium_diff_btn->setStyleSheet(style);

    hard_diff_btn = new QPushButton;
    hard_diff_btn->setText(QString::fromUtf8("16 \u00D7 30\n99mines"));
    hard_diff_btn->setStyleSheet(style);

    cust_diff_btn = new QPushButton;
    cust_diff_btn->setText("?\nCustom");
    cust_diff_btn->setStyleSheet(style);

    diffs_layout = new QGridLayout;
    diffs_layout->addWidget(easy_diff_btn, 0, 0);
    diffs_layout->addWidget(medium_diff_btn, 0, 1);
    diffs_layout->addWidget(hard_diff_btn, 1, 0);
    diffs_layout->addWidget(cust_diff_btn, 1, 1);
    setLayout(diffs_layout);
}

void DiffMenu::init_signal_slots() {
    connect(easy_diff_btn, &QPushButton::clicked, this, [this]() { emit start_game(8, 8, 10); });
    connect(medium_diff_btn, &QPushButton::clicked, this,
            [this]() { emit start_game(16, 16, 40); });
    connect(hard_diff_btn, &QPushButton::clicked, this, [this]() { emit start_game(16, 30, 99); });
    connect(cust_diff_btn, &QPushButton::clicked, this, [this]() { emit cust_diff(); });
}
