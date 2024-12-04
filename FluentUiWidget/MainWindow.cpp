#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QTreeView>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QVBoxLayout>
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


    // 创建QStandardItemModel
    QStandardItemModel* model = new QStandardItemModel();

    // 设置树的头
    model->setHorizontalHeaderLabels({"Category"});

    // 插入顶层项
    QStandardItem* rootItem = new QStandardItem();
    QStandardItem* descItem = new QStandardItem();
    rootItem->setData("Root Node1",Qt::UserRole+1);
    descItem->setData("Root Node2",Qt::UserRole+1);
    model->appendRow(rootItem);
    model->appendRow(descItem);

    QStandardItem* rootItem1 = new QStandardItem();
    QStandardItem* descItem1 = new QStandardItem();

    // rootItem1->setData("Root Node3",Qt::UserRole+1);
    // descItem1->setData("Root Node4",Qt::UserRole+1);
    // model->appendRow(rootItem1);
    // model->appendRow(descItem1);

    // 插入子节点
    QStandardItem* childItem1 = new QStandardItem("Child 1");
    QStandardItem* childDesc1 = new QStandardItem("Description of Child 1");
    rootItem->appendRow(childItem1);
    rootItem->appendRow(childDesc1);

    // QStandardItem* childItem2 = new QStandardItem("Child 2");
    // QStandardItem* childDesc2 = new QStandardItem("Description of Child 2");

    // rootItem->appendRow(childItem2);
    // rootItem->appendRow(childDesc2);

    // 将模型设置到QTreeView
    ui->tree_view_->setModel(model);

    // 展开所有节点
    ui->tree_view_->expandAll();


    CustomDelegate * delegate = new CustomDelegate(ui->tree_view_);
    ui->tree_view_->setItemDelegateForColumn(0, delegate);

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
