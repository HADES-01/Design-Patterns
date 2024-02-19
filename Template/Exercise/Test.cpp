#include "gtest/gtest.h"
#include "Exercise.cpp"

namespace {

    class Evaluate : public ::testing::Test {};

    TEST_F(Evaluate, ImpasseTest)
    {
      Creature c1{1,2};
      Creature c2{1,2};
      TemporaryCardDamageGame game({c1,c2});
      ASSERT_EQ(-1, game.combat(0,1));
      ASSERT_EQ(-1, game.combat(0,1));
    }

    TEST_F(Evaluate, TemporaryMurderTest)
    {
      Creature c1{1,1};
      Creature c2{2,2};
      TemporaryCardDamageGame game({c1,c2});
      ASSERT_EQ(1, game.combat(0,1));
    }

    TEST_F(Evaluate, DoubleMurderTest)
    {
      Creature c1{2,2};
      Creature c2{2,2};
      TemporaryCardDamageGame game({c1,c2});
      ASSERT_EQ(-1, game.combat(0,1)) << "The expectation here is that two 2/2 creatures kill each other";
    }

    TEST_F(Evaluate, PermanentDamageDeathTest)
    {
      Creature c1{1,2};
      Creature c2{1,3};
      PermanentCardDamageGame game({c1, c2});
      ASSERT_EQ(-1, game.combat(0,1)) << "1/2 vs 1/3 should have no winner after first round of combat";
      ASSERT_EQ(1, game.combat(0,1)) << "1/1 vs 1/2 here, so winner should be = 1";
    }

}  // namespace

// ERROR ON UDEMY'S END, POST AGAIN

int main(int ac, char* av[])
{
  //::testing::GTEST_FLAG(catch_exceptions) = false;
  testing::InitGoogleTest(&ac, av);
  return RUN_ALL_TESTS();
}