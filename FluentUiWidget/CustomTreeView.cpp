#include "CustomTreeView.h"

#include <QDebug>
#include <QHeaderView>
#include <QModelIndex>
#include <QMouseEvent>
#include <QPainter>
#include <QScrollBar>
#include <QScroller>
#include <QPropertyAnimation>
#include <QDebug>
CustomTreeView::CustomTreeView(QWidget *parent)
    : QTreeView{parent}
{
    setStyleSheet(
        "QTreeView{background-color: transparent;border:0px;}"
        "QTreeView::branch{image:none;}");
    setAnimated(true);
    setHeaderHidden(true);
    /* 去掉根节点装饰 */
    setRootIsDecorated(false);
    /* 禁用双击展开 */
    setExpandsOnDoubleClick(false);
    /* 禁用选择功能 */
    setSelectionMode(QAbstractItemView::NoSelection);
    /* 设置表头的列宽自动调整模式 */
    header()->setSectionResizeMode(QHeaderView::Stretch);
    /* 隐藏水平滚动条 */
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // ElaScrollBar* vScrollBar = new ElaScrollBar(this);
    // vScrollBar->setisAnimation(true);
    // setVerticalScrollBar(vScrollBar);


    /* 使用鼠标左键的拖动手势来进行滚动操作 */
    QScroller::grabGesture(this->viewport(), QScroller::LeftMouseButtonGesture);
    /* 获取当前滚动控件的属性 */
    QScrollerProperties properties = QScroller::scroller(this->viewport())->scrollerProperties();
#if (QT_VERSION < QT_VERSION_CHECK(6, 5, 3))
    properties.setScrollMetric(QScrollerProperties::MousePressEventDelay, 0);
#endif
    /* 禁用水平方向上的滚动过冲效果 */
    properties.setScrollMetric(QScrollerProperties::HorizontalOvershootPolicy, QScrollerProperties::OvershootAlwaysOff);
    /* 启用垂直方向上的过冲效果 */
    properties.setScrollMetric(QScrollerProperties::VerticalOvershootPolicy, QScrollerProperties::OvershootAlwaysOn);
    /* 设置拖动阻尼系数 */
    properties.setScrollMetric(QScrollerProperties::OvershootDragResistanceFactor, 0.35);
    /* 设置过冲恢复的时间 */
    properties.setScrollMetric(QScrollerProperties::OvershootScrollTime, 0.5);
    /* 设置帧率 */
    properties.setScrollMetric(QScrollerProperties::FrameRate, QScrollerProperties::Fps60);
    /* 应用自定义属性 */
    QScroller::scroller(this->viewport())->setScrollerProperties(properties);

    connect(this,&CustomTreeView::clicked,this,&CustomTreeView::onTreeViewClickedSlot);

}
void CustomTreeView::onTreeViewClickedSlot(const QModelIndex& index)
{

}
CustomTreeView::~CustomTreeView()
{
}

bool CustomTreeView::compareItemY(const QModelIndex &_previous, const QModelIndex &_current)
{
    int previous_row = _previous.row();
    int current_row = _current.row();

    /* 比较行号 */
    if (current_row < previous_row) {
        return true;
    }
    return false;
}

CustomScrollbar::CustomScrollbar(QWidget *parent)
    :QScrollBar(parent)
{
    /* 设置滚动条的单步增量为1 */
    setSingleStep(1);
    /* 保持部分透明的绘制效果 */
    setAttribute(Qt::WA_OpaquePaintEvent,false);
    /* 设置滚动条样式 */

    // setStyle();
    connect(this,&CustomScrollbar::rangeChanged,this,&CustomScrollbar::rangeChangedSlot);
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

int CustomScrollbar::target() const
{
    return m_target;
}

void CustomScrollbar::setTarget(int newTarget)
{
    if (m_target == newTarget)
        return;
    m_target = newTarget;
    emit targetChanged();
}

void CustomScrollbar::rangeChangedSlot(int _min, int _max)
{
    if(this->isVisible()&& _max != 0){
        QPropertyAnimation * range_animation = new QPropertyAnimation(this,"");
        /* 设置缓动曲线*/
        range_animation->setEasingCurve(QEasingCurve::OutSine);
        range_animation->setDuration(250);
        range_animation->setStartValue(m_target);
        range_animation->setEndValue(_max);
        range_animation->start(QAbstractAnimation::DeleteWhenStopped);

    }
}



CustomDelegate::CustomDelegate(QObject *parent): QStyledItemDelegate(parent)
{
    setProperty("lastSelectMarkTop", 10.0);
    setProperty("lastSelectMarkBottom", 10.0);
    setProperty("selectMarkTop", 10.0);
    setProperty("selectMarkBottom", 10.0);
    // Mark向上
    _lastSelectMarkTopAnimation = new QPropertyAnimation(this, "lastSelectMarkTop");
    connect(_lastSelectMarkTopAnimation, &QPropertyAnimation::valueChanged, this, [=](const QVariant& value) {
        _lastSelectMarkTop = value.toReal();
       /* d->_pNavigationView->viewport()->update();*/ });
    _lastSelectMarkTopAnimation->setDuration(300);
    _lastSelectMarkTopAnimation->setEasingCurve(QEasingCurve::InOutSine);

    _selectMarkBottomAnimation = new QPropertyAnimation(this, "selectMarkBottom");
    connect(_selectMarkBottomAnimation, &QPropertyAnimation::valueChanged, this, [=](const QVariant& value) {
        _selectMarkBottom = value.toReal();
        /*d->_pNavigationView->viewport()->update();*/ });
    _selectMarkBottomAnimation->setDuration(300);
    _selectMarkBottomAnimation->setEasingCurve(QEasingCurve::InOutSine);
    connect(_lastSelectMarkTopAnimation, &QPropertyAnimation::finished, this, [=]() {
        _isSelectMarkDisplay = true;
        // _lastSelectedNode = nullptr;
        _selectMarkBottomAnimation->setStartValue(0);
        _selectMarkBottomAnimation->setEndValue(10);
        _selectMarkBottomAnimation->start(); });

    // Mark向下
    // d->_lastSelectMarkBottomAnimation = new QPropertyAnimation(this, "lastSelectMarkBottom");
    // connect(d->_lastSelectMarkBottomAnimation, &QPropertyAnimation::valueChanged, this, [=](const QVariant& value) {
    //     d->_lastSelectMarkBottom =  value.toReal();
    //     d->_pNavigationView->viewport()->update(); });
    // d->_lastSelectMarkBottomAnimation->setDuration(300);
    // d->_lastSelectMarkBottomAnimation->setEasingCurve(QEasingCurve::InOutSine);

    // d->_selectMarkTopAnimation = new QPropertyAnimation(this, "selectMarkTop");
    // connect(d->_selectMarkTopAnimation, &QPropertyAnimation::valueChanged, this, [=](const QVariant& value) {
    //     d->_selectMarkTop =  value.toReal();
    //     d->_pNavigationView->viewport()->update(); });
    // d->_selectMarkTopAnimation->setDuration(300);
    // d->_selectMarkTopAnimation->setEasingCurve(QEasingCurve::InOutSine);
    // connect(d->_lastSelectMarkBottomAnimation, &QPropertyAnimation::finished, this, [=]() {
    //     d->_isSelectMarkDisplay = true;
    //     d->_lastSelectedNode = nullptr;
    //     d->_selectMarkTopAnimation->setStartValue(0);
    //     d->_selectMarkTopAnimation->setEndValue(10);
    //     d->_selectMarkTopAnimation->start(); });
}

CustomDelegate::~CustomDelegate()
{
}

void CustomDelegate::navigationNodeStateChange(QVariantMap data)
{
    int previous_row = previous_index_.row();
    int current_row = index.row();

    if(current_row < previous_row){
        _lastSelectMarkTopAnimation->setStartValue(10);
        _lastSelectMarkTopAnimation->setEndValue(0);
        _lastSelectMarkTopAnimation->start();
        _lastSelectMarkBottomAnimation->stop();
        _selectMarkTopAnimation->stop();
        _isSelectMarkDisplay = false;

    }else{

        _lastSelectMarkBottomAnimation->setStartValue(10);
        _lastSelectMarkBottomAnimation->setEndValue(0);
        _lastSelectMarkBottomAnimation->start();
        _lastSelectMarkTopAnimation->stop();
        _selectMarkBottomAnimation->stop();
        _isSelectMarkDisplay = false;
    }
}

void CustomDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyledItemDelegate::paint(painter, option, index);
}

QSize CustomDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QSize size = QStyledItemDelegate::sizeHint(option, index);
    size.setHeight(40);
    return size;
}


