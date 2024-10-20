#ifndef CUSTOMTREEVIEW_H
#define CUSTOMTREEVIEW_H

#include <QWidget>
#include <QTreeView>
#include <QScrollBar>
#include <QPropertyAnimation>
#include <QStyledItemDelegate>

class CustomTreeView : public QTreeView
{
    Q_OBJECT
public:
    explicit CustomTreeView(QWidget *parent = nullptr);
    ~CustomTreeView();
signals:
private:
    bool compareItemY(const QModelIndex& _previous, const QModelIndex& _current);
private slots:

    void onTreeViewClickedSlot(const QModelIndex& index);

private:
    QModelIndex previous_index_; // 上一个点击的节点
};


class CustomDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    CustomDelegate(QObject* parent = nullptr);
    ~CustomDelegate();
    void navigationNodeStateChange(QVariantMap data);
private:
    qreal _lastSelectMarkTop{10};
    qreal _lastSelectMarkBottom{10};
    qreal _selectMarkTop{10};
    qreal _selectMarkBottom{10};
    QPropertyAnimation* _lastSelectMarkTopAnimation{nullptr};
    QPropertyAnimation* _lastSelectMarkBottomAnimation{nullptr};
    QPropertyAnimation* _selectMarkTopAnimation{nullptr};
    QPropertyAnimation* _selectMarkBottomAnimation{nullptr};
    bool _isSelectMarkDisplay{true};
protected:
    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override;
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

signals:
    void targetChanged();
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
