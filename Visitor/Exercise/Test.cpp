#include "gtest/gtest.h"
#include "Exercise.cpp"

namespace {

  class Evaluate : public ::testing::Test {};

  TEST_F(Evaluate, SimpleAddition)
  {
    Value v{2};
    AdditionExpression simple{v,v};
    ExpressionPrinter ep;
    ep.accept(simple);
    ASSERT_EQ("(2+2)", ep.str());
  }

  TEST_F(Evaluate, ProductOfAdditionAndValue)
  {
    Value _2{2};
    Value _3{3};
    Value _4{4};
    AdditionExpression ae{_2, _3};
    MultiplicationExpression expr{ae, _4};
    ExpressionPrinter ep;
    ep.accept(expr);
    ASSERT_EQ("(2+3)*4", ep.str());
  }

}

int main(int ac, char* av[])
{
  testing::InitGoogleTest(&ac, av);
  return RUN_ALL_TESTS();
}