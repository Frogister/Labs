#ifndef MAINWINDOW_H
#define MAINWINDOW_H
\
#include <QMainWindow>
#include "appcontext.h"

#define NO_ERRORS ""
#define BIT_OVERLOAD "Error: Value > 4 Byte Value"
#define BAD_DIGIT "Error: Unsupported Digit"
#define NOTHING_ENTERED_OR_TRANSLATED "Error: Nothing Entered Or Translated"

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
    void errorsOperation();
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
