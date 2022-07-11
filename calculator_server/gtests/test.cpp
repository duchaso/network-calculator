#include "gtest/gtest.h"
#include "calculator.h"

TEST(Calculation, AdditionWorks)
{
    Calculator c;
    QString ex("2 + 2");
    c.calculate(ex);
    EXPECT_EQ(c.result(), 4);
}

TEST(Calculation, SubtractionWorks)
{
    Calculator c;
    QString ex("4 - 2");
    c.calculate(ex);
    EXPECT_EQ(c.result(), 2);
}

TEST(Calculation, MultiplicationWorks)
{
    Calculator c;
    QString ex("4 * 2");
    c.calculate(ex);
    EXPECT_EQ(c.result(), 8);
}

TEST(Calculation, DivisionWorks)
{
    Calculator c;
    QString ex("4 / 2");
    c.calculate(ex);
    EXPECT_EQ(c.result(), 2);
}

TEST(Calculation, DivisionByZero)
{
    Calculator c;
    QString ex("4 / 0");

    try
    {
        c.calculate(ex);
        FAIL() << "Expected std::runtime_error";
    } catch(std::runtime_error& err) {
        EXPECT_EQ(err.what(), std::string("Division by zero"));
    } catch(...) {
        FAIL() << "Expected std::runtime_error";
    }
}

TEST(ClassInvariant, Correctness)
{
    Calculator c;
    QString ex("hlag");
    c.calculate(ex);
    EXPECT_EQ(c.isCorrect(), false);
}






