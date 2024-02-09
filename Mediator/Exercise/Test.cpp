#include "Exercise.cpp"
#include "gtest/gtest.h"

TEST(Evaluate, LongMediationTest)
{
    Mediator m;
    Participant p1{m}, p2{m};
    ASSERT_EQ(0, p1.value);
    ASSERT_EQ(0, p2.value);

    p1.say(2);

    ASSERT_EQ(0, p1.value);
    ASSERT_EQ(2, p2.value);

    p2.say(4);

    ASSERT_EQ(4, p1.value);
    ASSERT_EQ(2, p2.value);
}

int main()
{
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
