#include "CustomTreeView.h"

#include <QDebug>
#include <QHeaderView>
#include <QModelIndex>
#include <QMouseEvent>
#include <QPainter>
#include <QScrollBar>
#include <QScroller>

CustomTreeView::CustomTreeView(QWidget *parent)
    : QTreeView{parent}
{
    setStyleSheet(
        "QTreeView{background-color: transparent;border:0px;}"
        "QTreeView::branch{image:none;}");
    setAnimated(true);
    setHeaderHidden(true);
    //去掉根节点装饰
    setRootIsDecorated(false);
    // 禁用双击展开
    setExpandsOnDoubleClick(false);
    // 禁用选择功能
    setSelectionMode(QAbstractItemView::NoSelection);
    // 设置表头的列宽自动调整模式
    header()->setSectionResizeMode(QHeaderView::Stretch);
    // 隐藏水平滚动条
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // ElaScrollBar* vScrollBar = new ElaScrollBar(this);
    // vScrollBar->setisAnimation(true);
    // setVerticalScrollBar(vScrollBar);

}

CustomTreeView::~CustomTreeView()
{
}

CustomScrollbar::CustomScrollbar(QWidget *parent)
    :QScrollBar(parent)
{

}

CustomScrollbar::~CustomScrollbar()
{

}

void CustomScrollbar::mousePressEvent(QMouseEvent *event)
{

}

void CustomScrollbar::mouseReleaseEvent(QMouseEvent *event)
{

}

void CustomScrollbar::mouseMoveEvent(QMouseEvent *event)
{

}

void CustomScrollbar::wheelEvent(QWheelEvent *event)
{

}

void CustomScrollbar::contextMenuEvent(QContextMenuEvent *event)
{

}
