#ifndef CUSTOMDELEGATE_H
#define CUSTOMDELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>
#include <QScopedPointer>
#include <QPushButton>
#include <QFontMetrics>
#include <QCheckBox>
#include <QPoint>
class CustomDelegate : public QObject
{
    Q_OBJECT
public:
    explicit CustomDelegate(QObject * parent = nullptr);

signals:
};


class CheckboxDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    CheckboxDelegate(QWidget * _parent);
    ~CheckboxDelegate() override;

protected:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) override;

private:
    QRect getCenterRect(QRect _source_rect) const;

private:
    QScopedPointer<QCheckBox> 													check_;
    QFontMetrics*																		use_font_metrics_;
};
#endif // CUSTOMDELEGATE_H
