#include "MainWindow.h"

#include <QMessageBox>
#include <QGridLayout>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    buildUi();
    connectSignals();

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

    QFont f = m_display->font();
    f.setPointSize(18);
    m_display->setFont(f);

    root->addWidget(m_display, 0, 0, 1, 4);

    m_btnCE = makeButton("CE");
    m_btnPM = makeButton("+/-");
    m_btnPercent = makeButton("%");
    m_btnDiv = makeButton("/");
    m_btnMul = makeButton("*");
    m_btnSub = makeButton("-");
    m_btnAdd = makeButton("+");

    root->addWidget(m_btnCE, 1, 0);
    root->addWidget(m_btnPM, 1, 1);
    root->addWidget(m_btnPercent, 1, 2);
    root->addWidget(m_btnDiv, 1, 3);
    root->addWidget(m_btnMul, 2, 3);
    root->addWidget(m_btnSub, 3, 3);
    root->addWidget(m_btnAdd, 4, 3, 2, 1);

    m_digitsBtns.resize(10);
    for(int i = 0; i < 10; ++i) {
        m_digitsBtns[i] = makeButton(QString::number(i));
    }

    root->addWidget(m_digitsBtns[7], 2, 0);
    root->addWidget(m_digitsBtns[8], 2, 1);
    root->addWidget(m_digitsBtns[9], 2, 2);

    root->addWidget(m_digitsBtns[4], 3, 0);
    root->addWidget(m_digitsBtns[5], 3, 1);
    root->addWidget(m_digitsBtns[6], 3, 2);

    root->addWidget(m_digitsBtns[1], 4, 0);
    root->addWidget(m_digitsBtns[2], 4, 1);
    root->addWidget(m_digitsBtns[3], 4, 2);

    m_btnDot = makeButton(".");
    m_btnEqual = makeButton("=");
    root->addWidget(m_digitsBtns[0], 5, 0);
    root->addWidget(m_btnDot, 5, 1);
    root->addWidget(m_btnEqual, 5, 2);
}

void MainWindow::connectSignals() {

}


