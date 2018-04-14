/*
In the following equation x, y, and n are positive integers.

            1/x + 1/y = 1/n

It can be verified that when n = 1260 there are 113 distinct solutions
and this is the least value of n for which the total number of distinct
solutions exceeds one hundred.

What is the least value of n for which the number of distinct
solutions exceeds four million?

NOTE: This problem is a much more difficult version of Problem 108
and as it is well beyond the limitations of a brute force approach
it requires a clever implementation.

Solution comment: Based on same logic as 108. But instead of finding
the factorization of each increasing n, we now generate n's from their
prime factorization. We pre-compute enough primes, initialize their exponents
to zero and place the pair (n = 1, factors = {0, 0, ... 0}) in a queue. We
let the queue be sorted, so the smallest solution n will be found first.
we calculate (d(n^2) + 1)/2 and test for a solution. New candidates are generated
by adding new variants to the queue, were each variant is the result of incrementing
successive exponents.
This works because we know that the prime factorization must have weakly decreasing
exponents (when primes are ordered), as the order of the exponents do not matter
for the number of factors, and we want the smallest n.

We also know that we need at most 14 distinct primes, because a number with 15
distinct primes would have
        ((2*1 + 1)^15 + 1) / 2 = 7 174 454 > 4 000 000
solutions. The 14th prime is 43.

Solution refined based on euler.stephan-brumme.com
*/

#include <iostream>
#include <vector>
#include <map>
#include <iomanip>

#include "timing.hpp"
#include "primes.hpp"

using namespace euler::primes;

int main() {
    euler::Timer timer{};

    const auto primes = primes_up_to<43>();

    std::map<long double, std::vector<int>> queue = { {1., std::vector<int>(primes.size(), 0)}};

    while (true) {
        auto next = queue.begin();
        auto n = next->first;
        auto exponents = next->second;
        queue.erase(next);

        unsigned long factors = 1;
        for (auto a : exponents)
            factors *= 2*a + 1;
        ++factors;
        factors >>= 1;

        if (factors > 4000000) {
            std::cout << std::fixed << std::setprecision(0)
                      << "n = " <<   n << " = ";
            for (std::size_t i = 0; i < primes.size() and exponents[i]; ++i)
                std::cout << primes[i] << "^" << exponents[i] << " ";
            std::cout << "\nSolutions -> " << factors << '\n';
            break;
        }

        for (std::size_t i = 0; i < exponents.size(); ++i) {
            ++exponents[i];
            n *= primes[i];
            queue.emplace(n, exponents);
        }
    }

    timer.stop();
}

