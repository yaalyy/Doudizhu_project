//
//  main.cpp
//  Doudizhu project
//
//  Created by ARCK on 02/02/2021.
//

#include "index.h"
#include <QApplication>

int main(int argc, char *argv[])
{
#if(QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QApplication a(argc, argv);
    Index w;
    w.setWindowTitle("Doudizhu Game");
    w.show();
    return a.exec();
}
