#include "handler.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Handler handler;
    return a.exec();
}
