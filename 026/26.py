"""
A unit fraction contains 1 in the numerator. The decimal representation of the unit fractions with denominators 2 to 10 are given:

1/2	= 	0.5
1/3	= 	0.(3)
1/4	= 	0.25
1/5	= 	0.2
1/6	= 	0.1(6)
1/7	= 	0.(142857)
1/8	= 	0.125
1/9	= 	0.(1)
1/10	= 	0.1
Where 0.1(6) means 0.166666..., and has a 1-digit recurring cycle. It can be seen that 1/7 has a 6-digit recurring cycle.

Find the value of d < 1000 for which 1/d contains the longest recurring cycle in its decimal fraction part.

Solution comment:
Tried first using the decimal module to get arbitrary precision. Hard part was
determining the length of the recurring part, which for d ~ 1000 took to long.

This solution is basically doing long division by hand.
"""

def recurr_length(d):
    seen = set([0])
    remainder = 1 % d  # == 1
    while remainder not in seen:
        seen.add(remainder)
        remainder = (10*remainder) % d
    return len(seen) - 1

max_d, max_len = 1, 0
for d in xrange(2, 1000):
    new_len = recurr_length(d)
    if new_len > max_len:
        max_d = d
        max_len = new_len

print max_d, max_len
