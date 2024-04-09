#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include "appcontext.h"

using namespace std;

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
    void printDataOnTableWidget();
    void setFullTableOnTableWidget(Node* current);
    void setTableOnTableWidget();
    void setRow(Node* current,int row);
    void setRegionTableOnTableWidget(Node* current);
    void onLoadFileButtonClicked();
    void errorsOperation();
    void onLoadDataButtonClicked();
    void onCalculateMetricsButtonClicked();
    void updateLabels();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
