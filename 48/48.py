# coding=utf-8
"""
The series, 1^1 + 2^2 + 3^3 + ... + 1010 = 10405071317.

Find the last ten digits of the series, 1^1 + 2^2 + 3^3 + ... + 1000^1000.

Solution comment:
Arbirary precision integers for the win.
"""

print sum(i**i for i in xrange(1, 1000+1)) % int(1e10)
