#include "gtest/gtest.h"

#include "Exercise.cpp"

TEST(Evaluate, SimpleTest)
{
    ASSERT_EQ("Drawing Square as lines", Square{VectorRenderer()}.str());
}

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}