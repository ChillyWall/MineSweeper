#include <qwidget.h>
#include <cust_diff_form.hpp>

CustDiffForm::CustDiffForm(QWidget* parent) : QWidget(parent) {
    init_ui();
    init_signal_slots();
}

void CustDiffForm::init_ui() {
    main_lay = new QVBoxLayout;
    setLayout(main_lay);

    // the layout of the form
    form_lay = new QFormLayout;

    row_label = new QLabel("Rows", this);
    row_spinbox = new QSpinBox(this);

    col_label = new QLabel("Columns", this);
    col_spinbox = new QSpinBox(this);

    mine_count_label = new QLabel("Mines", this);
    mine_count_spinbox = new QSpinBox(this);

    form_lay->addRow(row_label, row_spinbox);
    form_lay->addRow(col_label, col_spinbox);
    form_lay->addRow(mine_count_label, mine_count_spinbox);

    // the layout of the buttons
    btns_lay = new QVBoxLayout(this);

    start_btn = new QPushButton("Play Game", this);
    cancel_btn = new QPushButton("Cancel", this);

    btns_lay->addWidget(start_btn);
    btns_lay->addWidget(cancel_btn);

    // the main layout
    main_lay->addLayout(form_lay);
    main_lay->addLayout(btns_lay);
}

void CustDiffForm::init_signal_slots() {
    connect(start_btn, &QPushButton::clicked, this, [this]() {
        emit start_game(row_spinbox->value(), col_spinbox->value(), mine_count_spinbox->value());
    });

    connect(cancel_btn, &QPushButton::clicked, this, [this]() { emit new_game(); });
}
