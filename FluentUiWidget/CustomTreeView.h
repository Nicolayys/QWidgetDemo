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
    void sendModelIndexSignal(const QModelIndex &index);
private:


private slots:

    void onTreeViewClickedSlot(const QModelIndex& index);

private:
    QModelIndex previous_index_; // 上一个点击的节点
};


class CustomDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    CustomDelegate(CustomTreeView* _tree_view,QObject* parent = nullptr);
    ~CustomDelegate();

public slots:
    void sendModelIndexSlot(const QModelIndex &index);
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

    CustomTreeView * tree_view_;  // 存储传入的 QTreeView 指针

    QModelIndex previous_index_;  // 保存上一个节点
    QModelIndex current_index_;   // 当前节点
private:
    bool compareItemY(const QModelIndex& _current, const QModelIndex& _previous);
protected:
    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) override;
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
