#include "MainWindow.h"
#include <QApplication>
#include <QTranslator>
#include "Util.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator qtTranslator;
    qtTranslator.load(Util::getResourcePath() + "PaperMahjong.qm");
    a.installTranslator(&qtTranslator);

    MainWindow w;
    w.show();

    return a.exec();
}
