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

    // QStandardItemModel *model = new QStandardItemModel(5, 3, this); // 5行2列
    // model->setHorizontalHeaderLabels({"测试1","测试2","测试3","测试4","测试5"});
    // // 设置模型数据
    // for (int row = 0; row < 5; ++row) {
    //     QStandardItem *item = new QStandardItem(row);
    //     item->setCheckable(true);
    //     model->setItem(row, 0, item);
    // }


    // for (int row = 0; row < 5; ++row) {
    //     for (int col = 1; col < 3; ++col) {
    //         QStandardItem *item = new QStandardItem(QString("Row %1, Col %2").arg(row + 1).arg(col + 1));
    //         model->setItem(row, col, item);  // 将创建的项设置到模型中
    //     }
    // }
    // model_result_widget->setModel(model);

    // // setWindowFlag(Qt::FramelessWindowHint,true);
    // setWindowFlag(Qt::CustomizeWindowHint);

    // CheckBoxDelegate * check_delegate= new CheckBoxDelegate(model_result_widget);
    // // CheckboxDelegate * check_delegate= new CheckboxDelegate(model_result_widget);

    // model_result_widget->setDelegateForColumn(0,check_delegate);
    // model_result_widget->exec("SELECT * FROM students");

}

MainWindow::~MainWindow()
{
    delete ui;
}
