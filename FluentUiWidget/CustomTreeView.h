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
    Q_PROPERTY(int target READ target WRITE setTarget NOTIFY targetChanged FINAL)
    int target() const;
    void setTarget(int newTarget);



private:
    void targetChanged();
signals:
private slots:
    void rangeChangedSlot(int _min,int _max);

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    void contextMenuEvent(QContextMenuEvent* event) override;
private:
    int m_target;
};

#endif // CUSTOMTREEVIEW_H
