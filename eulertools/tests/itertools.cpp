#include <gtest/gtest.h>

#include "itertools.hpp"
#include "prettyprint.hpp"

using namespace euler::itertools;

TEST(Powerset, small_input_test) {
    std::vector<int> numbers = {1, 2, 3};
    auto powset = powerset(numbers.begin(), numbers.end());
    std::vector<std::vector<int>> expected = {{}, {1}, {2}, {3}, {1,2}, {1, 3}, {2, 3}, {1, 2, 3}};
    EXPECT_EQ(expected, powset);
}
