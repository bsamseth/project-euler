# -*- coding: utf-8 -*-
"""
Euler discovered the remarkable quadratic formula:

n^2 + n + 41

It turns out that the formula will produce 40 primes for the consecutive values n = 0 to 39. However, when n = 40, 402 + 40 + 41 = 40(40 + 1) + 41 is divisible by 41, and certainly when n = 41, 41^2 + 41 + 41 is clearly divisible by 41.

The incredible formula  n^2 − 79n + 1601 was discovered, which produces 80 primes for the consecutive values n = 0 to 79. The product of the coefficients, −79 and 1601, is −126479.

Considering quadratics of the form:

n^2 + an + b, where |a| < 1000 and |b| < 1000

where |n| is the modulus/absolute value of n
e.g. |11| = 11 and |−4| = 4
Find the product of the coefficients, a and b, for the quadratic expression that produces the maximum number of primes for consecutive values of n, starting with n = 0.
"""
import numpy as np
from itertools import count
def primes_up_to(n):
    if n < 2:
        return np.zeros(n+1, dtype=bool)

    A = np.ones(n+1, dtype=bool)
    A[0] = A[1] = False
    for i in xrange(2, int(np.sqrt(n))+1):
        if A[i]:
            for j in xrange(i**2, n+1, i):
                A[j] = False
    return np.where(A)[0]

def isprime(n):
    """Returns True if n is prime."""
    if n < 2:
        return False
    if n == 2 or n == 3:
        return True
    if n % 2 == 0 or n % 3 == 0:
        return False
    i = 5
    w = 2
    while i * i <= n:
        if n % i == 0:
            return False
        i += w
        w = 6 - w
    return True

def prime_length(a, b):
    f = lambda n: n*n + a*n + b
    nprimes = 0
    for n in count():
        if isprime(f(n)):
            nprimes += 1
        else:
            break
    return nprimes

p = primes_up_to(1000)
prime_set = set(p)

best_a, best_b, best_length = 0, 0, 0
for b in p:
    a_set = p - b - 1
    for a in a_set:
        nprimes = prime_length(a, b)
        if nprimes > best_length:
            best_a, best_b, best_length = a, b, nprimes
print best_a, best_b, best_length
print best_a * best_b
