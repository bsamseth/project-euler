"""
Starting with the number 1 and moving to the right in a clockwise direction a 5 by 5 spiral is formed as follows:

21 22 23 24 25
20  7  8  9 10
19  6  1  2 11
18  5  4  3 12
17 16 15 14 13

It can be verified that the sum of the numbers on the diagonals is 101.

What is the sum of the numbers on the diagonals in a 1001 by 1001 spiral formed in the same way?

Solution comment:
The inclueded numbers are increasing by 2 four times, then increasing by
4 four times, then by 6 four times... This is done (dim-1)/2 times. For dim=5
above, this is done 2 times.
"""

n = 1
s = n
addon = 0
for j in range((1001-1)/2):
    addon += 2
    for i in range(4):
        n += addon
        s += n
print s
