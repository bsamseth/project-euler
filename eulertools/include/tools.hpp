#pragma once

#include <cassert>
#include <type_traits>
#include <limits>

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
 * Return (a * b) % modulo, handling potential overflow in multiplication.
 */
template<typename IntA,
        typename IntB,
        typename Modulus>
Modulus mul_mod(IntA A, IntB B, Modulus modulo) {

    static_assert(std::is_integral<IntA>::value, "Integral required.");
    static_assert(std::is_integral<IntB>::value, "Integral required.");
    static_assert(std::is_integral<Modulus>::value, "Integral required.");

    static constexpr auto modulus_max_value = std::numeric_limits<Modulus>::max();

    // (a * b) % modulo = (a % modulo) * (b % modulo) % modulo
    Modulus a = A % modulo;
    Modulus b = B % modulo;

    // fast path
    if (b == 0 or a <= modulus_max_value / b)
        return (a * b) % modulo;

    // we might encounter overflows (slow path)
    // the number of loops depends on b, therefore try to minimize b
    if (b > a)
        std::swap(a, b);

    // bitwise multiplication
    Modulus result = 0;
    while (a > 0 && b > 0) {
        // b is odd ? a*b = a + a*(b-1)
        if (odd(b)) {
            result += a;
            if (result >= modulo)
                result -= modulo;
        }

        // b is even ? a*b = (2*a)*(b/2)
        a <<= 1;
        if (a >= modulo)
            a -= modulo;

        // next bit
        b >>= 1;
    }

    return result;
}

/**
 * Fast calculation of `a^x mod n` using right-to-left
 * binary modular exponentiation.
 *
 * Safe from overfow issues due to use of mul_mod.
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

        if ( odd(x) )
            res = mul_mod(a, res, n);

        x >>= 1;

        a = mul_mod(a, a, n);
    }
    return res;
};



template<typename Base, typename Exponent>
Base pow(Base base, Exponent exp) {
    Base result = 1;
    while (true) {
        if (odd(exp))
            result *= base;
        exp >>= 1;
        if (!exp)
            break;
        base *= base;
    }
    return result;
}

}
