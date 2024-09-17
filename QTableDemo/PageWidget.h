#ifndef PAGEWIDGET_H
#define PAGEWIDGET_H

#include <QWidget>
#include <QTableView>
#include <QToolButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QLabel>
#include <QHeaderView>
#include <QStandardItemModel>
#include <QtConcurrent/QtConcurrent>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QIntValidator>
#include <QListWidget>
#include <QPushButton>
#include <QMouseEvent>
#include <QPainter>
namespace Ui {
class PageWidget;
}

class PageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PageWidget(QWidget *parent = nullptr);
    ~PageWidget();

private:
    Ui::PageWidget *ui;
};

#endif // PAGEWIDGET_H
