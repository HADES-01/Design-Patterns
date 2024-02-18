#include "gtest/gtest.h"
#include "Exercise.cpp"

namespace {

    class Evaluate : public ::testing::Test {};

    TEST_F(Evaluate, PositiveTestOrdinaryStrategy)
    {
      OrdinaryDiscriminantStrategy strategy;
      QuadraticEquationSolver solver{strategy};
      auto results = solver.solve(1,10,16);
      ASSERT_EQ(complex<double>(-2,0), get<0>(results));
      ASSERT_EQ(complex<double>(-8,0), get<1>(results));
    }

    TEST_F(Evaluate, PositiveTestRealStrategy)
    {
      RealDiscriminantStrategy strategy;
      QuadraticEquationSolver solver{strategy};
      auto results = solver.solve(1,10,16);
      ASSERT_EQ(complex<double>(-2,0), get<0>(results));
      ASSERT_EQ(complex<double>(-8,0), get<1>(results));
    }

    TEST_F(Evaluate, NegativeTestOrdinaryStrategy)
    {
      OrdinaryDiscriminantStrategy strategy;
      QuadraticEquationSolver solver{strategy};
      auto results = solver.solve(1,4,5);
      ASSERT_EQ(complex<double>(-2,1), get<0>(results));
      ASSERT_EQ(complex<double>(-2,-1), get<1>(results));
    }

    TEST_F(Evaluate, NegativeTestRealStrategy)
    {
      RealDiscriminantStrategy strategy;
      QuadraticEquationSolver solver{strategy};
      auto results = solver.solve(1,4,5);
      auto x1 = get<0>(results);
      auto x2 = get<1>(results);
      ASSERT_TRUE(isnan(x1.real()));
      ASSERT_TRUE(isnan(x2.real()));
      ASSERT_TRUE(isnan(x1.imag()));
      ASSERT_TRUE(isnan(x2.imag()));
    }

}
int main(int ac, char* av[])
{
  //::testing::GTEST_FLAG(catch_exceptions) = false;
  testing::InitGoogleTest(&ac, av);
  return RUN_ALL_TESTS();
}