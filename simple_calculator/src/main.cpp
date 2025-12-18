#include "MainWindow.h"
#include "CalculatorModel.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    CalcResult res = CalculatorModel::compute(10.0, 5.0, Operand::Add);
    qDebug() << res.value;
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
//    return a.exec();
}
