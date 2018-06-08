/*
The palindromic number 595 is interesting because it can be written as the sum
of consecutive squares: 62 + 72 + 82 + 92 + 102 + 112 + 122.

There are exactly eleven palindromes below one-thousand that can be written as
consecutive square sums, and the sum of these palindromes is 4164. Note that 1
= 02 + 12 has not been included as this problem is concerned with the squares
of positive integers.

Find the sum of all the numbers less than 108 that are both palindromic and can
be written as the sum of consecutive squares.


Solution comment: Quite fast, ~5ms. Generating all the square sums efficiently,
then checking them for palindromes.

Incidentally, this solution looks pretty much like a translation of
mathblog.dk's solution. I swear though, I didn't cheat on this one.
*/

#include <iostream>
#include <cmath>
#include <unordered_set>
#include "timing.hpp"
#include "tools.hpp"
#include "numbers.hpp"
#include "prettyprint.hpp"

using euler::numbers::is_palindrome;
using euler::square;

int main() {
    euler::Timer timer{};

    constexpr long limit = 1e8;
    constexpr long sqrt_limit = std::sqrt(limit);

    // Some sums will equal the same number, so a set is needed to keep track
    // of the palindromes that has been added.
    std::unordered_set<long> seen;
    long sum = 0;
    for (long i = 1; i <= sqrt_limit; ++i) {
        long prev = i*i;
        for (long j = i + 1; j <= sqrt_limit; ++j) {
            prev += j*j;
            if (prev >= limit)
                break;
            else if (is_palindrome(prev) and not seen.count(prev)) {
                sum += prev;
                seen.insert(prev);
            }
        }
    }

    timer.stop();
    std::cout << "Answer: " << sum << '\n';
}

