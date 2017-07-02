# coding=utf-8
"""
The arithmetic sequence, 1487, 4817, 8147, in which each of the terms increases by 3330, is unusual in two ways: (i) each of the three terms are prime, and, (ii) each of the 4-digit numbers are permutations of one another.

There are no arithmetic sequences made up of three 1-, 2-, or 3-digit primes, exhibiting this property, but there is one other 4-digit increasing sequence.

What 12-digit number do you form by concatenating the three terms in this sequence?

Solution comment:
For each 4-digit prime, find all permutations of its digits that are also
themselves primes and larger than the original prime. Then check if there is
a perm, which difference to the prime, added twice, is also a perm.
"""

from projecteuler.prime import primes_up_to
from itertools import permutations as perms
from numpy import array

primes = primes_up_to(9999)
primes = primes[primes > 999]
prime_set = set(primes)

for p in primes:
    pos = array(list(prime_set & set(int(''.join(elm)) for elm in perms(str(p), 4))))
    pos = set(pos[pos > p])

    for q in pos:
        if p + 2*(q - p) in pos:
            print p, q, p + 2*(q-p)
