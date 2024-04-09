#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "entrypoint.h"
#include "string.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->loadFileButton, SIGNAL(clicked()), this, SLOT(onLoadFileButtonClicked()));
    connect(ui->loadDataButton, SIGNAL(clicked()), this, SLOT(onLoadDataButtonClicked()));
    connect(ui->calculateButton, SIGNAL(clicked()), this, SLOT(onCalculateMetricsButtonClicked()));
    doOperation(Initialization, &context, nullptr);
    updateLabels();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::printDataOnTableWidget()
{
    ui->tableWidget->setRowCount(0);
    Node* current = context.table->first;
    if (!strcmp(context.region, "")) {
        setTableOnTableWidget();
    } else {
        setRegionTableOnTableWidget(current);
    }
}

void MainWindow::setTableOnTableWidget()
{
    ui->tableWidget->setRowCount(0);
    Node* current = context.table->first;
    if (!strcmp(context.region, "")) {
        setFullTableOnTableWidget(current);
    } else {
        setRegionTableOnTableWidget(current);
    }
}

void MainWindow::setFullTableOnTableWidget(Node* current)
{
    int row = 0;
    ui->tableWidget->setRowCount(context.totalSuccessfulLines);
    while (current) {
        setRow(current, row);
        current = current->next;
        ++row;
    }
    if (row == 0) {
        context.errorCode = ZeroRowsError;
    }
}

void MainWindow::setRegionTableOnTableWidget(Node* current)
{
    int row = 0;
    while (current) {
        if (!strcmp(current->data.region, context.region)) {
            ui->tableWidget->insertRow(row);
            setRow(current,row);
            ++row;
        }
        current = current->next;
    }
    if (row == 0) {
        context.errorCode = ZeroRowsError;
    }
}

void MainWindow::setRow(Node* current,int row) {
    ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(current->data.year)));
    ui->tableWidget->setItem(row, 1, new QTableWidgetItem(QString(current->data.region)));
    ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(current->data.nPG)));
    ui->tableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(current->data.birthRate)));
    ui->tableWidget->setItem(row, 4, new QTableWidgetItem(QString::number(current->data.deathRate)));
    ui->tableWidget->setItem(row, 5, new QTableWidgetItem(QString::number(current->data.gDW)));
    ui->tableWidget->setItem(row, 6, new QTableWidgetItem(QString::number(current->data.urbanisation)));
}

void MainWindow::onLoadFileButtonClicked()
{
    AppParams param;
    QString filePathQString = QFileDialog::getOpenFileName(this, "Choose Table", "/Users/frogister/Documents/ОП/Lab2/Example Tables", "CSV Tables (*.csv)");
    string filePathStr = filePathQString.toStdString();
    const char* filePath = filePathStr.c_str();
    strncpy(param.filePath, filePath, sizeof(param.filePath) - 1);
    param.filePath[sizeof(param.filePath) - 1] = '\0';
    doOperation(CopyFilePath, &context, &param);
}

void MainWindow::onLoadDataButtonClicked()
{
    AppParams param;
    string regionStr = ui->regionLine->text().toStdString();
    const char* regionCStr = regionStr.c_str();
    strncpy(param.region, regionCStr, sizeof(param.region) - 1);
    param.region[sizeof(param.region) - 1] = '\0';
    doOperation(CopyRegionName, &context, &param);
    if (strcmp(context.filePath, NO_FILE)) {
        doOperation(GetData, &context, NULL);
        if (context.table != NULL) {
            setTableOnTableWidget();
        }
    } else {
        context.errorCode = FileNotSelected;
    }
    updateLabels();
}

void MainWindow::onCalculateMetricsButtonClicked()
{
    if (strcmp(context.filePath,"")) {
        AppParams param;

        string regionStr = ui->regionLine->text().toStdString();
        const char* regionCStr = regionStr.c_str();
        strncpy(param.region, regionCStr, sizeof(param.region) - 1);
        param.region[sizeof(param.region) - 1] = '\0';
        string columnStr = ui->columnIndexLine->text().toStdString();
        const char* columnCStr = columnStr.c_str();
        strncpy(param.column, columnCStr, sizeof(param.column) - 1);
        param.column[sizeof(param.column) - 1] = '\0';
        doOperation(CopyRegionName, &context, &param);
        doOperation(CopyColumnIndex, &context, &param);
        if (context.table != NULL ) {
            doOperation(Calculation, &context, NULL);
        } else {
            context.errorCode = NoCalculationData;
        }
    } else {
        context.errorCode = FileNotSelected;
    }
    updateLabels();
}

void MainWindow::errorsOperation()
{
    switch(context.errorCode)
    {
    case NoErrors:
        ui->errLine->clear();
        break;
    case NoErrorsFileLoaded:
        ui->errLine->setText(QString(FILE_LOAD_SUCCESS) + ": " + context.filePath);
        ui->currentFileLabel->setText(context.filePath);
        break;
    case FileLoadError:
        ui->errLine->setText(FILE_LOAD_ERROR);
        ui->currentFileLabel->setText(READ_ERROR);
        break;
    case FileOpenError:
        ui->errLine->setText(FILE_OPEN_ERROR);
        ui->currentFileLabel->setText(READ_ERROR);
        break;
    case FileReadError:
        ui->errLine->setText(FILE_READ_ERROR);
        break;
    case ZeroRowsError:
        ui->errLine->setText(ZERO_ROWS_ERROR);
        break;
    case FileNotSelected:
        ui->errLine->setText(FILE_NOT_SELECTED);
        break;
    case ColumnError:
        ui->errLine->setText(COLUMN_ERROR);
        break;
    case RegionError:
        ui->errLine->setText(REGION_ERROR);
        break;
    case NoCalculationData:
        ui->errLine->setText(NO_CALCULATION_DATA);
        break;
    }
    context.errorCode = NoErrors;
}

void MainWindow::updateLabels()
{
    ui->minimumLabel->setText(QString::number(context.min));
    ui->maximumLabel->setText(QString::number(context.max));
    ui->medianLabel->setText(QString::number(context.med));
    ui->totalLines->setText(QString::number(context.totalLines));
    ui->totalErrorLines->setText(QString::number(context.totalErrorLines));
    ui->totalSuccessfulLines->setText(QString::number(context.totalSuccessfulLines));
    errorsOperation();
    context.min = DEFAULT_METRICS_VALUE;
    context.max = DEFAULT_METRICS_VALUE;
    context.med = DEFAULT_METRICS_VALUE;
}

