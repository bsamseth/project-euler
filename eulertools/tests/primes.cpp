#include <gtest/gtest.h>

#include "primes.hpp"

using namespace euler::primes;

TEST(Primes, composite_mask) {
    auto mask = composite_mask<11>();
    ASSERT_EQ(12U, mask.size());
    EXPECT_TRUE(mask[0]);
    EXPECT_TRUE(mask[1]);
    EXPECT_TRUE(mask[4]);
    EXPECT_TRUE(mask[6]);
    EXPECT_TRUE(mask[8]);
    EXPECT_TRUE(mask[9]);
    EXPECT_TRUE(mask[10]);
    EXPECT_FALSE(mask[2]);
    EXPECT_FALSE(mask[3]);
    EXPECT_FALSE(mask[5]);
    EXPECT_FALSE(mask[7]);
    EXPECT_FALSE(mask[11]);
}

TEST(Primes, composite_mask_tiny_N) {
    auto mask0 = composite_mask<0>();
    auto mask1 = composite_mask<1>();
    ASSERT_EQ(1U, mask0.size());
    ASSERT_EQ(2U, mask1.size());
    ASSERT_TRUE(mask0[0]);
    ASSERT_TRUE(mask1[0]);
    ASSERT_TRUE(mask1[1]);
}

TEST(Primes, primes_up_to) {
    auto primes = primes_up_to<11>();
    ASSERT_EQ(5U, primes.size());
    ASSERT_EQ(2, primes[0]);
    ASSERT_EQ(3, primes[1]);
    ASSERT_EQ(5, primes[2]);
    ASSERT_EQ(7, primes[3]);
    ASSERT_EQ(11, primes[4]);
}

TEST(Primes, primes_up_to_tiny_N) {
    auto p0 = primes_up_to<0>();
    auto p1 = primes_up_to<1>();
    auto p2 = primes_up_to<2>();
    ASSERT_EQ(0U, p0.size() + p1.size());
    ASSERT_EQ(1U, p2.size());
    ASSERT_EQ(2, p2[0]);
}

TEST(Primes, prime_map) {
    std::map<int, int> primes;
    prime_map(2*2*2*3*3*11, primes);
    ASSERT_EQ(3U, primes.size());
    ASSERT_TRUE(primes.count(2));
    ASSERT_EQ(3, primes[2]);
    ASSERT_TRUE(primes.count(3));
    ASSERT_EQ(2, primes[3]);
    ASSERT_TRUE(primes.count(11));
    ASSERT_EQ(1, primes[11]);
}

TEST(Primes, number_of_divisors) {
    EXPECT_EQ(2, number_of_divisors(17));
    EXPECT_EQ(8, number_of_divisors(24));
    EXPECT_EQ(21, number_of_divisors(24*24));
    EXPECT_EQ(21, number_of_divisors(24, 2));
    EXPECT_EQ(40, number_of_divisors(24, 3));
}


TEST(Primes, is_prime) {
    EXPECT_TRUE(is_prime(2));
    EXPECT_TRUE(is_prime(3));
    EXPECT_FALSE(is_prime(4));
    EXPECT_TRUE(is_prime(13));

    EXPECT_TRUE(is_prime(179426549UL));
    EXPECT_FALSE(is_prime(179426551UL));
}
