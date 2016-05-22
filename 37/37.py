# coding=utf-8
"""
The number 3797 has an interesting property. Being prime itself, it is possible to continuously remove digits from left to right, and remain prime at each stage: 3797, 797, 97, and 7. Similarly we can work from right to left: 3797, 379, 37, and 3.

Find the sum of the only eleven primes that are both truncatable from left to right and right to left.

NOTE: 2, 3, 5, and 7 are not considered to be truncatable primes.

Solution comment:
Going to make a guess that there is an upper boundry here, since
more digits mean more primes. Turns out, need upper to be about 1M
to get all 11 solutions.

Done with just sets (except the imported primes function), beacause sets are nice.
"""
from projecteuler import prime

def truncations(n):
    """Return all right-left and left-right truncations of n as a set"""
    s = str(n)
    left_right = {int(s[i:]) for i in xrange(len(s))}
    right_left = {int(s[0:i]) for i in xrange(1, len(s))}
    return left_right | right_left

upper = int(1e6)
all_primes = prime.primes_up_to(upper)
primes_set = set(all_primes)
primes = all_primes[4:]

trunc_primes = set()
for p in primes:
    truncs = truncations(p)
    if truncs & primes_set == truncs:
        trunc_primes.add(p)

print trunc_primes, len(trunc_primes), sum(trunc_primes)
