# coding=utf-8
"""
It can be seen that the number, 125874, and its double, 251748, contain exactly the same digits, but in a different order.

Find the smallest positive integer, x, such that 2x, 3x, 4x, 5x, and 6x, contain the same digits.
"""
from itertools import count

def digs(n):
    return {dig for dig in str(n)}

for x in count(1):
    d = digs(x)
    for mul in xrange(2, 7):
        if digs(x*mul) ^ d:
            break
    else:
        print 'x = {0}'.format(x)
        break
