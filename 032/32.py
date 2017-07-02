# coding=utf-8
"""
We shall say that an n-digit number is pandigital if it makes use of all the digits 1 to n exactly once; for example, the 5-digit number, 15234, is 1 through 5 pandigital.

The product 7254 is unusual, as the identity, 39 × 186 = 7254, containing multiplicand, multiplier, and product is 1 through 9 pandigital.

Find the sum of all products whose multiplicand/multiplier/product identity can be written as a 1 through 9 pandigital.

HINT: Some products can be obtained in more than one way so be sure to only include it once in your sum.

Solution comment:
Assume a < b < c, just so that we don't include both a x b and b x a.
Then, if a has n digits, there are 9-n remaining. b can at most have
an equal number of digits to c, so b has (9-n)//2 digits.

So for each n, for each 3-length permutation of digits given to a,
b is the (9-n)//2-length permutation of the remaining digits.
Then, if c cointains no repeted numbers, and no digit already
used in a and b, the product is pandigital.
"""
from itertools import permutations as perm

def perms(arr, n, start=1):
    """Return i-length permutations of iter for i in range(1, n)"""
    a = []
    for i in range(start, n):
        a += list(perm(arr, i))
    return a

digits = '123456789'

a_all = perms(digits, 4)

pandigital = []
for n in xrange(1, 4):
    a_all = list(perm(digits, n))
    for a in a_all:
        a = ''.join(a)
        dig = ''.join([char for char in digits if char not in a])
        b_all = perm(dig, (9-n)//2)
        for b in b_all:
            b = ''.join(b)
            if int(b) < int(a):
                continue
            c = int(a) * int(b)
            used_dig = {char for char in digits if char in (a+b)} | {'0'}
            for char in str(c):
                if char in used_dig:
                    break
                else:
                    used_dig.add(char)
            else:
                pandigital.append((a, b, c))

sum_of_products = sum({elm[2] for elm in pandigital})
print sum_of_products
print pandigital
