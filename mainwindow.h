#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "appcontext.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    AppContext context;

private slots:
    void onTranslateClicked();
    void updateLabels();
    void onCopyClicked();
    void onSwapClicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
