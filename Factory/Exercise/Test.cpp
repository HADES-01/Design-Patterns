#include "Exercise.cpp"
#include <gtest/gtest.h>

class Evaluate : public testing::Test
{
};

TEST_F(Evaluate, SimplePersonTest)
{
    PersonFactory pf;

    auto p1 = pf.create_person("Chris");
    ASSERT_EQ("Chris", p1.name);

    auto p2 = pf.create_person("Sarah");
    ASSERT_EQ(1, p2.id) << "Expected the second created person's id to be = 1";
}

int main(int ac, char *av[])
{
    testing::InitGoogleTest(&ac, av);
    return RUN_ALL_TESTS();
}