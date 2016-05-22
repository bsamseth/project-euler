# coding=utf-8
"""
If p is the perimeter of a right angle triangle with integral length sides, {a,b,c}, there are exactly three solutions for p = 120.

{20,48,52}, {24,45,51}, {30,40,50}

For which value of p ≤ 1000, is the number of solutions maximised?

Solution comment:
Assume a < b, and know b < c. Then a <= p/2, a < b <= (p-a)/2.

Then simply check if c^2 = a^2 + b^2 is possible and makes the
total perimeter equal to p.
"""
from math import sqrt
from gmpy2 import is_square
from numpy import zeros, argmax

p_all = xrange(3, 1000 + 1)
solutions = zeros(len(p_all))

for i, p in enumerate(p_all):
    for a in xrange(1, p//2+1):
        for b in xrange(a+1, (p - a)//2 + 1):
            c2 = a**2 + b**2
            if is_square(c2) and int(sqrt(c2)) + a + b == p:
                solutions[i] += 1

print p_all[argmax(solutions)]
