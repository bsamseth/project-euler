# coding=utf-8
"""
The decimal number, 585 = 1001001001_2 (binary), is palindromic in both bases.

Find the sum of all numbers, less than one million, which are palindromic in base 10 and base 2.

(Please note that the palindromic number, in either base, may not include leading zeros.)

Solution comment:
First thing to note, since we can't have leading zeros, then any palindrome in
base 2 can't end in a 0, so it can't be an even number.

Simple to brute force check the rest
"""

def palindrome(s):
    """Returns true if string s is a palindrome"""
    l = len(s)
    even = int(l % 2 == 0)
    return s[:l//2] == s[-1:l//2-even:-1]

upper = int(1e6)
palindromes = []
for n in xrange(1, upper, 2):
    base_10 = str(n)
    base_2 = str(bin(n))[2:]
    if palindrome(base_10) and palindrome(base_2):
        palindromes.append((base_10, base_2))

print palindromes
print sum([int(elm[0]) for elm in palindromes])
