#include "gtest/gtest.h"

#include "Exercise.cpp"

class Evaluate : public testing::Test
{
};

TEST_F(Evaluate, SimpleTest)
{
    Line line1{
        new Point{3, 3},
        new Point{10, 10}};

    auto line2 = line1.deep_copy();
    line1.start->x = line1.start->y =
        line1.end->y = line1.end->y = 0;

    ASSERT_EQ(3, line2.start->x);
    ASSERT_EQ(3, line2.start->y);
    ASSERT_EQ(10, line2.end->x);
    ASSERT_EQ(10, line2.end->y);
}

int main(int ac, char *av[])
{
    testing::InitGoogleTest(&ac, av);
    return RUN_ALL_TESTS();
}