#include "gtest/gtest.h"
#include <sstream>
#include "Exercise.cpp"
using namespace std;

namespace {

    class Evaluate : public ::testing::Test {};

    TEST_F(Evaluate, ExampleTest) {
      Node<char> c{'c'};
      Node<char> d{'d'};
      Node<char> e{'e'};
      Node<char> b{'b', &c, &d};
      Node<char> a{'a', &b, &e};

      vector<Node<char>*> result;
      a.preorder_traversal(result);

      ostringstream oss;
      for (auto n : result)
        oss << n->value;
      ASSERT_EQ("abcde", oss.str());
    }

}  // namespace

int main(int ac, char* av[])
{
  //::testing::GTEST_FLAG(catch_exceptions) = false;
  testing::InitGoogleTest(&ac, av);
  return RUN_ALL_TESTS();
}