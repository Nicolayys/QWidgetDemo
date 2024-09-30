#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    PageWidget *model_result_widget = new PageWidget(this);
    setCentralWidget(model_result_widget);
    QFile qss_file(":/res/file/ac_software.qss");
    if (qss_file.open(QFile::ReadOnly))
    {
        qApp->setStyleSheet(qss_file.readAll());
        qss_file.close();
    }
    else{
        QMessageBox::warning(nullptr,"qss","加载qss文件失败");
    }


    model_result_widget->setColumnWidth(0, 80);
    // model_result_widget->translateHeadNames(field_display_maps_);
}

MainWindow::~MainWindow()
{
    delete ui;
}
