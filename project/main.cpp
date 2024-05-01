#include <QApplication>
#include "dbvisual.h"
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    dbVisual window;
    window.show();

    return app.exec();
}
