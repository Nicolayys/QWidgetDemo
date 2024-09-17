#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    PageWidget *wid = new PageWidget(this);
    wid->setGeometry(50,50,400,400);
    wid->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::execSqlWork(const QString &_exec_sql)
{

}
