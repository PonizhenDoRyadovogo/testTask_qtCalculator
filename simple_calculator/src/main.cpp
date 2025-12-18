#include "MainWindow.h"
#include "CalculatorModel.h"
#include "CalculatorPresenter.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    CalculatorPresenter presenter(&w);

    QObject::connect(&w, &MainWindow::digitPressed, &presenter, &CalculatorPresenter::onDigit);
    QObject::connect(&w, &MainWindow::clearPressed, &presenter, &CalculatorPresenter::onClear);
    QObject::connect(&w, &MainWindow::dotPressed, &presenter, &CalculatorPresenter::onDot);
    QObject::connect(&w, &MainWindow::equalsPressed, &presenter, &CalculatorPresenter::onEquals);
    QObject::connect(&w, &MainWindow::operandPressed, &presenter, &CalculatorPresenter::onOperand);
    QObject::connect(&w, &MainWindow::percentPressed, &presenter, &CalculatorPresenter::onPercent);
    QObject::connect(&w, &MainWindow::toggleSignPressed, &presenter, &CalculatorPresenter::onToggleSign);

    w.show();
    return a.exec();
}
