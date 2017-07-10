"""
Triangle, square, pentagonal, hexagonal, heptagonal, and octagonal numbers
are all figurate (polygonal) numbers and are generated by the following
formulae:

Triangle         P3,n=n(n+1)/2         1, 3, 6, 10, 15, ...
Square         P4,n=n2         1, 4, 9, 16, 25, ...
Pentagonal         P5,n=n(3n−1)/2         1, 5, 12, 22, 35, ...
Hexagonal         P6,n=n(2n−1)         1, 6, 15, 28, 45, ...
Heptagonal         P7,n=n(5n−3)/2         1, 7, 18, 34, 55, ...
Octagonal         P8,n=n(3n−2)         1, 8, 21, 40, 65, ...

The ordered set of three 4-digit numbers: 8128, 2882, 8281, has three
interesting properties.

The set is cyclic, in that the last two digits of each number is the first two
digits of the next number (including the last number with the first).  Each
polygonal type: triangle (P3,127=8128), square (P4,91=8281), and pentagonal
(P5,44=2882), is represented by a different number in the set.  This is the
only set of 4-digit numbers with this property.  Find the sum of the only
ordered set of six cyclic 4-digit numbers for which each polygonal type:
triangle, square, pentagonal, hexagonal, heptagonal, and octagonal, is
represented by a different number in the set.
"""

def cyclic(a, b):
    return a % 100 == b // 100

def four_digit_list(f):
    n = 1
    while f(n) < 1000:
        n += 1
    s = []
    while f(n) < 10000:
        s.append(f(n))
        n += 1
    return s

def rec(seq, sets):
    if len(sets) == 0 and cyclic(seq[-1], seq[0]):
        print(seq, sum(seq))
    for next_set in sets:
        sets_copy = sets.copy()
        sets_copy.remove(next_set)
        for n in next_set:
            if cyclic(seq[-1], n):
                rec(seq + [n], sets_copy)

triangle   = four_digit_list(lambda n: (n*(n+1))//2)
square     = four_digit_list(lambda n: n*n)
pentagonal = four_digit_list(lambda n: n*(3*n-1)//2)
hexagonal  = four_digit_list(lambda n: n*(2*n-1))
heptagonal = four_digit_list(lambda n: n*(5*n-3)//2)
octagonal  = four_digit_list(lambda n: n*(3*n-2))
sets = [square, pentagonal, hexagonal, heptagonal, octagonal]

for tri in triangle:
    rec([tri], sets)
