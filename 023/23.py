"""
A perfect number is a number for which the sum of its proper divisors is exactly equal to the number. For example, the sum of the proper divisors of 28 would be 1 + 2 + 4 + 7 + 14 = 28, which means that 28 is a perfect number.

A number n is called deficient if the sum of its proper divisors is less than n and it is called abundant if this sum exceeds n.

As 12 is the smallest abundant number, 1 + 2 + 3 + 4 + 6 = 16, the smallest number that can be written as the sum of two abundant numbers is 24. By mathematical analysis, it can be shown that all integers greater than 28123 can be written as the sum of two abundant numbers. However, this upper limit cannot be reduced any further by analysis even though it is known that the greatest number that cannot be expressed as the sum of two abundant numbers is less than this limit.

Find the sum of all the positive integers which cannot be written as the sum of two abundant numbers.

Solution comment:
If b(n) = d(n) + n
    b(n) = b(p1 * p2 * .... * pn) = b(p1) * b(p2) * ... * b(pn)
with
    b(p**a) = sum( p**i for i in range(0, a+1)  )
"""
from numpy import prod

def primes_dict(n):
    primfac = {}
    d = 2
    while d*d <= n:
        while n % d == 0:
            if d in primfac:
                primfac[d] += 1
            else:
                primfac[d] = 1
            n /= d
        d += 1
    if n > 1:
        primfac[n] = 1
    return primfac

def d(n):
    if n <= 1:
        return 0
    primefac = primes_dict(n)
    per_prime = prod([sum(( p**i for i in xrange(primefac[p]+1))) for p in primefac ])
    return per_prime - n


# find abundant numbers less than 28123
abundant = [n for n in xrange(28123) if d(n) > n]

# make a set for faster 'in' testing
# this is absolutely necessary
# as list lookup is O(n),
# compared to set lookup which is O(1)
abundant_set = set(abundant)


# store all numbers that is not the sum of two abundants
# use that if n = a1 + a2, then a2 = n - a1
non_sum_of_abundant = []
for n in xrange(1, 28124):
    is_sum_of_abundant = False
    for a in abundant:
        if n - a in abundant_set:
            is_sum_of_abundant = True
            break
        elif a >= n:
            break
    if not is_sum_of_abundant:
        non_sum_of_abundant.append(n)

print 'Sum of all intergers that cannot be written as the sum of two abundant numbers:',
print sum(non_sum_of_abundant)
