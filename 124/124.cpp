/*
The radical of n, rad(n), is the product of the distinct prime factors of n. For example, 504 = 23 × 32 × 7, so rad(504) = 2 × 3 × 7 = 42.

If we calculate rad(n) for 1 ≤ n ≤ 10, then sort them on rad(n), and sorting on n if the radical values are equal, we get:

....

Let E(k) be the kth element in the sorted n column; for example, E(4) = 8 and E(6) = 9.

If rad(n) is sorted for 1 ≤ n ≤ 100000, find E(10000).


Solution comment: Using a sieve to generate all the radicals, then selecting out the result.
                  Quite fast, about ~1.6ms.
*/

#include <iostream>
#include <array>
#include <utility>
#include <algorithm>

#include "timing.hpp"

int main() {

    euler::Timer timer{};

    constexpr int N = 1e5 + 1;
    constexpr int target = 1e4;

    // Pairs are (rad(n), n).
    // Initialize all numbers with rad(n) = 1.
    std::array<std::pair<int, int>, N> rads;
    for (int i = 0; i < N; ++i) {
        rads[i] = {1, i};
    }

    for (int i = 2; i < N; ++i) {
        // If rads[i].first == 1, then i is a prime, and rad(i) = i.
        if (rads[i].first == 1) {
            rads[i].first = i;
            // Then every multiple of k*i has a factor of i in its radical.
            for (int j = i + i; j < N; j += i) {
                rads[j].first *= i;
            }
        }
    }

    // Find the nth smallest element. After this, rads[target] is that pair.
    std::nth_element(rads.begin(), rads.begin() + target, rads.end());

    timer.stop();
    printf("Answer: %d\n", rads[target].second);
}

