#include <pybind11/pybind11.h>
#include "Tables.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Tables w;
    w.show();
    return a.exec();
}
