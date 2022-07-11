#include "calculator.h"

Calculator::Calculator(QObject *parent)
    : QObject{parent}
    , m_correctExample{true}
    , m_result{0}
{}

const QMap<QString, int> Calculator::m_opPrecedence {
    {"+", 0},
    {"-", 0},
    {"*", 1},
    {"/", 1}
};

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

    convertToPolishNotation(example);
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
            case '*':
                m_stack.push(m_stack.pop() * m_stack.pop());
                break;
            case '/':
                op2 = m_stack.pop();
                if (op2 == 0)
                {
                    throw std::runtime_error("Division by zero");
                    return;
                }
                m_stack.push(m_stack.pop() / op2);
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

void Calculator::convertToPolishNotation(QString &example)
{
    auto tmpList = example.split(' ');
    QStack<QString> stOp;

    bool ok = false;
    foreach(const auto& i, tmpList)
    {
        i.toDouble(&ok);
        if (ok)
        {
            m_example.push_back(i);
        } else if (i == "(") {
            stOp.push(i);
        } else if (i == ")") {
            while (!stOp.isEmpty() && stOp.top() != "(")
            {
                m_example.push_back(stOp.pop());
            }
            stOp.pop();
        } else {
            while (!stOp.isEmpty() && m_opPrecedence[stOp.top()] >= m_opPrecedence[i])
            {
                m_example.push_back(stOp.pop());
            }
            stOp.push(i);
        }
    }

    while (!stOp.isEmpty())
    {
        m_example.push_back(stOp.pop());
    }
}
