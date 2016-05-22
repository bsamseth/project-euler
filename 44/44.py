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
from gmpy2 import is_square, sqrt

def pentagonal(n):
    return n*(3*n-1)/2

def ispentagonal(P):
    """Returns true if P is pentagonal.
    ABC-formula on P(n) gives
        n = (sqrt(1+24P)+1)/6
    If P is pentagonal, n is an int.
        1. sqrt must return a integer
        2. must be divisble by 6
    """
    sq = 1 + 24*P
    return is_square(sq) and int(sqrt(sq)+1) % 6 == 0


upper = 10000  # upper n in P(n)

pentagonals = [ pentagonal(i) for i in xrange(1, upper+1) ]
pentagonals_set = set(pentagonals)

for i in xrange(1, upper):
    Pi = pentagonal(i)
    for j in xrange(i, upper+1):
        Pj = pentagonal(j)
        if ispentagonal(Pj-Pi) and ispentagonal(Pi+Pj):
            print i, j, Pi, Pj, Pj-Pi
