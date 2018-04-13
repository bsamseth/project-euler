#pragma once

#include <unordered_map>
#include <cmath>

namespace euler::primes {

/**
 * Return a N+1 size array of booleans such that
 * mask[a] is true iff a is a composite number.
 */
template<int N>
constexpr std::array<bool, N + 1> composite_mask() {

    static_assert(N >= 0, "N must be non-negative.");

    std::array<bool, N + 1> mask = {true, true};

    for (int i = 2; i*i <= N; ++i)
        if (!mask[i])
            for (int j = i * i; j <= N; j += i)
                mask[j] = true;
    return mask;
}
template<> constexpr std::array<bool, 1> composite_mask<0>() { return {true}; };
template<> constexpr std::array<bool, 2> composite_mask<1>() { return {true, true}; };

/**
 * Fill a supplied map with (p : a) pairs where a is
 * the largest power of p which divides n.
 */
template<typename Integer = int,
         typename Power = int,
         typename Maptype = std::unordered_map<Integer, Power>>
void prime_map(Integer n, Maptype &map) {

    Integer d = 2;

    while (d * d <= n) {
        while (n % d == 0) {
            if (map.count(d)) {
                map[d] += 1;
            } else {
                map.emplace(d, 1);
            }
            n /= d;
        }
        ++d;
    }

    if (n > 1)
        map.emplace(n, 1);
};


/**
 * Return the number of divisors for n^(power).
 */
template<typename Integer = int, typename Power = int>
Integer number_of_divisors(Integer n, Power power = 1) {
    std::unordered_map<Integer, Integer> primes;
    prime_map(n, primes);
    Integer count = 1;
    for (auto [p, a] : primes) {
        count *= power * a + 1;
    }
    return count;
}
}
