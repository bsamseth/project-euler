# coding=utf-8
"""
Pentagonal numbers are generated by the formula, Pn=n(3n−1)/2. The first ten pentagonal numbers are:

1, 5, 12, 22, 35, 51, 70, 92, 117, 145, ...

It can be seen that P4 + P7 = 22 + 70 = 92 = P8. However, their difference, 70 − 22 = 48, is not pentagonal.

Find the pair of pentagonal numbers, Pj and Pk, for which their sum and difference are pentagonal and D = |Pk − Pj| is minimised; what is the value of D?

Solution comment:
No brain, just find any solution with n <= 10000. Happens to
include the desired solution, but not smart in any way.
"""
from projecteuler.numbers import pentagonal, ispentagonal

upper = 10000  # upper n in P(n)

pentagonals = [ pentagonal(i) for i in xrange(1, upper+1) ]
pentagonals_set = set(pentagonals)

for i in xrange(1, upper):
    Pi = pentagonal(i)
    for j in xrange(i, upper+1):
        Pj = pentagonal(j)
        if ispentagonal(Pj-Pi) and ispentagonal(Pi+Pj):
            print i, j, Pi, Pj, Pj-Pi
