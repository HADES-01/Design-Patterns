#include "gtest/gtest.h"
#include "Exercise.cpp"

namespace
{
  class Evaluate : public testing::Test
  {
  public:
  };

  TEST_F(Evaluate, LotsOfAccountTests)
  {
    Account a;
    Command command{Command::deposit, 100};
    a.process(command);

    ASSERT_EQ(100, a.balance);
    ASSERT_TRUE(command.success);

    command = Command{Command::withdraw, 50};
    a.process(command);

    ASSERT_EQ(50, a.balance);
    ASSERT_TRUE(command.success);

    command = Command{Command::withdraw, 150};
    a.process(command);

    ASSERT_EQ(50, a.balance);
    ASSERT_FALSE(command.success);
  }
} // namespace

int main(int ac, char* av[])
{
  testing::InitGoogleTest(&ac, av);
  return RUN_ALL_TESTS();
}