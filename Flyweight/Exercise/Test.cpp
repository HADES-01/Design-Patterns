#include "Exercise.cpp"
#include "gtest/gtest.h"

TEST(Evaluate, BaselineTest)
{
    Sentence s{"alpha beta gamma alpha"};
    s[0].capitalize = true;
    s[2].capitalize = false;
    s[1].capitalize = true;
    ASSERT_EQ("alpha BETA gamma alpha", s.str());
}

int main(int ac, char *av[])
{
    testing::InitGoogleTest(&ac, av);
    return RUN_ALL_TESTS();
}