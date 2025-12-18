#ifndef CALCULATORMODEL_H
#define CALCULATORMODEL_H

#include <QString>

enum Operand {
    None,
    Add,
    Sub,
    Mul,
    Div
};

struct CalcResult {
    bool ok = false;
    double value = 0.0;
    QString error;
};

class CalculatorModel {
public:
    static CalcResult compute(double a, double b, Operand op) {
        switch(op) {
        case Operand::Add: return {true, a + b, {}};
        case Operand::Sub: return {true, a - b, {}};
        case Operand::Mul: return {true, a * b, {}};
        case Operand::Div:
            if(b == 0) {
                return {false, 0.0, "Error: dividing by 0"};
            }
            else {
                return {true, a / b, {}};
            };
        case Operand::None: return {false, 0.0, "Opertion not selected"};
        }

        return {false, 0.0, "Operation not defined"};
    }
};

#endif // CALCULATORMODEL_H
