/*
The Fibonacci sequence is defined by the recurrence relation:

    Fn = Fn−1 + Fn−2, where F1 = 1 and F2 = 1.

It turns out that F541, which contains 113 digits, is the first Fibonacci
number for which the last nine digits are 1-9 pandigital (contain all the
digits 1 to 9, but not necessarily in order). And F2749, which contains 575
digits, is the first Fibonacci number for which the first nine digits are 1-9
pandigital.

Given that Fk is the first Fibonacci number for which the first nine digits AND
the last nine digits are 1-9 pandigital, find k.

Solution comment: Quick, ~10 ms.
                  Fib(n) = round(phi^n / sqrt(5)), with phi = (1 + sqrt(5)) / 2.
                  Then, log Fib(n) = n * log phi - log sqrt(5),
                  and the first 9 digits of Fib(n) are:
                    10^(8 + fractional(log(Fib(n))))
                  The last digits we get easily by building each successive term,
                  keeping only the last 9 digits.
                  Then just a matter of searching.
 */
#include <iostream>
#include <chrono>
#include <cmath>

inline int first_digits(int n) {
    static const double logsqrt5 = std::log10(std::sqrt(5));
    static const double logphi   = std::log10((1 + std::sqrt(5)) / 2);
    auto l = n * logphi - logsqrt5;
    auto frac = l - (int) l;
    return static_cast<int>(std::pow(10, 8 + frac));
}

bool is_pandigital(int n) {
    int digits = 0;
    while (n) {
        digits |= (1 << n % 10);
        n /= 10;
    }
    return (digits|1) == 0b1111111111;  // Don't care if 0 was present.
}
int main() {
    auto start = std::chrono::high_resolution_clock::now();

    constexpr auto upper = static_cast<const int>(1e9);
    int xp = 1, x = 1, n = 1;
    while (true) {

        if (is_pandigital(xp) and is_pandigital(first_digits(n))) {
            printf("fib(%d) is pandigital in both first and last digits.\n", n);
            break;
        }
        int tmp = x;
        x = (x + xp) % upper;
        xp = tmp;
        n++;
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::nanoseconds> (end - start).count() / (double) 1e6;
    printf("Found in time: %g ms\n", time);
}
