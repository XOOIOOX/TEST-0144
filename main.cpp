#include "TEST0144.h"
#include <QtWidgets/QApplication>

CommonBus commonBus;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TEST0144 w;
    w.show();
    return a.exec();
}
