#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QObject>
#include <QStack>

class Calculator : public QObject
{
    Q_OBJECT
public:
    explicit Calculator(QObject *parent = nullptr);

public:
    bool isCorrect();
    double result();
    void calculate(QString& example);

private:
    QStringList m_example;
    QStack<double> m_stack;
    bool m_correctExample;
    double m_result;
};

#endif // CALCULATOR_H
