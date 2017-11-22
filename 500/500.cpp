/*
 The number of divisors of 120 is 16.
 In fact 120 is the smallest number having 16 divisors.
 
 Find the smallest number with 2^500500 divisors.
 Give your answer modulo 500500507.
 
 
 Solution comment:
 Let n = sum_i p_i^(a_i), where p_i are the primes of n and a_i are
 the multiplicities. Then, as d(p^a) = (a + 1) and d(n) is multiplicative,
    d(n) = (a_1 + 1) * ... * (a_k + 1).
 For d(n) to equal a power of two, each a_i must be one less than a power of
 two. To get the smallest n, we should always multiply with the smallest new prime,
 or the smallest new power of a new prime. Always adding the square of the
 "prime" taken out will ensure that (a_i+1) remains a power of 2 for all the primes.
 A min heap is used to always select the smallest new factor.
 Prime sieve to genereate the potential primes, being the first 500500.
 Each time we take a new number, d(n) doubles.
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

template <typename int_type>
vector<int_type> prime_sieve(int_type n) {
    vector<int_type> primes = {2};
    vector<bool> is_prime (n+1, true);

    int_type m = 3;
    while (m * m <= n) {
        if (is_prime[m]) {
            primes.push_back(m);
            for (int_type k = m * m; k <= n; k += m)
                is_prime[k] = false;
        }
        m += 2;
    }
    for (; m <= n; m += 2) {
        if (is_prime[m]) {
            primes.push_back(m);
        }
    }
    return primes;
}

int main() {
    const int N        = 500500;    // 2^N.
    const uint64_t mod = 500500507;
    auto primes = prime_sieve<uint64_t>(7376507);
    const auto ascending_order = greater<uint64_t>();
    
    uint64_t x = 1;
    int d = 1;
    while (d <= N) {
        uint64_t p = primes.front();
        pop_heap(primes.begin(), primes.end(), ascending_order); primes.pop_back();
        primes.push_back(p*p); push_heap(primes.begin(), primes.end(), ascending_order);
        if ((x *= p) >= mod)
            x %= mod;
        d++;
    }
    printf("d=2^%d, x=%lld\n", d, x);
    return 0;
}
