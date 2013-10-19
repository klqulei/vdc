

#include "vscmainwindows.h"
#include <QtWidgets/QApplication>
#include <QStyleFactory>
#include "factory.hpp"
#include <QPixmap>
#include <QSplashScreen>
#include <QtWidgets/QMainWindow>

Debug * Debug::gDebug = NULL;
thread * Debug::gThread = NULL;

Factory *gFactory = NULL;

int main(int argc, char *argv[])
{
    int dummy = errno;
    QApplication a(argc, argv);
    Debug::init(0);

    QPixmap pixmap(":/logo/resources/splash.png");
    QSplashScreen *splash = new QSplashScreen(pixmap);
    splash->show();

    QApplication::setStyle(QStyleFactory::create("Fusion"));
	gFactory = new Factory;

    gFactory->Init();

    VSCMainWindows w;
    //w.setWindowIcon(QIcon(":/logo/resources/vscsmall.jpg"));
    //w.show();
    Sleep(1000);
    //w.setWindowFlags(Qt::FramelessWindowHint );
    w.showMaximized();
    //w.showFullScreen();
    splash->finish(&w);

    delete splash;
    return a.exec();
}
