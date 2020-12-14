#include "functionderivation.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FunctionDerivation w;
    w.show();

    return a.exec();
}
