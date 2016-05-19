"""
A palindromic number reads the same both ways. The largest palindrome made from the product of two 2-digit numbers is 9009 = 91 x 99.

Find the largest palindrome made from the product of two 3-digit numbers.
"""

def largest_palindrome(f, t):
    return max([a*b for a in range(f, t) for b in range(f, t)
                if str(a*b) == str(a*b)[::-1]])

print largest_palindrome(100, 1000)
