#include "gtest/gtest.h"
#include "Exercise.cpp"

namespace
{
    class Evaluate : public testing::Test
    {
    };

    TEST_F(Evaluate, SimpleTest)
    {
        Square sq{11};
        SquareToRectangleAdapter adapter{sq};
        ASSERT_EQ(121, adapter.area());
    }
}

int main(int ac, char *av[])
{
    testing::InitGoogleTest(&ac, av);
    return RUN_ALL_TESTS();
}