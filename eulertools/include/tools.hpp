#pragma once

#include <cassert>
#include <type_traits>

namespace euler {

/**
 * Return true if x is odd.
 */
template<typename Int>
inline constexpr bool odd(Int x) {
    static_assert(std::is_integral<Int>::value, "Integral required.");
    return static_cast<bool>(x & 1);
}
/**
 * Return true if x is even.
 */
template<typename Int>
inline constexpr bool even(Int x) {
    return not odd(x);
}

/**
 * Convenience squaring template.
 * Useful when the expression to square is long,
 * and boring to type out multiple times.
 * Works with any type that defines operator* (T, T).
 */
template<typename T>
inline auto square(T x) {
    return x * x;
}

/**
 * Fast calculation of `a^x mod n` using right-to-left
 * binary modular exponentiation.
 *
 * Note that overflow is a potential issue, if (n -1)^2
 * overflows the integer type of n.
 *
 * See http://en.wikipedia.org/wiki/Modular_exponentiation
 */
template<typename Base,
         typename Exponent,
         typename Modulus>
constexpr Modulus pow_mod(Base a, Exponent x, Modulus n) {
    static_assert(std::is_integral<Base>::value, "Integral required.");
    static_assert(std::is_integral<Exponent>::value, "Integral required.");
    static_assert(std::is_integral<Modulus>::value, "Integral required.");

    assert(x >= 0);  // only non-negative exponents.

    Modulus res = 1;
    a %= n;

    while (x) {

        if ( x & 1)
            res = (a * res) % n;

        x >>= 1;

        a = (a * a) % n;
    }
    return res;
};

}
