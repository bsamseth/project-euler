/*
A Harshad or Niven number is a number that is divisible by the sum of its
digits.  201 is a Harshad number because it is divisible by 3 (the sum of its
digits.) When we truncate the last digit from 201, we get 20, which is a
Harshad number.  When we truncate the last digit from 20, we get 2, which is
also a Harshad number.  Let's call a Harshad number that, while recursively
truncating the last digit, always results in a Harshad number a right
truncatable Harshad number.

Also: 201/3=67 which is prime.  Let's call a Harshad number that, when divided
by the sum of its digits, results in a prime a strong Harshad number.

Now take the number 2011 which is prime.  When we truncate the last digit from
it we get 201, a strong Harshad number that is also right truncatable.  Let's
call such primes strong, right truncatable Harshad primes.

You are given that the sum of the strong, right truncatable Harshad primes less
than 10000 is 90619.

Find the sum of the strong, right truncatable Harshad primes less than 1014.


Solution comment: Quite fast, <100 ms. Hard to optimize further.

Starting with all single digit numbers, which are Harshads, we can add digits
that produces new Harshads. If adding a digit does not give a new Harshad, then
it is either because we just hit a boring number, or it could be that we hit a
prime. If this prime, without its last digit added happens to be a strong
Harshad (and also truncatable by design) then the prime is a strong right
truncatable Harshad prime.

This problem really put the eulertools to the test, showing overflow issues in
pow_mod, which is used in the Miller-Rabbin primality test.  I don't think this
is solvable without that test btw., as the numbers are way to big to test by
trial division. Now there should be no overflow issues left, as handling of it
is explicitly done when needed.

I really don't agree with the 10% difficulty of this one, clearly much harder
than many other problems in the 30-40% range.

*/

#include <iostream>
#include "timing.hpp"
#include "primes.hpp"

using euler::primes::is_prime;

using Int = uint64_t;
Int sum = 0;

void build_strong_Harshad_prime(Int base, Int base_digit_sum, int depth) {
    if (depth < 1)
        return;

    bool base_is_strong = is_prime(base / base_digit_sum);

    for (Int digit = 0; digit <= 9; ++digit) {
        Int x = base * 10 + digit;
        Int digit_sum = base_digit_sum + digit;
        if (x % digit_sum != 0) {
            if ( base_is_strong and is_prime(x)) {
                sum += x;
            }
            continue;
        }

        build_strong_Harshad_prime(x, digit_sum, depth - 1);
    }
}

int main() {
    euler::Timer timer {};

    constexpr Int digits = 14;

    for (Int base = 1; base <= 9; ++base) {
        build_strong_Harshad_prime(base, base, digits - 1);
    }
    std::cout << "Answer: " << sum << std::endl;

    timer.stop();
}
