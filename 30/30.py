"""
Surprisingly there are only three numbers that can be written as the sum of fourth powers of their digits:

1634 = 1^4 + 6^4 + 3^4 + 4^4
8208 = 8^4 + 2^4 + 0^4 + 8^4
9474 = 9^4 + 4^4 + 7^4 + 4^4
As 1 = 1^4 is not a sum it is not included.

The sum of these numbers is 1634 + 8208 + 9474 = 19316.

Find the sum of all the numbers that can be written as the sum of fifth powers of their digits.

Solution comment:
Pure brute force, and guessing on an upper bound. Tested with
one extra order of magnitude, but all of them are
    [4150, 4151, 54748, 92727, 93084, 194979]
"""

sum_of_fifth_power_digits = []

for n in xrange(1000, 1000000):
    if sum([int(digit)**5 for digit in str(n)]) == n:
        sum_of_fifth_power_digits.append(n)
        print sum_of_fifth_power_digits
print sum(sum_of_fifth_power_digits)
