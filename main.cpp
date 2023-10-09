#include "omermainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    OmerMainWindow w;
    w.show();
    return a.exec();
}
