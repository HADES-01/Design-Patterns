#include "gtest/gtest.h"
#include "Exercise.cpp"

namespace {

    class Evaluate : public ::testing::Test {};

    TEST_F(Evaluate, SingleRatTest)
    {
      Game game;
      Rat rat{game};
      ASSERT_EQ(1, rat.attack);
    }

    TEST_F(Evaluate, TwoRatTest)
    {
      Game game;
      Rat rat{game};
      Rat rat2{game};
      ASSERT_EQ(2, rat.attack);
      ASSERT_EQ(2, rat2.attack);
    }

    TEST_F(Evaluate, ThreeRatsOneDies)
    {
      Game game;
      Rat rat{game};
      ASSERT_EQ(1, rat.attack);

      Rat rat2{game};
      ASSERT_EQ(2, rat.attack);
      ASSERT_EQ(2, rat2.attack);

      {
        Rat rat3{game};

        ASSERT_EQ(3, rat.attack);
        ASSERT_EQ(3, rat2.attack);
        ASSERT_EQ(3, rat3.attack);
      }

      ASSERT_EQ(2, rat.attack);
      ASSERT_EQ(2, rat2.attack);
    }

}  // namespace

int main(int ac, char* av[])
{
  //::testing::GTEST_FLAG(catch_exceptions) = false;
  testing::InitGoogleTest(&ac, av);
  return RUN_ALL_TESTS();
}