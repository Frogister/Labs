#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QClipboard>
#include "entrypoint.h"
#include "logic.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->comboBoxFrom->addItem(Десятичная);
    ui->comboBoxFrom->addItem(Двоичная);
    ui->comboBoxFrom->addItem(Восьмеричная);
    ui->comboBoxTo->addItem(Десятичная);
    ui->comboBoxTo->addItem(Двоичная);
    ui->comboBoxTo->addItem(Восьмеричная);
    connect(ui->translateButton, &QPushButton::clicked, this, &MainWindow::onTranslateClicked);
    connect(ui->copyButton, &QPushButton::clicked, this, &MainWindow::onCopyClicked);
    connect(ui->swapButton, &QPushButton::clicked, this, &MainWindow::onSwapClicked);
    doOperation(Initialization, &context, nullptr);
    updateLabels();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onTranslateClicked() {
    std::string str = ui->lineEdit->text().toStdString();
    std::string fromBase = ui->comboBoxFrom->currentText().toStdString();
    std::string toBase = ui->comboBoxTo->currentText().toStdString();
    const char* cStr = str.c_str();
    const char* comboBoxStrFrom = fromBase.c_str();
    const char* comboBoxStrTo = toBase.c_str();
    AppParams* param = (AppParams*)malloc(sizeof(AppParams));
    param->newValue = cStr;
    context.fromBase = comboBoxStrFrom;
    context.toBase = comboBoxStrTo;
    doOperation(GetErrorCode, &context, param);
    if (context.errorCode != NoErrors)
    {
        errorsOperation();
    }
    else
    {
        errorsOperation();
        doOperation(Translation, &context, param);
    }
    updateLabels();
    free(param);
}

void MainWindow::onCopyClicked()
{
    QClipboard* clipboard = QGuiApplication::clipboard();
    QString textToCopy = ui->translatedValue->text();
    clipboard->setText(textToCopy);
}

void MainWindow::onSwapClicked() {
    std::string lineEditValue = ui->translatedValue->text().toStdString();
    std::string newFromBase = ui->comboBoxTo->currentText().toStdString();
    std::string newToBase = ui->comboBoxFrom->currentText().toStdString();
    const char* newLineEditValue = lineEditValue.c_str();
    const char* newComboBoxStrFrom = newFromBase.c_str();
    const char* newComboBoxStrTo = newToBase.c_str();
    AppParams* param = (AppParams*)malloc(sizeof(AppParams));
    param->newValue = newLineEditValue;
    swapReplace(&context, param->newValue);
    context.fromBase = newComboBoxStrFrom;
    context.toBase = newComboBoxStrTo;
    ui->comboBoxFrom->setCurrentText(newComboBoxStrFrom);
    ui->comboBoxTo->setCurrentText(newComboBoxStrTo);
    param->newValue = newLineEditValue;
    ui->lineEdit->setText(param->newValue);
    swapReplace(&context, param->newValue);
    doOperation(Translation, &context, param);
    doOperation(GetErrorCode, &context, param);
    errorsOperation();
    updateLabels();
    free(param);
}

void MainWindow::errorsOperation()
{
    switch(context.errorCode)
    {
    case NoErrors:
        ui->errLine->clear();
        break;
    case BitOverload:
        ui->errLine->setText(BIT_OVERLOAD);
        break;
    case BadDigit:
        ui->errLine->setText(BAD_DIGIT);
        break;
    case NothingEnteredOrTranslated:
        ui->errLine->setText(NOTHING_ENTERED_OR_TRANSLATED);
        break;
    }
}

void MainWindow::updateLabels() {
    if (context.errorCode != NoErrors) {
        ui->translatedValue->clear();
    }
    else
    {
        ui->translatedValue->setText(context.translatedValue);
    }
}
