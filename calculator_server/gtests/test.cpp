#include "gtest/gtest.h"
#include "calculator.h"

TEST(test1, myTest)
{
    Calculator c;
    QString ex("2 2 -");
    c.calculate(ex);
    EXPECT_EQ(c.result(), 0);
}

TEST(test2, myTest2)
{
    EXPECT_EQ(1, 2);
}
