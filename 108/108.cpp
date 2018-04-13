/*
In the following equation x, y, and n are positive integers.

        1/x + 1/y = 1/n

For n = 4 there are exactly three distinct solutions:

        1/5 + 1/20 = 1/4
        1/6 + 1/12 = 1/4
        1/8 + 1/8  = 1/4

What is the least value of n for which the number of distinct solutions exceeds
one-thousand?

NOTE: This problem is an easier version of Problem 110; it is strongly advised
that you solve this one first.


Solution comment: Final version simplified somewhat based on mathblog.dk write-up,
                  although original also worked. Math is just a little cleaner now:

                  Rewrite as

                     n(x + y) = x*y
                  Then, observing that x and y must be greater than n, substitute

                    x = n + r, y = n + s

                  Giving:

                    n^2 = r * s

                  This means any pair of divisors of n^2 will give a solution. Half of these
                  pairs are the unique. Because n^2 is a square, it has an odd number of divisors,
                  meaning we don't divide the 1/2n + 1/2n = 1/n solution by two. So, with
                  d(n) being the number of divisors of n, we want to find n so that

                    ( d(n) + 1 ) / 2 > 1000.
*/

#include <iostream>
#include <vector>
#include <chrono>

#include "primes.hpp"

using namespace std::chrono;
using namespace euler::primes;

int main() {
    auto start = high_resolution_clock::now();

    int n = 4;
    int best = 3;

    while (best <= 1000) {
        ++n;

        int solutions = (number_of_divisors(n, 2) + 1) / 2;

        best = std::max(best, solutions);
    }


    auto time = duration_cast<nanoseconds>(high_resolution_clock::now() - start).count() / (double) 1e6;
    printf("Answer: n = %d -> solutions = %d\n", n, best);
    printf("Found in %.3f ms\n", time);

}
