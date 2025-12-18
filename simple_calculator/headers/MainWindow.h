#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVector>

#include "IView.h"
#include "CalculatorModel.h"

class MainWindow : public QWidget, public IView
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);


    void setDisplayText(const QString& text) override;
    QString getDisplayText() const override;
    void showError(const QString& errorMessage) override;

signals:
    void digitPressed(int d);
    void operandPressed(Operand op);
    void dotPressed();
    void equalsPressed();
    void clearPressed();
    void toggleSignPressed();
    void percentPressed();
private:
    void buildUi();
    void connectSignals();
    QPushButton* makeButton(const QString& btnName);
private:
    QLineEdit* m_display = nullptr;

    QVector<QPushButton*> m_digitsBtns;

    QPushButton* m_btnCE = nullptr; //CE
    QPushButton* m_btnPM = nullptr; // +/-
    QPushButton* m_btnPercent = nullptr;
    QPushButton* m_btnEqual = nullptr;

    QPushButton* m_btnDiv = nullptr;
    QPushButton* m_btnMul = nullptr;
    QPushButton* m_btnSub = nullptr;
    QPushButton* m_btnAdd = nullptr;

    QPushButton* m_btnDot = nullptr;
};
#endif // MAINWINDOW_H
