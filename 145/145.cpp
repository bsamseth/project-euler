/*
Some positive integers n have the property that the sum [ n + reverse(n) ]
consists entirely of odd (decimal) digits. For instance, 36 + 63 = 99 and 409 +
904 = 1313. We will call such numbers reversible; so 36, 63, 409, and 904 are
reversible. Leading zeroes are not allowed in either n or reverse(n).

There are 120 reversible numbers below one-thousand.

How many reversible numbers are there below one-billion (10^9)?


Solution comment: One billion is within reach of a brute force solution. ~4 secs.
Anticipating a smarter solution exists, but when it works it works.
*/

#include <iostream>
#include <array>

#include "tools.hpp"
#include "timing.hpp"

using namespace euler;

/*
 * Treat container as a number n = [d_n ... d_1 d_0] for
 * digits d_i of n. Update n to represent n+1.
 * @return False if increment overflows back to zero.
 */
template<typename Container>
bool increment(Container &n) {
    static_assert( n.size() > 0, "Number array empty. Time to turn on brain.");

    int i = n.size() - 1;
    do {
        if (n[i] < 9) {
            ++n[i];
            return true;
        } else {
            n[i--] = 0;
        }
    } while (i >= 0);

    return false;
}

/*
 * @return true if n is reversible.
 */
template<typename Container>
bool reversible(const Container &n) {
    const int size = n.size();
    int i = 0, j = size - 1;

    // Leading zeros not allowed, so cannot end with zero.
    if (n[j] == 0)
        return false;

    // Locate start of number.
    while (not n[i]) ++i;

    // Compute n + reversed(n) digit for digit, keeping track of carry.
    // If the sum is ever an even number we fail.
    int sum = 0;
    do {
        sum += n[i++] + n[j--];
        if (even(sum))
            return false;
        sum /= 10;
    } while (i < size);

    // No even sum encountered, means n is reversible.
    return true;
}

int main() {

    constexpr int digits = 9;
    std::array<unsigned char, digits> n{};

    Timer t{};

    unsigned long count = 0;
    do {
        if (reversible(n)) {
            ++count;
        }
    } while (increment(n));

    std::cout << "Answer: " << count << '\n';
    t.stop();
}
