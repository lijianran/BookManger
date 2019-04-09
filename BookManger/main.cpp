#include "mainwindow.h"
#include <QApplication>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
#if(QT_VERSION >= QT_VERSION_CHECK(5,6,0))
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QApplication::setStyle(QStyleFactory::create("Fusion"));
    QApplication app(argc, argv);
    MainWindow w;

    QFont font;
    font.setPixelSize(20);
    app.setFont(font);
//    QFile qss(":/qss/my.qss");
//    qss.open(QFile::ReadOnly);
//    app.setStyleSheet(qss.readAll());
//    qss.close();

    w.show();
    return app.exec();
}
