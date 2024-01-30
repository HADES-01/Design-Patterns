#include "Exercise.cpp"
#include "gtest/gtest.h"

TEST(Evaluate, SimpleTest)
{
    SingleValue single_value{11};
    ManyValues other_values;
    other_values.add(22);
    other_values.add(33);
    ASSERT_EQ(77, sum({&single_value, &other_values, &single_value}));
}

int main(int ac, char *av[])
{
    testing::InitGoogleTest(&ac, av);
    return RUN_ALL_TESTS();
}