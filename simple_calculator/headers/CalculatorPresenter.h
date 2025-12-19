#ifndef CALCULATORPRESENTER_H
#define CALCULATORPRESENTER_H

#include <QObject>

#include "IView.h"
#include "CalculatorModel.h"

class CalculatorPresenter: public QObject {
    Q_OBJECT
public:
    CalculatorPresenter(IView* view, QObject* parent = nullptr);
public slots:
    void onDigit(int d);
    void onDot();
    void onOperand(Operand op);
    void onEquals();
    void onClear();
    void onToggleSign();
    void onPercent();
private:
    double getDisplayNumber() const;
    void setDisplayNumber(double x);
    void setErrorState(const QString& errorMessage);
    bool isError() const;
    QString operandSym(Operand op) const;
    bool isOperand(const QString str) const;
private:
    IView* m_view = nullptr;

    double m_acc = 0.0;
    Operand m_pending = Operand::None;
    bool m_enteringNow = true;
    bool m_enteredEqual = false;
    bool m_enterdDot = false;
    QString m_lastNumber = "";
};

#endif // CALCULATORPRESENTER_H
