# coding=utf-8
"""
The number, 1406357289, is a 0 to 9 pandigital number because it is made up of each of the digits 0 to 9 in some order, but it also has a rather interesting sub-string divisibility property.

Let d1 be the 1st digit, d2 be the 2nd digit, and so on. In this way, we note the following:

d2d3d4=406 is divisible by 2
d3d4d5=063 is divisible by 3
d4d5d6=635 is divisible by 5
d5d6d7=357 is divisible by 7
d6d7d8=572 is divisible by 11
d7d8d9=728 is divisible by 13
d8d9d10=289 is divisible by 17
Find the sum of all 0 to 9 pandigital numbers with this property.

Solution comment:
Iterate over all 0-9 pandigitals. First digit must be one of
1-9, rest can be any of the 9 remaining digits.

Then check that each window of 3 digits is divisible by its
corresponding prime.
"""
from itertools import permutations, izip

def slidingWindow(sequence, winSize, step=1):
    """Returns a generator that will iterate through
    the defined chunks of input sequence.  Input sequence
    must be iterable."""
    numOfChunks = ((len(sequence)-winSize)/step)+1
    for i in xrange(0, numOfChunks*step, step):
        yield sequence[i:i+winSize]

digits = set(str(d) for d in xrange(10))
primes = [2, 3, 5, 7, 11, 13, 17]

results = []

for d1 in xrange(1, 10):
    for perm in permutations(digits ^ {str(d1)}, 9):
        n = str(d1) + ''.join(perm)

        for part, p in izip(slidingWindow(n[1:], 3), primes):
            if int(part) % p != 0:
                break
        else:
            print n
            results.append(int(n))

print results, sum(results)
