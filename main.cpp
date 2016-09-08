#include "assembler.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Assembler w;
    w.show();

    return a.exec();
}
