#pragma once

#include <cassert>
#include <type_traits>

namespace euler::numbers {

/**
 * Return true if x is a palindromic number.
 */
template<typename Int>
constexpr bool is_palindrome(Int x) {
    static_assert(std::is_integral<Int>::value, "Integral required.");

    Int t = x, m = 0;
    do {
        m = m * 10 + t % 10;
    } while (t /= 10);

    return x == m;
}

/**
 * Return the digit sum of a base-10 number.
 */
template<typename Int>
constexpr bool digit_sum(Int x) {
    static_assert(std::is_integral<Int>::value, "Integral required.");

    Int s = 0;
    do {
        s += x % 10;
    } while (x /= 10);

    return s;
}
}
