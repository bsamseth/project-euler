# coding=utf-8
"""
Take the number 192 and multiply it by each of 1, 2, and 3:

192 × 1 = 192
192 × 2 = 384
192 × 3 = 576
By concatenating each product we get the 1 to 9 pandigital, 192384576. We will call 192384576 the concatenated product of 192 and (1,2,3)

The same can be achieved by starting with 9 and multiplying by 1, 2, 3, 4, and 5, giving the pandigital, 918273645, which is the concatenated product of 9 and (1,2,3,4,5).

What is the largest 1 to 9 pandigital 9-digit number that can be formed as the concatenated product of an integer with (1,2, ... , n) where n > 1?

Solution comment:
Starting number can be no larger than 4 digits long beacause we
need to concatenate at least two products.
"""
from itertools import count

upper = int(1e4)

digits = {i for i in xrange(10)}

pandigitals_multiples = []
for n in xrange(2, upper):
    pandigital = ''
    for i in count(1):
        used_dig = {int(d) for d in pandigital} | {0}
        prod = n * i
        digs = {int(d) for d in str(prod)}

        if used_dig == digits:
            # we have used all digits and not hit break
            pandigitals_multiples.append(int(pandigital))
            break

        if len(digs) != len(str(prod)):
            # prod has repeted digits
            break

        if used_dig & digs:
            # new digs already used
            break
        pandigital += str(prod)

print max(pandigitals_multiples)
