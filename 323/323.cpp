/*

Let y0, y1, y2,... be a sequence of random unsigned 32 bit integers (i.e. 0 ≤
yi < 232, every value equally likely).

For the sequence xi the following recursion is given:

x0 = 0 and xi = xi-1| yi-1, for i > 0. ( | is the bitwise-OR operator) It can
be seen that eventually there will be an index N such that xi = 232 -1 (a
bit-pattern of all ones) for all i ≥ N.

Find the expected value of N. Give your answer rounded to 10 digits after the
decimal point.


Solution comment:

Let E[n] be the expected number of tries to fix n remaining zeros.

For n=2, potential outcomes after one try is 00, 01, 10, 11:

    E[2] = 2^(-2) * ( (1 + E[2]) + 2 * (1 + E[1]) + (1 + E[0]) )

where E[0] is defined as 0. Then solve for E[2]. Generalizing,

    E[n] = ( 1 + sum_{k=1}^n  ( n choose k ) * (1 + E[n-k])  ) / (2^n - 1).

We want E[32], so we can build the table of solutions iteratively from E[0] = 0.
 */

#include <iostream>
#include <algorithm>
#include <numeric>
#include <cmath>

#include "timing.hpp"


constexpr auto choose(int n, int k) {
    double res = 1;
    for (int i = 1; i <= k; ++i) {
        res *= n - k + i;
        res /= i;
    }
    return static_cast<int>(std::round(res));
}


int main() {

    euler::Timer timer {};

    constexpr int N = 32;

    double E[N+1];
    E[0] = 0;

    for (int n = 1; n <= N; ++n) {
        double s = 0;
        for (int k = 1; k <= n; ++k) {
            s += choose(n, k) * (1 + E[n-k]);
        }
        E[n] = (1 + s) / (std::pow(2, n) - 1);
    }

    printf("Expectation: %.10f\n", E[N]);

    timer.stop();

}
