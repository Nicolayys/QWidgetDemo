#include "MainWindow.h"

#include <QApplication>
#include <QFileInfo>
#include <QMessageBox>
#include <QResource>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 1. 通过文件加载样式表
    // QFile qss_file(":/res/file/ac_software.qss");
    // if (qss_file.open(QFile::ReadOnly))
    // {
    //     qApp->setStyleSheet(qss_file.readAll());
    //     qss_file.close();
    // }
    // else{
    //     QMessageBox::warning(nullptr,"qss","加载qss文件失败");
    // }
    //Qt中使用二进制资源文件方法如下
    //将qrc编译为二进制文件rcc，在控制台执行下列命令
    // rcc -binary qss.qrc -o qss.rcc

    // 2. 通过命令加载样式表 可执行程序执行后仍可以替换样式表
    QFileInfo rcc_file(qApp->applicationDirPath() + "/../qss.rcc");
    QString rcc_path = rcc_file.absoluteFilePath();
    bool flag = QResource::registerResource(rcc_path);
    MainWindow w;
    w.show();


    return a.exec();
}
