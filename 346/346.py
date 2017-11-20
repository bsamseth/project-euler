"""
The number 7 is special, because 7 is 111 written in base 2, and 11 written
in base 6 (i.e. 710 = 116 = 1112). In other words, 7 is a repunit in at least
two bases b > 1.

We shall call a positive integer with this property a strong repunit. It can be
verified that there are 8 strong repunits below 50: {1,7,13,15,21,31,40,43}.
Furthermore, the sum of all strong repunits below 1000 equals 15864.

Find the sum of all strong repunits below 1012.


Solution comment:
For a base b, n = b + 1 is as repunit. For n to be a
repunit of tree digits, we must have 1 + b + b^2 < upper.
This gives the maximum base for which we can have a repunit below upper,
excl. the trivial case above. The max_base is then related to sqrt(upper) (see below).

All repunits (below upper) in every base up to this maximum base are generated. If
we produce a repunit larger than max_base + 1 using a base b <= max_base, then this
n will have one other base for which it is a repunit, so we can count this straight away.
Any other n <= max_base must be seen twice in order to be counted.
"""


from math import log, sqrt, ceil
from collections import defaultdict

upper = int(1e12)
seen = defaultdict(int)
max_base = int(0.5 * (sqrt(4 * upper - 3) - 1))
s = 1
for b in range(2, max_base + 1):
    n = 1
    for i in range(ceil(log(upper * (b-1) + 1) / log( b )  - 1) - 1):
        n += b**(i+1)
        if n > max_base + 1:
            s += n
        else:
            seen[n] += 1
            if seen[n] == 2:
                s += n
print(s)
