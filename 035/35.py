# coding=utf-8
"""
The number, 197, is called a circular prime because all rotations of the digits: 197, 971, and 719, are themselves prime.

There are thirteen such primes below 100: 2, 3, 5, 7, 11, 13, 17, 31, 37, 71, 73, 79, and 97.

How many circular primes are there below one million?

Solution comment:
Make use of module fuction to get all primes up to 1 million. Just need the
set, so just keep the set for faster lookup.

Shift number by shifting the string of it.

Can test circular shifts for primeness by testing for membership in
prime set, beacause no circular shift can be bigger than a number
with one more digit.
"""

from projecteuler import prime

def shift(s, n=1):
    """Rightshift string n places, with wrap around"""
    return s[-n:] + s[:-n]

def circular(s):
    """Return list of all circular shifts of number s"""
    return [int(shift(str(s), i)) for i in xrange(1, len(str(s)))]


upper = 1000000
primes = set(prime.primes_up_to(upper))

circular_primes = []
for p in primes:
    for circ in circular(p):
        if circ not in primes:
            break
    else:
        circular_primes.append(p)

print circular_primes
print len(circular_primes)
