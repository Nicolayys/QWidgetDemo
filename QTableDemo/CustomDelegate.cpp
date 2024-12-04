#include "CustomDelegate.h"

#include <QApplication>
#include <QDateTime>
#include <QPainter>
#include <QFontMetrics>
#include <QEvent>
#include <QMouseEvent>
#include <QPushButton>
#include <QPainter>
#include <QStandardItemModel>
#include <QDebug>

CustomDelegate::CustomDelegate(QObject *parent)
    : QObject{parent}
{}

#pragma region 复选框代理

CheckboxDelegate::CheckboxDelegate(QWidget * _parent)
    : QStyledItemDelegate(_parent)
    , check_(new QCheckBox())
{
    // check_->setObjectName("mainBtn");

    QFont use_font = check_->font();
    use_font.setPixelSize(14);
    use_font.setFamily("PingFang SC Regular");
    use_font_metrics_ = new QFontMetrics(use_font);
}

CheckboxDelegate::~CheckboxDelegate()
{

}

void CheckboxDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex & index) const
{
    QStyleOptionButton style_option_button;
    style_option_button.rect = getCenterRect(option.rect);
    style_option_button.state = option.state;
    /* 调整复选框位置 */
    style_option_button.rect.setLeft(option.rect.left()+20);

    if (option.state & QStyle::State_Selected) {
        style_option_button.state |= QStyle::State_Selected;
    }

    if (option.state & QStyle::State_Enabled) {
        style_option_button.state |= QStyle::State_Enabled;
    }

    Qt::CheckState check_state = static_cast<Qt::CheckState>(index.data(Qt::CheckStateRole).toInt());
    if (check_state == Qt::Checked)
    {
        style_option_button.state |= QStyle::State_On;
    }
    else if (check_state == Qt::PartiallyChecked)
    {
        style_option_button.state |= QStyle::State_NoChange;
    }

    /* 绘制复选框 */
    QApplication::style()->drawControl(QStyle::CE_CheckBox, &style_option_button, painter, check_.data());
    /* 绘制复选框文本 */
    QString check_text = index.data(Qt::DisplayRole).toString();
    QRect text_rect = option.rect;
    text_rect.setLeft(option.rect.left() + 40);
    text_rect.setRight(option.rect.right());
    painter->drawText(text_rect, Qt::AlignVCenter, check_text);
}

bool CheckboxDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    if (event->type() == QEvent::MouseButtonRelease)
    {
        QMouseEvent* mouse_event = static_cast<QMouseEvent*>(event);
        /* 复选框区域 */
        QRect check_rect = option.rect.adjusted(20,0,0,0);
        /* 判断是否点击到复选框区域 */
        if (check_rect.contains(mouse_event->pos())) {
            Qt::CheckState checkState = static_cast<Qt::CheckState>(index.data(Qt::CheckStateRole).toInt());
            checkState = (checkState == Qt::Checked) ? Qt::Unchecked : Qt::Checked;
            return model->setData(index, checkState, Qt::CheckStateRole);
        }
    }
    return QStyledItemDelegate::editorEvent(event, model, option, index);

}

QRect CheckboxDelegate::getCenterRect(QRect _source_rect) const
{
    QStyleOptionButton style_option_button;

    QRect check_box_rect = QApplication::style()->subElementRect(QStyle::SE_CheckBoxIndicator, &style_option_button);
    int x = _source_rect.x() + (_source_rect.width() - check_box_rect.width()) / 2;
    int y = _source_rect.y() + (_source_rect.height() - check_box_rect.height()) / 2;

    return QRect(QPoint(x, y), check_box_rect.size());
}

#pragma endregion 复选框代理
