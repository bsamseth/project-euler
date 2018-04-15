/*
Working from left-to-right if no digit is exceeded by the digit to its left it
is called an increasing number; for example, 134468.

Similarly if no digit is exceeded by the digit to its right it is called a
decreasing number; for example, 66420.

We shall call a positive integer that is neither increasing nor decreasing a
"bouncy" number; for example, 155349.

As n increases, the proportion of bouncy numbers below n increases such that
there are only 12951 numbers below one-million that are not bouncy and only
277032 non-bouncy numbers below 1010.

How many numbers below a googol (10100) are not bouncy?


Solution comment: Zero run time. Really.
Carefull listing of the increasing numbers leads one to find
the pattern for all numbers less than 10^d:

    sum_{i=1}^10  sum_{j=1}^i  sum_{k=1}^j  ...  sum_{y=1}^{x} y

where there are d-1 such sums. The formula for this is:

    prod_{i=0}^{d-1} (10 + i) / (i+1)

The decreasing numbers are the same, but also includes the number of increasing
numbers with (d-1) digits, (d-2) digits ... due to the trailing/leading zero
being treated differently.

Then we must subtract the numbers that are counted twice, (d-1) * 9 + 1. Euler seems to
count differently, off by one. So call that (d-1) * 9 + 2 numbers to subtract.

Could have been solved trivially with loops, but the following does all
computations on compile time, and the result is stored litteraly in the byte
code of the executable. So run time is zero, excluding the time it takes to
print.

 */
#include <iostream>

template<int d>
constexpr unsigned long long increasing() {
    return (increasing<d-1>() * (10 + d-1)) / d;
}
template<>
constexpr unsigned long long increasing<1>() { return 10; }

template<int d>
constexpr auto decreasing() {
    return decreasing<d-1>() + increasing<d>() - 1;
}
template<> constexpr auto decreasing<1>() { return increasing<1>(); }

template<int d>
constexpr auto non_bouncy() {
    return increasing<d>() + decreasing<d>() - d * 9 - 2;
}

int main() {
    constexpr int d = 100;
    std::cout << "Answer: " << non_bouncy<d>() << '\n';
}
