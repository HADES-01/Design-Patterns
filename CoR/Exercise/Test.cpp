#include "gtest/gtest.h"
#include "Exercise.cpp"

namespace
{
  class Evaluate : public testing::Test
  {
  public:
  };

  TEST_F(Evaluate, ManyGoblinsTest)
  {
    Game game;
    Goblin goblin{game};
    game.creatures.push_back(&goblin);

    cout << "Checking that a baseline goblin is a 1/1...\n";

    ASSERT_EQ(1, goblin.get_attack());
    ASSERT_EQ(1, goblin.get_defense());

    cout << "Adding a second goblin, now they should be 1/2...\n";
    Goblin goblin2{game};
    game.creatures.push_back(&goblin2);

    ASSERT_EQ(1, goblin.get_attack());
    ASSERT_EQ(2, goblin.get_defense());

    cout << "Adding a goblin king, now a goblin should be 2/3...\n";
    GoblinKing goblin3{game};
    game.creatures.push_back(&goblin3);

    ASSERT_EQ(2, goblin.get_attack());
    ASSERT_EQ(3, goblin.get_defense());
  }

} // namespace

int main(int ac, char* av[])
{
  testing::InitGoogleTest(&ac, av);
  return RUN_ALL_TESTS();
}