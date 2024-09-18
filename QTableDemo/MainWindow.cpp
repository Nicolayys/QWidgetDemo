#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    PageWidget *wid = new PageWidget(this);
    setCentralWidget(wid);
    QFile qss_file(":/res/file/ac_software.qss");
    if (qss_file.open(QFile::ReadOnly))
    {
        qApp->setStyleSheet(qss_file.readAll());
        qss_file.close();
    }
    else{
        QMessageBox::warning(nullptr,"qss","加载qss文件失败");
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}
