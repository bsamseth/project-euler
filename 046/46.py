# coding=utf-8
"""
It was proposed by Christian Goldbach that every odd composite number can be written as the sum of a prime and twice a square.

9 = 7 + 2×1^2
15 = 7 + 2×2^2
21 = 3 + 2×3^2
25 = 7 + 2×3^2
27 = 19 + 2×2^2
33 = 31 + 2×1^2

It turns out that the conjecture was false.

What is the smallest odd composite that cannot be written as the sum of a prime and twice a square?

Solution comment:
Precompute primes up to a guessed bound. Then, for each composite odd
number, find the possible squares and primes. If no match is found,
a counter example is found.
"""
from  math import sqrt
from projecteuler.prime import primes_up_to

upper = 10000
primes = primes_up_to(upper)
prime_set = set(primes)


for n in xrange(3, upper+1, 2):
    if n in prime_set:
        continue
    goldbach = False
    squares = xrange(1, int(sqrt(n/2))+1)
    for sq in squares:
        primes_less = primes[primes <= n - 2*sq**2]
        for p in primes_less:
            if p + 2*sq**2 == n:
                goldbach = True
                break

        if goldbach:
            break
    else:
        print 'Found one! n = {0}'.format(n)
        break
