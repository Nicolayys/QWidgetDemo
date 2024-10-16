#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initWindow();

    //额外布局
    initEdgeLayout();

    //中心窗口
    initContent();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initWindow()
{

}

void MainWindow::initEdgeLayout()
{

}

void MainWindow::initContent()
{

}
