#include "calculator.h"

Calculator::Calculator(QObject *parent)
    : QObject{parent}
    , m_correctExample{true}
    , m_result{0}
{}

bool Calculator::isCorrect()
{
    return m_correctExample;
}

double Calculator::result()
{
    return m_result;
}

void Calculator::calculate(QString& example)
{
    double op2 = 0;
    bool ok = false;
    m_example = example.split(' ');

    foreach (const QString& i, m_example)
    {
        double d = i.toDouble(&ok);
        if (ok)
        {
            m_stack.push(d);
        } else {
            switch (i.toStdString()[0]) {
            case '+':
                m_stack.push(m_stack.pop() + m_stack.pop());
                break;
            case '-':
                op2 = m_stack.pop();
                m_stack.push(m_stack.pop() - op2);
                break;
            default:
                m_correctExample = false;
                return;
            }
        }
    }
    m_result = m_stack.pop();
    m_correctExample = true;
}
