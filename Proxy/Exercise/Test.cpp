#include "Exercise.cpp"
#include "gtest/gtest.h"

TEST(Evaluate, BaselineTest)
{
    Person p{10};
    ResponsiblePerson rp{p};

    ASSERT_EQ("too young", rp.drive());
    ASSERT_EQ("too young", rp.drink());
    ASSERT_EQ("dead", rp.drink_and_drive());

    rp.set_age(20);

    ASSERT_EQ("driving", rp.drive());
    ASSERT_EQ("drinking", rp.drink());
    ASSERT_EQ("dead", rp.drink_and_drive());
}

int main(int ac, char *av[])
{
    testing::InitGoogleTest(&ac, av);
    return RUN_ALL_TESTS();
}