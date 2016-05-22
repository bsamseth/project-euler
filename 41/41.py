# coding=utf-8
"""
We shall say that an n-digit number is pandigital if it makes use of all the digits 1 to n exactly once. For example, 2143 is a 4-digit pandigital and is also prime.

What is the largest n-digit pandigital prime that exists?

Solution comment:
Maximum value of n = 9 -> start with 9 going down to find the biggest.

Test all n-digit pandigitals (in decending order) for primeness,
and if one is found, this is the largest.
"""
from itertools import permutations
from projecteuler.prime import isprime

for n in xrange(9, 0, -1):
    digits = range(1, n+1)
    numbers = list(permutations(digits, n))[::-1]
    for numb in numbers:
        i = int(''.join([str(d) for d in numb]))
        if isprime(i):
            print i
            break
