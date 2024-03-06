#include "basewindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BaseWindow w;
    w.show();
    return a.exec();
}
