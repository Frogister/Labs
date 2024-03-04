#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "entrypoint.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->comboBoxFrom->addItem("Десятичная");
    ui->comboBoxFrom->addItem("Двоичная");
    ui->comboBoxFrom->addItem("Восьмеричная");
    ui->comboBoxTo->addItem("Десятичная");
    ui->comboBoxTo->addItem("Двоичная");
    ui->comboBoxTo->addItem("Восьмеричная");
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
    if (param == NULL) {
        snprintf(context.errorLine, sizeof(context.errorLine), "Ошибка: Ошибка выделения памяти для параметров");
        updateLabels();
        return;
    }
    param->newValue = cStr;
    param->fromBase = comboBoxStrFrom;
    param->toBase = comboBoxStrTo;
    const char* error = doOperation(ErrorOperation, &context, param);
    if (error != nullptr)
    {
        snprintf(context.errorLine, sizeof(context.errorLine), "Ошибка: %s", error);
        updateLabels();
        free(param);
        return;
    }
    doOperation(Translation, &context, param);
    updateLabels();
    free(param);
}

void MainWindow::onCopyClicked()
{
    doOperation(CopyOperation, &context, nullptr);
}

void MainWindow::onSwapClicked() {
    std::string lineEditValue = ui->translatedValue->text().toStdString();
    std::string translatedValueStr = ui->lineEdit->text().toStdString();
    std::string newFromBase = ui->comboBoxTo->currentText().toStdString();
    std::string newToBase = ui->comboBoxFrom->currentText().toStdString();
    const char* newLineEditValue = lineEditValue.c_str();
    const char* newTranslatedValue = translatedValueStr.c_str();
    const char* newComboBoxStrFrom = newFromBase.c_str();
    const char* newComboBoxStrTo = newToBase.c_str();
    ui->lineEdit->setText(QString::fromStdString(newLineEditValue));
    ui->translatedValue->setText(QString::fromStdString(newTranslatedValue));
    ui->comboBoxFrom->setCurrentText(QString::fromStdString(newComboBoxStrFrom));
    ui->comboBoxTo->setCurrentText(QString::fromStdString(newComboBoxStrTo));
    AppParams* param = (AppParams*)malloc(sizeof(AppParams));
    if (param == NULL) {
        snprintf(context.errorLine, sizeof(context.errorLine), "Ошибка: Ошибка выделения памяти для параметров");
        updateLabels();
        return;
    }
    param->newValue = newTranslatedValue;
    param->fromBase = newComboBoxStrFrom;
    param->toBase = newComboBoxStrTo;
    updateLabels();
    free(param);
}


void MainWindow::updateLabels() {
    if (context.errorLine[0] != '\0') {
        ui->translatedValue->clear();
        ui->errLine->setText(QString::fromUtf8(context.errorLine));
    } else {
        ui->errLine->clear();
        ui->translatedValue->setText(QString::fromUtf8(context.translatedValue));
    }
}
