#include "PageWidget.h"
#include "ui_PageWidget.h"

PageWidget::PageWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PageWidget)
{
    ui->setupUi(this);
}

PageWidget::~PageWidget()
{
    delete ui;
}