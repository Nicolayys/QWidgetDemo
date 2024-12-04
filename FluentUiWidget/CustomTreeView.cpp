#include "CustomTreeView.h"

#include <QApplication>
#include <QHeaderView>
#include <QModelIndex>
#include <QMouseEvent>
#include <QPainter>
#include <QScrollBar>
#include <QScroller>
#include <QPropertyAnimation>
#include <QDebug>
#include <QStyleOptionViewItem>
#include <QItemSelectionModel>
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
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);

}
void CustomTreeView::onTreeViewClickedSlot(const QModelIndex& index)
{
    if(index != previous_index_){
        emit sendModelIndexSignal(previous_index_);
    }
    emit sendModelIndexSignal(previous_index_);
    previous_index_ = index;
}
CustomTreeView::~CustomTreeView()
{
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



CustomDelegate::CustomDelegate(CustomTreeView* _tree_view,QObject *parent): QStyledItemDelegate(parent)
    ,tree_view_(_tree_view)
    ,previous_index_()
{
    setProperty("lastSelectMarkTop", 10.0);
    setProperty("lastSelectMarkBottom", 10.0);
    setProperty("selectMarkTop", 10.0);
    setProperty("selectMarkBottom", 10.0);
    /* 向上 */
    _lastSelectMarkTopAnimation = new QPropertyAnimation(this, "lastSelectMarkTop");
    connect(_lastSelectMarkTopAnimation, &QPropertyAnimation::valueChanged, this, [=](const QVariant& value) {
        _lastSelectMarkTop = value.toReal();
        tree_view_->viewport()->update(); });
    _lastSelectMarkTopAnimation->setDuration(300);
    _lastSelectMarkTopAnimation->setEasingCurve(QEasingCurve::InOutSine);

    _selectMarkBottomAnimation = new QPropertyAnimation(this, "selectMarkBottom");
    connect(_selectMarkBottomAnimation, &QPropertyAnimation::valueChanged, this, [=](const QVariant& value) {
        _selectMarkBottom = value.toReal();
        tree_view_->viewport()->update(); });
    _selectMarkBottomAnimation->setDuration(300);
    _selectMarkBottomAnimation->setEasingCurve(QEasingCurve::InOutSine);
    connect(_lastSelectMarkTopAnimation, &QPropertyAnimation::finished, this, [=]() {
        // _isSelectMarkDisplay = true;
        // _lastSelectedNode = nullptr;
        _selectMarkBottomAnimation->setStartValue(0);
        _selectMarkBottomAnimation->setEndValue(10);
        _selectMarkBottomAnimation->start(); });

    /* 向下 */
    _lastSelectMarkBottomAnimation = new QPropertyAnimation(this, "lastSelectMarkBottom");
    connect(_lastSelectMarkBottomAnimation, &QPropertyAnimation::valueChanged, this, [=](const QVariant& value) {
        _lastSelectMarkBottom =  value.toReal();
        tree_view_->viewport()->update(); });
    _lastSelectMarkBottomAnimation->setDuration(300);
    _lastSelectMarkBottomAnimation->setEasingCurve(QEasingCurve::InOutSine);

    _selectMarkTopAnimation = new QPropertyAnimation(this, "selectMarkTop");
    connect(_selectMarkTopAnimation, &QPropertyAnimation::valueChanged, this, [=](const QVariant& value) {
        _selectMarkTop =  value.toReal();
        tree_view_->viewport()->update(); });
    _selectMarkTopAnimation->setDuration(300);
    _selectMarkTopAnimation->setEasingCurve(QEasingCurve::InOutSine);
    connect(_lastSelectMarkBottomAnimation, &QPropertyAnimation::finished, this, [=]() {
        // _isSelectMarkDisplay = true;
        // _lastSelectedNode = nullptr;
        _selectMarkTopAnimation->setStartValue(0);
        _selectMarkTopAnimation->setEndValue(10);
        _selectMarkTopAnimation->start(); });


    connect(tree_view_,&CustomTreeView::sendModelIndexSignal,this,&CustomDelegate::sendModelIndexSlot);
}

CustomDelegate::~CustomDelegate()
{
}

void CustomDelegate::sendModelIndexSlot(const QModelIndex& index)
{
    // qDebug()<<"11";
    previous_index_ = index;
    current_index_ = tree_view_->currentIndex();


    bool flag = compareItemY(index,previous_index_);
    _lastSelectMarkTop = 10;
    _lastSelectMarkBottom = 10;
    _selectMarkTop = 10;
    _selectMarkBottom = 10;
    if(flag){
        /* 当前节点高于上一个节点，向上 */
        _lastSelectMarkTopAnimation->setStartValue(10);
        _lastSelectMarkTopAnimation->setEndValue(0);
        _lastSelectMarkTopAnimation->start();
        _lastSelectMarkBottomAnimation->stop();
        _selectMarkTopAnimation->stop();
        // _isSelectMarkDisplay = false;

    }else{
        /* 当前节点低于上一个节点，向下 */
        _lastSelectMarkBottomAnimation->setStartValue(10);
        _lastSelectMarkBottomAnimation->setEndValue(0);
        _lastSelectMarkBottomAnimation->start();
        _lastSelectMarkTopAnimation->stop();
        _selectMarkBottomAnimation->stop();
        // _isSelectMarkDisplay = false;
    }

}

bool CustomDelegate::compareItemY(const QModelIndex& _current, const QModelIndex& _previous)
{
    /* 返回TRUE _current 高于 _previous ，treeview 默认选中第一行*/
    if(!_current.isValid()){
        return false;
    }
    if(!_previous.isValid()){
        return false;
    }
    int previous_row = _previous.row();
    int current_row = _current.row();

    /* 比较行号 */
    if (current_row < previous_row) {
        return true;
    }
    return false;
}


void CustomDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    /* 视图更新时触发，每个项的 paint() 被调用 */
    QStyleOptionViewItem view_option(option);
    initStyleOption(&view_option, index);
    if (option.state.testFlag(QStyle::State_HasFocus))
    {
        /* 移除焦点状态，焦点状态通常会在默认的绘制中显示一个突出边框或其他效果 */
        view_option.state &= ~QStyle::State_HasFocus;
    }
    QStyledItemDelegate::paint(painter, view_option, index);
    painter->save();
    /* 启用抗锯齿效果 */
    painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing);

    if(index.model()->hasChildren(index)){
        QStyleOption arrow_option;
        arrow_option.rect = QRect(option.rect.right() - 20, option.rect.top(), 20, option.rect.height()); // 右侧的箭头位置

        arrow_option.state = QStyle::State_Children;

        // 判断当前节点是展开状态还是折叠状态
        if (view_option.state & QStyle::State_Open) {
            // 节点展开 -> 向上箭头
            arrow_option.state |= QStyle::State_Open;
        }

        // 绘制箭头
        QApplication::style()->drawPrimitive(QStyle::PE_IndicatorBranch, &arrow_option, painter);

    }

    /* 文字绘制 */
    QRect item_rect = option.rect;
    QString text = index.data(Qt::UserRole+1).toString();
    painter->drawText(item_rect.x() + 37, item_rect.y() + 25, text);


    /* 设置轮廓线的颜色 */
    painter->setPen(Qt::white);
    QStyledItemDelegate::paint(painter, option, index);
    /* 设置填充颜色 */
    QColor color(14,111,195);
    painter->setBrush(color);
    /* 设置无边框 */
    painter->setPen(Qt::NoPen);


    QString text45 = current_index_.data(Qt::UserRole+1).toString();
    QString text1 = previous_index_.data(Qt::UserRole+1).toString();

    if(index.isValid() && current_index_ == index){
        /* 矩形区域 x,y 宽度，高度 */
        QRectF rect(item_rect.x() +3,item_rect.y() + _selectMarkTop,3, item_rect.height() - _selectMarkTop - _selectMarkBottom);
        /* 3,3 圆角半径 */
        painter->drawRoundedRect(rect, 3, 3);

        int row = index.row();
        // qDebug()<<"current-----"<<row; 3 10 3 20
        QString text = current_index_.data(Qt::UserRole+1).toString();
        QString text1 = previous_index_.data(Qt::UserRole+1).toString();
        qDebug()<<"current-----"<<text;
        qDebug()<<"previous-----"<<text1;
    }

    if(previous_index_.isValid() && index == previous_index_){
        QRectF rect(item_rect.x() +3,item_rect.y() + _lastSelectMarkTop,3, item_rect.height() - _lastSelectMarkTop - _lastSelectMarkBottom);
        painter->drawRoundedRect(rect, 3, 3);

        int row = previous_index_.row();
        // qDebug()<<"last-----"<<row;
    }

    /* 恢复绘图状态 */
    painter->restore();

}

QSize CustomDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    /* 设置项的显示大小 */
    QSize size = QStyledItemDelegate::sizeHint(option, index);
    size.setHeight(40);
    return size;
}

bool CustomDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
#if 0
    if(event->type() == QEvent::MouseButtonRelease){


        if(index == previous_index_){
            return QStyledItemDelegate::editorEvent(event,model,option,index);

        }
        bool flag = false;
        if(index.isValid()){
            flag = compareItemY(index,previous_index_);
            /* 记录上一次节点 */
            previous_index_ = current_index_;
            current_index_ = index;
        }

        _lastSelectMarkTop = 10;
        _lastSelectMarkBottom = 10;
        _selectMarkTop = 10;
        _selectMarkBottom = 10;
        if(flag){
            /* 当前节点高于上一个节点，向上 */
            _lastSelectMarkTopAnimation->setStartValue(10);
            _lastSelectMarkTopAnimation->setEndValue(0);
            _lastSelectMarkTopAnimation->start();
            _lastSelectMarkBottomAnimation->stop();
            _selectMarkTopAnimation->stop();
            // _isSelectMarkDisplay = false;

        }else{
            /* 当前节点低于上一个节点，向下 */
            _lastSelectMarkBottomAnimation->setStartValue(10);
            _lastSelectMarkBottomAnimation->setEndValue(0);
            _lastSelectMarkBottomAnimation->start();
            _lastSelectMarkTopAnimation->stop();
            _selectMarkBottomAnimation->stop();
            // _isSelectMarkDisplay = false;
        }
    }
#endif
    return QStyledItemDelegate::editorEvent(event,model,option,index);
}


