#include "index.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Index w;
    w.setWindowTitle("Doudizhu Game");
    w.show();
    return a.exec();
}
