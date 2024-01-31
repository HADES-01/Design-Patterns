#include "gtest/gtest.h"
#include "Exercise.cpp"

namespace
{
  class Evaluate : public testing::Test
  {
  public:
    Rose rose;
    BlueFlower blue_rose{rose};
    RedFlower red_rose{rose};
  };

  TEST_F(Evaluate, BaselineTest)
  {
    ASSERT_EQ("A rose", Rose{}.str());
  }

  TEST_F(Evaluate, SingleColorTests)
  {
    ASSERT_EQ("A rose that is blue", blue_rose.str());
    ASSERT_EQ("A rose that is red", red_rose.str());
  }

  TEST_F(Evaluate, RepetitionTest)
  {
    ASSERT_EQ("A rose that is red", RedFlower{red_rose}.str())
            << "This rose was made red twice, but you should print once.";
  }

  TEST_F(Evaluate, MultiColorTests)
  {
    ASSERT_EQ("A rose that is red and blue",
      BlueFlower{red_rose}.str());
    ASSERT_EQ("A rose that is blue and red",
      RedFlower{blue_rose}.str());
  }

  TEST_F(Evaluate, NestedRepetitionTest)
  {
    BlueFlower b_r_rose{red_rose};
    RedFlower r_b_r_rose{b_r_rose};
    ASSERT_EQ("A rose that is red and blue",
      r_b_r_rose.str())
      << "This is a complicated case. I'm expecting that "
      << "a rose defined as Red{Blue{Red{Rose{}}}} is printed "
      << "as 'red and blue'.";
  }

} // namespace

int main(int ac, char* av[])
{
  testing::InitGoogleTest(&ac, av);
  return RUN_ALL_TESTS();
}