# -*- coding: utf-8 -*-
"""
Let d(n) be defined as the sum of proper divisors of n (numbers less than n which divide evenly into n).
If d(a) = b and d(b) = a, where a ≠ b, then a and b are an amicable pair and each of a and b are called amicable numbers.

For example, the proper divisors of 220 are 1, 2, 4, 5, 10, 11, 20, 22, 44, 55 and 110; therefore d(220) = 284. The proper divisors of 284 are 1, 2, 4, 71 and 142; so d(284) = 220.

Evaluate the sum of all the amicable numbers under 10000.

Solution commment:
I evaluate d(n) by first prime factorizing n, taking all the possible partitions of
the primes and summing the product of them. Hoping this is faster for large n because
prime factorization only needs to look at sqrt(n) numbers. Potential bottleneck is
the partitioning of the primes, a recursive method which is probably not very fast for
large numbers of primes. Find solution for 10 000 in under 2 sec, 100 000 in under 30 sec.
"""
from numpy import prod
from itertools import groupby

def partitions(arr):
    """Return a list of all the partitions of arr"""
    if len(arr) == 1:
        return [arr]
    without = partitions(arr[:-1])
    incl = [part + [arr[-1]] for part in without]
    return without + incl + [[arr[-1]]]

def prodComplex(listoflists):
    return [prod(arr) for arr in listoflists]

def primes(n):
    primefac = []
    d = 2
    while d*d <= n:
        while n % d == 0:
            primefac.append(d)
            n /= d
        d += 1
    if n > 1:
        primefac.append(n)
    return primefac

def unduplicate(listoflists):
    listoflists.sort()
    return list(k for k, _ in groupby(listoflists))

def d(n):
    if n <= 1:
        return 0
    primefac = primes(n)
    primeparts = unduplicate(partitions(primefac))
    primeprod = prodComplex(primeparts)
    return sum(primeprod) - n + 1


s = 0
seen = set()
num = 0
while num < 10000:
    num += 1
    if num in seen:
        continue

    amicable = d(num)
    if d(amicable) == num and num != amicable:
        print "Found pair:", num, amicable
        seen.add(num)
        seen.add(amicable)
        s += amicable + num
print 'sum of amicable numbers =', s
