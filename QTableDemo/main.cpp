#include "MainWindow.h"

#include <QApplication>
#include "PageWidget.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // MainWindow w;
    // w.show();

    PageWidget *wid = new PageWidget(nullptr);
    wid->setGeometry(50,50,400,400);
    wid->show();
    return a.exec();
}
