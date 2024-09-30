#include "FluentWindow.h"
#include "private/FluentWindowPrivate.h"
FluentWindow::FluentWindow(QWidget *parent)
    : QMainWindow{parent}
    ,d_ptr(new FluentWindowPrivate())
{
    Q_D(FluentWindow);
    d->q_ptr = this;


    resize(1020,680);

}

FluentWindow::~FluentWindow()
{

}

void FluentWindow::test()
{
    Q_D(FluentWindow);

}
