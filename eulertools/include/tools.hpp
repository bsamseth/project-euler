#pragma once

#include <cassert>
#include <type_traits>

namespace euler {

/**
 * Return true if x is odd.
 */
template<typename Int>
inline bool odd(Int x) {
    static_assert(std::is_integral<Int>::value, "Integral required.");
    return static_cast<bool>(x & 1);
}
/**
 * Return true if x is even.
 */
template<typename Int>
inline bool even(Int x) {
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

}
