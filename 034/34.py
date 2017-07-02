# coding=utf-8
"""
145 is a curious number, as 1! + 4! + 5! = 1 + 24 + 120 = 145.

Find the sum of all numbers which are equal to the sum of the factorial of their digits.

Note: as 1! = 1 and 2! = 2 are not sums they are not included.

Solution comment:
Upper limit to possible matches:
When diff of adding a new digit is always larger than adding the
corresponding factorial.

Largest case: all 9's

Diff of adding one more 9 to n 9's: (10*n+9) - n = 9(n+1)
Diff in factorial sum: 9! = 362880

Upper limit when 9(n+1) > 9! -> n < 1e6 is a definite upper limit.
Possible to brute force.
"""
import math

# precompute factorials (not very important for low factorials, but still better)
fac = { n: math.factorial(n) for n in xrange(10) }

s = 0
n = 999999

for i in xrange(3, n+1):
    digfac = sum((fac[int(d)] for d in str(i)))
    if digfac == i:
        print i
        s += i

print s
