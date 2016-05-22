# coding=utf-8
"""
An irrational decimal fraction is created by concatenating the positive integers:

0.123456789101112131415161718192021...

It can be seen that the 12th digit of the fractional part is 1.

If dn represents the nth digit of the fractional part, find the value of the following expression.

d1 × d10 × d100 × d1000 × d10000 × d100000 × d1000000

Solution comment:
Just brute force.
"""
from numpy import prod
upper = int(1e6)
s = ''.join((str(n) for n in xrange(1, upper + 1)))
result = prod([int(s[10**(i)-1]) for i in xrange(6+1)])
print result
