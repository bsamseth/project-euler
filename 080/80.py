"""
It is well known that if the square root of a natural number is not an integer, then it is irrational. The decimal expansion of such square roots is infinite without any repeating pattern at all.

The square root of two is 1.41421356237309504880..., and the digital sum of the first one hundred decimal digits is 475.

For the first one hundred natural numbers, find the total of the digital sums of the first one hundred decimal digits for all the irrational square roots.
"""

from mpmath import mp
mp.dps = 105  # Set precision high enough for 100 decimals.

perfect_squares = { i * i for i in range(11) }
s = 0

for n in range(1, 101):
    if n not in perfect_squares:
        digits = str(mp.sqrt(n))[:101]
        s += sum(int(i) for i in digits if i != '.')
print(s)
