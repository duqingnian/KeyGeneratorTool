#include "generatortool.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QIcon appIcon(":/res/icons/ico.png");
    a.setWindowIcon(appIcon);

    GeneratorTool w;
    w.show();

    return a.exec();
}
