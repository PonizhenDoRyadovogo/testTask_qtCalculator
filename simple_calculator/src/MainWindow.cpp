#include "MainWindow.h"

#include <QMessageBox>
#include <QGridLayout>
#include <QPalette>
#include <QColor>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    buildUi();
    connectSignals();

    applyColors();

    setWindowTitle("Calculator");
    setFixedSize(320, 420);
}

void MainWindow::setDisplayText(const QString& text) {
    m_display->setText(text);
}

QString MainWindow::getDisplayText() const {
    return m_display->text();
}

void MainWindow::showError(const QString& errorMessage) {
    QMessageBox::warning(this, "Error", errorMessage);
}

void MainWindow::setExpressionText(const QString& text) {
    m_expr->setText(text);
}

void MainWindow::setEqualsIndicatorVisible(bool visible) {
    m_equl->setVisible(visible);
}

QString MainWindow::getExpressionText() const {
    return m_expr->text();
}

QPushButton* MainWindow::makeButton(const QString& btnName){
    QPushButton* b = new QPushButton(btnName, this);
    b->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    return b;
}

void MainWindow::buildUi() {
    QGridLayout* root = new QGridLayout(this);

    root->setSpacing(8);
    root->setContentsMargins(12, 12, 12, 12);

    m_display = new QLineEdit("0", this);
    m_display->setReadOnly(true);
    m_display->setMinimumHeight(54);
    m_display->setAlignment(Qt::AlignRight);
    m_display->setFrame(false);
    QFont f = m_display->font();
    f.setPointSize(18);
    m_display->setFont(f);
    root->addWidget(m_display, 0, 0, 1, 4);

    m_expr = new QLabel("", this);
    m_expr->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    m_expr->setMinimumHeight(22);
    QFont ef = m_expr->font();
    ef.setPointSize(11);
    m_expr->setFont(ef);
    auto* displayRow = new QWidget(this);
    auto* h = new QHBoxLayout(displayRow);
    h->setContentsMargins(0, 0, 0, 0);
    h->setSpacing(8);

    m_equl = new QLabel("=", this);
    m_equl->setMinimumWidth(18);
    m_equl->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    m_equl->setVisible(false);

    h->addWidget(m_equl);
    h->addWidget(m_display, 1);

    root->addWidget(m_expr,      1, 0, 1, 4);
    root->addWidget(displayRow,  0, 0, 1, 4);

    m_btnCE = makeButton("CE");
    m_btnPM = makeButton("+/-");
    m_btnPercent = makeButton("%");
    m_btnDiv = makeButton("/");
    m_btnMul = makeButton("*");
    m_btnSub = makeButton("-");
    m_btnAdd = makeButton("+");

    root->addWidget(m_btnCE, 2, 0);
    root->addWidget(m_btnPM, 2, 1);
    root->addWidget(m_btnPercent, 2, 2);
    root->addWidget(m_btnDiv, 2, 3);
    root->addWidget(m_btnMul, 3, 3);
    root->addWidget(m_btnSub, 4, 3);
    root->addWidget(m_btnAdd, 5, 3, 2, 1);

    m_digitsBtns.resize(10);
    for(int i = 0; i < 10; ++i) {
        m_digitsBtns[i] = makeButton(QString::number(i));
    }

    root->addWidget(m_digitsBtns[7], 3, 0);
    root->addWidget(m_digitsBtns[8], 3, 1);
    root->addWidget(m_digitsBtns[9], 3, 2);

    root->addWidget(m_digitsBtns[4], 4, 0);
    root->addWidget(m_digitsBtns[5], 4, 1);
    root->addWidget(m_digitsBtns[6], 4, 2);

    root->addWidget(m_digitsBtns[1], 5, 0);
    root->addWidget(m_digitsBtns[2], 5, 1);
    root->addWidget(m_digitsBtns[3], 5, 2);

    m_btnDot = makeButton(".");
    m_btnEqual = makeButton("=");
    root->addWidget(m_digitsBtns[0], 6, 0);
    root->addWidget(m_btnDot, 6, 1);
    root->addWidget(m_btnEqual, 6, 2);
}

void MainWindow::connectSignals() {
    for(int i = 0; i < 10; ++i) {
        connect(m_digitsBtns[i], &QPushButton::clicked, this, [this, i] {emit digitPressed(i);});
    }

    connect(m_btnCE, &QPushButton::clicked, this, &MainWindow::clearPressed);
    connect(m_btnPM, &QPushButton::clicked, this, &MainWindow::toggleSignPressed);
    connect(m_btnPercent, &QPushButton::clicked, this, &MainWindow::percentPressed);
    connect(m_btnDot, &QPushButton::clicked, this, &MainWindow::dotPressed);
    connect(m_btnEqual, &QPushButton::clicked, this, &MainWindow::equalsPressed);

    connect(m_btnDiv, &QPushButton::clicked, this, [this]{emit operandPressed(Operand::Div);});
    connect(m_btnMul, &QPushButton::clicked, this, [this]{emit operandPressed(Operand::Mul);});
    connect(m_btnSub, &QPushButton::clicked, this, [this]{emit operandPressed(Operand::Sub);});
    connect(m_btnAdd, &QPushButton::clicked, this, [this]{emit operandPressed(Operand::Add);});
}

void MainWindow::setButtonColors(QPushButton* b, const QColor& bg, const QColor& fg) {
    QPalette p = b->palette();
    p.setColor(QPalette::Button, bg);
    p.setColor(QPalette::ButtonText, fg);
    b->setAutoFillBackground(true);
    b->setPalette(p);
    b->update();
}

void MainWindow::applyColors() {
    {
        QPalette p = palette();
        p.setColor(QPalette::Window, QColor(18, 18, 18));
        p.setColor(QPalette::WindowText, QColor(240, 240, 240));
        setAutoFillBackground(true);
        setPalette(p);
    }
    {
        QPalette p = m_display->palette();
        p.setColor(QPalette::Base, QColor(12, 12, 12));
        p.setColor(QPalette::Text, QColor(240, 240, 240));
        m_display->setPalette(p);
    }
    const QColor digitBg(30, 30, 30);
    const QColor fg(240, 240, 240);
    const QColor opBg(38, 38, 38);
    for (auto* b : m_digitsBtns) {
        setButtonColors(b, digitBg, fg);
    }

    setButtonColors(m_btnAdd, opBg, fg);
    setButtonColors(m_btnCE, opBg, fg);
    setButtonColors(m_btnDiv, opBg, fg);
    setButtonColors(m_btnDot, opBg, fg);
    setButtonColors(m_btnEqual, opBg, fg);
    setButtonColors(m_btnMul, opBg, fg);
    setButtonColors(m_btnPM, opBg, fg);
    setButtonColors(m_btnPercent, opBg, fg);
    setButtonColors(m_btnSub, opBg, fg);
}
