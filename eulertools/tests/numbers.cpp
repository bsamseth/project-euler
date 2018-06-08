
#include <gtest/gtest.h>

#include "numbers.hpp"

using namespace euler::numbers;

TEST(Numbers, is_palindrome) {
    EXPECT_TRUE(is_palindrome(1234321));
    EXPECT_TRUE(is_palindrome(941149));
    EXPECT_FALSE(is_palindrome(123123));
    EXPECT_FALSE(is_palindrome(93));

    for (int i = 0; i < 10; ++i)
        ASSERT_TRUE(is_palindrome(i));
}
