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
    m_view->setExpressionText("");
    m_enteredEqual = false;
}

bool CalculatorPresenter::isError() const {
    return m_view->getDisplayText() == "Error";
}

QString CalculatorPresenter::operandSym(Operand op) const{
    switch (op) {
    case Operand::Add: return "+";
    case Operand::Div: return "/";
    case Operand::Mul: return "x";
    case Operand::Sub: return "-";
    default: return "";
    }
}

void CalculatorPresenter::onDigit(int d) {
    QString expr = m_view->getExpressionText();
    int size = expr.size();
    QString t = QString::number(d);
    if(expr == "" || isError()) {
        expr = QString::number(d);
        m_enteringNow = false;
        m_lastNumber = t;
    } else if(m_enteringNow) {
        expr = (size == 1) ? expr + QString::number(d) : expr + " " + QString::number(d);
        m_lastNumber = (size == 1) ? "-" + t : t;
        m_enteringNow = false;
    } else if(m_enteredEqual) {
        m_enteredEqual = false;
        m_lastNumber = t;
        expr = t;
        m_view->setDisplayText("0");
        m_view->setEqualsIndicatorVisible(false);
    } else {
        expr = expr + QString::number(d);
        m_lastNumber = m_enterdDot ? m_lastNumber + "." + t : m_lastNumber + t;
        m_enterdDot = false;
    }
    m_view->setExpressionText(expr);
}

void CalculatorPresenter::onDot() {
    QString t = m_view->getExpressionText();

    if(m_enteringNow || isError()) {
        m_view->setExpressionText("0.");
        m_enteringNow = false;
        m_enterdDot = true;
        return;
    } else if (!m_lastNumber.contains('.')) {
        m_view->setExpressionText(t+".");
        m_enterdDot = true;
    }
}

void CalculatorPresenter::onOperand(Operand op) {
    if(isError()) return;

    QString t = m_view->getExpressionText();
    if(t.isEmpty() && op == Operand::Sub) {
        m_view->setExpressionText("-");
        return;
    } else if(t.isEmpty()){
        return;
    }

    if(m_enteredEqual) {
        m_lastNumber = m_view->getDisplayText();
        m_view->setExpressionText(m_lastNumber);
        m_enteredEqual = false;
    }


    QString last = t.right(1);
    if(last == "+" || last == "-" || last == "x" || last == "/") {
        t.chop(1);
        t += operandSym(op);
        m_view->setExpressionText(t);

        m_pending = op;
        m_enteringNow = true;
        return;
    }

    bool ok = false;
    double cur = QLocale::c().toDouble(m_lastNumber, &ok);
    cur = ok ? cur : 0.0;
    if(m_pending == Operand::None) {
        m_pending = op;
        m_acc = cur;
        m_enteringNow = true;
        t = t + " " + operandSym(m_pending);
        m_view->setExpressionText(t);
        return;
    }

    if(!m_enteringNow) {
        const CalcResult res = CalculatorModel::compute(m_acc, cur, m_pending);
        if(!res.ok) {
            setErrorState(res.error);
            return;
        }
        m_acc = res.value;
    }
    m_pending = op;
    m_enteringNow = true;
    t = t + " " + operandSym(m_pending);
    m_view->setExpressionText(t);
}

void CalculatorPresenter::onEquals(){
    if(isError()) {
        return;
    }
    if(m_pending == Operand::None) {
        return;
    }

    bool ok = false;
    double cur = QLocale::c().toDouble(m_lastNumber, &ok);;
    cur = ok ? cur : 0.0;
    const CalcResult res = CalculatorModel::compute(m_acc, cur, m_pending);

    if(!res.ok) {
        setErrorState(res.error);
        return;
    }
    m_acc = res.value;
    m_pending = Operand::None;
    m_enteringNow = false;
    m_enteredEqual = true;
    m_view->setEqualsIndicatorVisible(true);
    setDisplayNumber(m_acc);
}

void CalculatorPresenter::onClear() {
    m_view->setDisplayText("0");
    m_acc = 0.0;
    m_pending = Operand::None;
    m_enteringNow = true;
    m_view->setEqualsIndicatorVisible(false);
    m_view->setExpressionText("");
    m_enteredEqual = false;
    m_enterdDot = false;
}

void CalculatorPresenter::onToggleSign() {
    if(isError()) {
        return;
    }

    if(m_enteredEqual) {
        double cur = getDisplayNumber();
        cur *= -1;
        m_lastNumber = QString::number(cur);
        m_view->setExpressionText(QString::number(cur));
        m_view->setDisplayText("0");
        m_enteredEqual = false;
        m_enteringNow = true;
        return;
    }

    QString expr = m_view->getExpressionText();
    if(expr.isEmpty() || expr == "-"){
        return;
    }
    if(m_lastNumber.isEmpty() || m_lastNumber == "0" || m_lastNumber == "0.") {
        return;
    }

    int numStart = expr.length() - m_lastNumber.length();
    int i = numStart - 1;
    while (i >= 0 && expr[i].isSpace()) {
        --i;
    }
    const QChar prev = (i >= 0) ? expr[i] : QChar();

    const QString absNum = m_lastNumber.startsWith('-') ? m_lastNumber.mid(1) : m_lastNumber;
    if (prev == '+' || prev == '-') {
        expr[i] = (prev == '+') ? '-' : '+';

        if (m_lastNumber.startsWith('-')) {
            expr.replace(numStart, m_lastNumber.length(), absNum);
            m_lastNumber = absNum;
        } else {
            m_lastNumber = absNum;
        }
    } else {
        const QString newNum = m_lastNumber.startsWith('-') ? absNum : ("-" + absNum);
        expr.replace(numStart, m_lastNumber.length(), newNum);
        m_lastNumber = newNum;
    }
    m_view->setExpressionText(expr);
    m_enteringNow = false;
}

void CalculatorPresenter::onPercent() {
    if(isError()) {
        return;
    }

    if(m_view->getExpressionText() == "" || m_view->getExpressionText() == "-" || m_lastNumber == "") {
        return;
    }

    if(m_enteredEqual) {
        double cur = getDisplayNumber();
        cur = cur / 100.0;
        m_view->setDisplayText("0");
        m_view->setExpressionText(QString::number(cur));
        m_lastNumber = QString::number(cur);
        m_view->setEqualsIndicatorVisible(false);
        m_acc = cur;
        m_enteringNow = false;
        m_enteredEqual = false;
        return;
    }

    QString t = m_view->getExpressionText();
    t.remove(t.length() - m_lastNumber.length(), m_lastNumber.length());

    bool ok = false;
    double last = QLocale::c().toDouble(m_lastNumber, &ok);
    last = ok ? last : 0.0;

    last = last / 100.0;
    m_lastNumber = QString::number(last);

    t = t + m_lastNumber;

    m_enteringNow = true;

    m_view->setExpressionText(t);
}
