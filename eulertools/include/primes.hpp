#pragma once

#include <cstdlib>
#include <type_traits>
#include <cmath>
#include <array>
#include <unordered_map>
#include <random>

#include <tools.hpp>

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

    static_assert(std::is_integral<Integer>::value, "Integral required.");
    static_assert(std::is_integral<Power>::value, "Integral required.");

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

    static_assert(std::is_integral<Integer>::value, "Integral required.");
    static_assert(std::is_integral<Power>::value, "Integral required.");

    std::unordered_map<Integer, Integer> primes;
    prime_map(n, primes);
    Integer count = 1;
    for (auto it = primes.begin(); it != primes.end(); ++it) {
        count *= power * it->second + 1;
    }
    return count;
}

/**
 * Miller-Rabin test for primality.
 * If the return is false, then n is definitively composite.
 * If the return is true, n is probably prime, with accuracy depending
 * on the value of k. k = 40 -> prob of false positive ~2^-80.
 *
 * See https://en.wikipedia.org/wiki/Miller-Rabin_primality_test
 */
template<typename Integer>
bool is_prime(Integer n, int k = 20) {
    if ( n == 2 or n == 3 ) return true;
    if ( n <= 1 or even(n) ) return false;

    static std::default_random_engine generator;
    std::uniform_int_distribution<Integer> distribution(2, n - 2);

    Integer r = 0, d = n - 1;
    for (; even(d); ++r, d >>= 1);

    for (int check = 0; check < k; ++check) {
        Integer a = distribution(generator);

        Integer x = pow_mod(a, d, n);
        if (x == 1 or x == n - 1)
            continue;

        for (Integer inner_check = 0; inner_check < r - 1; ++inner_check) {
            x = pow_mod(x, 2, n);
            if (x == 1)
                return false;
            if (x == n - 1)
                goto continue_checks;
        }
        return false;

        continue_checks:
        continue;
    }
    return true;
}

}
