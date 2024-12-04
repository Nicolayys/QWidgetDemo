#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "PageWidget.h"
#include <QMessageBox>
#include "CustomDelegate.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    PageWidget *model_result_widget = new PageWidget(this);
    setCentralWidget(model_result_widget);

    model_result_widget->setColumnWidth(0, 80);
    // model_result_widget->translateHeadNames(field_display_maps_);

    QStandardItemModel * model = new QStandardItemModel(4,3);
    model->setHorizontalHeaderLabels({"测试1","测试2","测试3","测试4","测试5"});
    QStandardItem * item = new QStandardItem("111");
    QStandardItem * item1 = new QStandardItem("222");
    QStandardItem * item2= new QStandardItem("3333");
    model->appendRow(item);
    model->appendRow(item1);
    model->appendRow(item2);

    model_result_widget->setTableViewModel(model);

    // setWindowFlag(Qt::FramelessWindowHint,true);
    setWindowFlag(Qt::CustomizeWindowHint);

    CheckboxDelegate * check_delegate= new CheckboxDelegate(model_result_widget);

    model_result_widget->setDelegateForColumn(0,check_delegate);
}

MainWindow::~MainWindow()
{
    delete ui;
}
