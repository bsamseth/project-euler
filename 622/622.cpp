/*
A riffle shuffle is executed as follows: a deck of cards is split into two
equal halves, with the top half taken in the left hand and the bottom half
taken in the right hand. Next, the cards are interleaved exactly, with the top
card in the right half inserted just after the top card in the left half, the
2nd card in the right half just after the 2nd card in the left half, etc. (Note
that this process preserves the location of the top and bottom card of the
deck)

Let s(n) be the minimum number of consecutive riffle shuffles needed to restore
a deck of size n to its original configuration, where n is a positive even
number.

Amazingly, a standard deck of 52 cards will first return to its original
configuration after only 8 perfect shuffles, so s(52)=8. It can be verified
that a deck of 86 cards will also return to its original configuration after
exactly 8 shuffles, and the sum of all values of n that satisfy s(n)=8 is 412.

Find the sum of all values of n that satisfy s(n)=60.


Solution comment: A perfect shuffle takes the k-th card to position 2k (mod n-1).
After j iterations the card is at 2^j * k (mod n-1). We want to find j so that 2^j * k = k (mod n-1),
for all the k values. That is, we want to find for what n we have that 2^j - 1 is divisible by n-1, for some j.
It is also important that 2^i-1 does not divide by n-1, for i < j, because this
means the deck returned to its starting position earlier.

Luckily 2^60-1 is just within a uint64_t, so we can do this.

Pretty fast as well, due to efficient calculation of divisors. Around 50 ms.
*/
#include <iostream>
#include <unordered_set>

#include "timing.hpp"
#include "primes.hpp"

int main() {

    euler::Timer timer {};

    constexpr uint64_t target = 60;

    // Find all divisors of 2^i - 1 for i < target.
    std::unordered_set<uint64_t> others;
    for (unsigned i = 2; i < target - 1; ++i) {
        auto divs = euler::primes::divisors((1ULL << i) - 1ULL);
        others.insert(divs.begin(), divs.end());
    }

    // Find 2^target - 1 divisors.
    auto ours = euler::primes::divisors((1ULL << target) - 1ULL);

    // Sum all divisors that are not among the others.
    uint64_t sum = 0;
    for (const auto div : ours) {
        if (not others.count(div)) {
            sum += div + 1;
        }
    }
    std::cout << "Sum = " << sum << std::endl;
    timer.stop();
};
