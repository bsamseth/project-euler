# coding=utf-8
"""
The series, 1^1 + 2^2 + 3^3 + ... + 1010 = 10405071317.

Find the last ten digits of the series, 1^1 + 2^2 + 3^3 + ... + 1000^1000.

Solution comment:
Arbirary precision integers for the win.
"""

print sum(i**i for i in xrange(1, 1000+1)) % int(1e10)


# in case of non-arbitrary precision, keep only
# the trailing 10 digits. This means doing the exponentiation
# manualy, holding the total number of digits at a low number.
s = 0
modulo = int(1e10)
for i in xrange(1, 1001):
    tmp = i  # tmp will be the trailing digits of the i**i
    for j in xrange(1, i):
        tmp *= i
        if tmp >= modulo / i:
            tmp %= modulo

    s = (s + tmp) % modulo
print s
