#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "src/FluentWindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public FluentWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    // Ui::MainWindow *ui;

    void initWindow();
    void initEdgeLayout();
    void initContent();

private:
    int ThemeChangeTime{100};

};
#endif // MAINWINDOW_H
