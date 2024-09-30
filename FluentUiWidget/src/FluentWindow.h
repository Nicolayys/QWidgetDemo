#ifndef FLUENTWINDOW_H
#define FLUENTWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QScopedPointer>
class FluentWindowPrivate;

class FluentWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit FluentWindow(QWidget *parent = nullptr);
    ~FluentWindow();
    FluentWindow(FluentWindowPrivate& dd, FluentWindow* parent = nullptr);
    QScopedPointer<FluentWindowPrivate> d_ptr;

private:
    Q_DECLARE_PRIVATE(FluentWindow)
    Q_DISABLE_COPY(FluentWindow);
signals:
private:
    void test();
};

#endif // FLUENTWINDOW_H
