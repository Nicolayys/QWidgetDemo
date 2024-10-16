#ifndef CUSTOMTREEVIEW_H
#define CUSTOMTREEVIEW_H

#include <QWidget>
#include <QTreeView>
#include <QScrollBar>



class CustomTreeView : public QTreeView
{
    Q_OBJECT
public:
    explicit CustomTreeView(QWidget *parent = nullptr);
    ~CustomTreeView();
signals:
};

class CustomScrollbar : public QScrollBar
{

    Q_OBJECT
public:
    explicit CustomScrollbar(QWidget *parent = nullptr);
    ~CustomScrollbar();

signals:


protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    void contextMenuEvent(QContextMenuEvent* event) override;
};

#endif // CUSTOMTREEVIEW_H
