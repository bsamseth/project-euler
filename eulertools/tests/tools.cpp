#include <gtest/gtest.h>

#include "tools.hpp"

using namespace euler;

TEST(Tools, even_odd) {
    ASSERT_TRUE(even(28));
    ASSERT_TRUE(odd(29));
}

TEST(Tools, square) {
    ASSERT_EQ(123*123, square(123));
    ASSERT_DOUBLE_EQ(123.321*123.321, square(123.321));
}

TEST(Tools, pow_mod) {
    ASSERT_EQ(723, pow_mod(123, 321, 1000));
    ASSERT_EQ(1, pow_mod(100, 0, 101));

    ASSERT_EQ(723UL, pow_mod(123ULL, 321, 1000UL));
}
