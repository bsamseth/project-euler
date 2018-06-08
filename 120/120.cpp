/*
Let r be the remainder when (a−1)n + (a+1)n is divided by a2.

For example, if a = 7 and n = 3, then r = 42: 63 + 83 = 728 ≡ 42 mod 49. And as
n varies, so too will r, but for a = 7 it turns out that rmax = 42.

For 3 ≤ a ≤ 1000, find ∑ rmax.


Solution comment: Quite fast, < 30ms with OpenMP enabled.

If we generate the sequence of r's for a given value of a, there will
eventually be a repeated subsequence in there. This can probably be proved, but
empirical tests for some a's showed this to hold for all values checked. Then
we can detect when such a sequence is obtained, and find the maximum of the
sequence thus far.

Analytic solutions for any given a do exist, which would be better. This was
just the first way that came to mind.
*/
#include <iostream>
#include <algorithm>
#include <vector>
#ifdef OPENMP_ENABLED
#include <omp.h>
#endif

#include "timing.hpp"
#include "tools.hpp"

using namespace euler;

/*
 * Check if sequence is of type [ S, S ], where S is some sub-sequence.
 */
template<typename Sequence>
bool is_cycle(const Sequence &seq) {
    const auto length = seq.size();
    if (odd(length))
        return false;
    const auto split = seq.begin() + (length >> 1);
    if (std::equal(seq.begin(), split, split))
        return true;
    else
        return false;
}

int main() {
    euler::Timer timer{};

    long r_sum = 0;

#ifdef OPENMP_ENABLED
#pragma omp parallel for reduction(+:r_sum)
#endif
    for (int a = 3; a <= 1000; ++a) {
        long a2 = a * a;   // modulus
        long ap = 1;       // (a+1)^n
        long am = 1;       // (a-1)^n
        long max_r = 0;
        std::vector<long> seq;
        while (true) {
            long r = (ap + am) % a2;
            max_r = std::max(max_r, r);
            seq.push_back(r);
            if (is_cycle(seq)) {
                r_sum += max_r;
                break;
            }
            ap = ap * (a+1) % a2;
            am = am * (a-1) % a2;
        }
    }

    timer.stop();

    printf("r_sum = %ld\n", r_sum);
}
