#include "snake.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Snake w;
    w.show();
    return app.exec(); // 0;
}