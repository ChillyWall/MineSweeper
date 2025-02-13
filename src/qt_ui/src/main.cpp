#include <mainwindow.hpp>
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Main main;
    main.show();
    app.setStyleSheet("CellButton { padding: 0px; margin: 0px; }");

    return app.exec();
}
