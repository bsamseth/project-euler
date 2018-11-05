#pragma once

#include <cstdlib>
#include <type_traits>
#include <cmath>
#include <array>
#include <unordered_map>
#include <random>

#include <tools.hpp>
#include <itertools.hpp>

namespace euler::primes {

/**
 * Return a N+1 size array of booleans such that
 * mask[a] is true iff a is a composite number.
 */
template<int N>
std::array<bool, N + 1> composite_mask() {

    static_assert(N >= 0, "N must be non-negative.");

    std::array<bool, N + 1> mask = { {true, true} };

    for (int i = 2; i*i <= N; ++i)
        if (!mask[i])
            for (int j = i * i; j <= N; j += i)
                mask[j] = true;
    return mask;
}
template<> std::array<bool, 1> composite_mask<0>() { return { {true} }; }
template<> std::array<bool, 2> composite_mask<1>() { return { {true, true} }; }

template<int N>
std::vector<int> primes_up_to() {
    const auto composite = composite_mask<N>();
    std::vector<int> primes = {2};
    for (std::size_t i = 3; i < composite.size(); i += 2)
        if (not composite[i])
            primes.push_back(i);
    return primes;
};
template<> std::vector<int> primes_up_to<0>() { return {}; }
template<> std::vector<int> primes_up_to<1>() { return {}; }
template<> std::vector<int> primes_up_to<2>() { return {2}; }

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
 * Return an unordered_map with (p : a) pairs where a is
 * the largest power of p which divides n.
 */
template<typename Integer = int,
        typename Power = int>
std::unordered_map<Integer, Power> prime_map(Integer n) {
    std::unordered_map<Integer, Power> primes;
    prime_map(n, primes);
    return primes;
}

/**
 * Return a vector with all factors of n, including duplicates.
 */
template<typename Integer = int>
std::vector<Integer> prime_list(Integer n) {
    std::vector<Integer> primes;
    for (const auto& [prime, power] : prime_map(n)) {
        for (int i = 0; i < power; ++i)
            primes.push_back(prime);
    }
    return primes;
}

/**
 * Return all divisors of n.
 */
template<typename Integer = int>
std::set<Integer> divisors(Integer n) {
    auto factors = prime_list(n);
    auto divisors = itertools::powerset(factors.begin(), factors.end());
    std::set<Integer> divs;
    for (const auto& factors : divisors) {
        divs.insert(std::accumulate(factors.begin(), factors.end(), 1, std::multiplies<Integer>()));
    }
    return divs;
}

/**
 * Return the number of divisors for n^(power).
 */
template<typename Integer = int, typename Power = int>
Integer number_of_divisors(Integer n, Power power = 1) {

    static_assert(std::is_integral<Integer>::value, "Integral required.");
    static_assert(std::is_integral<Power>::value, "Integral required.");

    auto primes = prime_map(n);
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
            x = mul_mod(x, x, n);
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
