#pragma once

namespace euler {

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
