#ifndef FLUENTWINDOWPRIVATE_H
#define FLUENTWINDOWPRIVATE_H

#include <QObject>
class FluentWindow;
class FluentWindowPrivate : public QObject
{
    Q_OBJECT
public:
    explicit FluentWindowPrivate(QObject *parent = nullptr);
    ~FluentWindowPrivate();
private:
    FluentWindow *q_ptr;
    Q_DECLARE_PUBLIC(FluentWindow)

private:
    int data{100};
};

#endif // FLUENTWINDOWPRIVATE_H
