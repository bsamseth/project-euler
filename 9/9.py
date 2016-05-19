"""
A Pythagorean triplet is a set of three natural numbers, a < b < c, for which,

a^2 + b^2 = c^2
For example, 3^2 + 4^2 = 9 + 16 = 25 = 5^2.

There exists exactly one Pythagorean triplet for which a + b + c = 1000.
Find the product abc.
"""

for a in xrange(1, 999):
    for b in xrange(a+1, 999):
        for c in xrange(b+1, 999):
            if a + b + c == 1000 and a**2 + b**2 == c**2:
                print a, b, c, a*b*c
