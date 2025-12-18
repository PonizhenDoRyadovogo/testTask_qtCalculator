#include "CalculatorPresenter.h"

#include <QLocale>

CalculatorPresenter::CalculatorPresenter(IView* view, QObject* parent)
    : QObject(parent),m_view(view) {}

double CalculatorPresenter::getDisplayNumber() const {
    bool ok = false;
    const double value = QLocale::c().toDouble(m_view->getDisplayText(), &ok);
    return ok ? value : 0.0;
}

void CalculatorPresenter::setDisplayNumber(double x) {
    m_view->setDisplayText(QLocale::c().toString(x, 'g', 4));
}

void CalculatorPresenter::setErrorState(const QString& errorMessage) {
    m_view->showError(errorMessage);
    m_view->setDisplayText("Error");
    m_acc = 0.0;
    m_pending = Operand::None;
    m_enteringNow = true;
}

bool CalculatorPresenter::isError() const {
    return m_view->getDisplayText() == "Error";
}

void CalculatorPresenter::onDigit(int d) {
    QString t = m_view->getDisplayText();

    if(m_enteringNow || t == "0" || isError() || t == "0.0") {
        t = QString::number(d);
        m_enteringNow = false;
    } else {
        t += QString::number(d);
    }
    m_view->setDisplayText(t);
}

void CalculatorPresenter::onDot() {
    QString t = m_view->getDisplayText();

    if(m_enteringNow || isError()) {
        m_view->setDisplayText("0.");
        m_enteringNow = false;
        return;
    } else if (!t.contains('.')) {
        m_view->setDisplayText(t + ".");
    }
}

void CalculatorPresenter::onOperand(Operand op) {
    if(isError()) return;

    const double cur = getDisplayNumber();
    if(m_pending == Operand::None) {
        m_pending = op;
        m_acc = cur;
        m_enteringNow = true;
        return;
    }

    if(!m_enteringNow) {
        const CalcResult res = CalculatorModel::compute(m_acc, cur, m_pending);
        if(!res.ok) {
            setErrorState(res.error);
            return;
        }
        m_acc = res.value;
        setDisplayNumber(m_acc);
    }
    m_pending = op;
    m_enteringNow = true;
}

void CalculatorPresenter::onEquals(){
    if(isError()) {
        return;
    }
    if(m_pending == Operand::None) {
        return;
    }

    const double cur = getDisplayNumber();
    const CalcResult res = CalculatorModel::compute(m_acc, cur, m_pending);

    if(!res.ok) {
        setErrorState(res.error);
        return;
    }
    m_acc = res.value;
    m_pending = Operand::None;
    m_enteringNow = true;
    setDisplayNumber(m_acc);
}

void CalculatorPresenter::onClear() {
    m_view->setDisplayText("0");
    m_acc = 0.0;
    m_pending = Operand::None;
    m_enteringNow = true;
}

void CalculatorPresenter::onToggleSign() {
    if(isError()) {
        return;
    }
    QString t = m_view->getDisplayText();

    if(t == "0" || t == "0." || t.isEmpty()) {
        return;
    }

    if(t.startsWith("-")) {
        t.remove(0, 1);
    } else {
        t.prepend("-");
    }
    m_view->setDisplayText(t);
}

void CalculatorPresenter::onPercent() {
    if(isError()) {
        return;
    }
    const double t = getDisplayNumber();
    const double res = t / 100.0;
    setDisplayNumber(res);

    m_enteringNow = false;
}
