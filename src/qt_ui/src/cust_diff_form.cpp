#include <qwidget.h>
#include <cust_diff_form.hpp>

CustDiffForm::CustDiffForm(QWidget* parent) : QWidget(parent) {
    init_ui();
    init_signal_slots();
}

void CustDiffForm::init_ui() {
    // the layout of the form
    form_lay = new QFormLayout;

    row_label = new QLabel("Rows");
    row_spinbox = new QSpinBox;
    row_spinbox->setMaximum(45);
    form_lay->addRow(row_label, row_spinbox);

    col_label = new QLabel("Columns");
    col_spinbox = new QSpinBox;
    col_spinbox->setMaximum(72);
    form_lay->addRow(col_label, col_spinbox);

    mine_count_label = new QLabel("Mines");
    mine_count_spinbox = new QSpinBox;
    mine_count_spinbox->setMaximum(700);
    form_lay->addRow(mine_count_label, mine_count_spinbox);

    // the layout of the buttons
    btns_lay = new QVBoxLayout;

    start_btn = new QPushButton("Play Game");
    btns_lay->addWidget(start_btn);

    cancel_btn = new QPushButton("Cancel");
    btns_lay->addWidget(cancel_btn);

    // the main layout
    main_lay = new QVBoxLayout;
    main_lay->addLayout(form_lay);
    main_lay->addLayout(btns_lay);
    setLayout(main_lay);
}

void CustDiffForm::init_signal_slots() {
    connect(start_btn, &QPushButton::clicked, this, [this]() {
        emit start_game(row_spinbox->value(), col_spinbox->value(),
                        mine_count_spinbox->value());
    });

    connect(cancel_btn, &QPushButton::clicked, this,
            [this]() { emit new_game(); });
}
