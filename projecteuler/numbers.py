def pentagonal(n):
    """Returns the n-th pentagonal number"""
    return n*(3*n-1)/2

def ispentagonal(P):
    """Returns true if P is pentagonal.
    ABC-formula on P(n) gives
        n = (sqrt(1+24P)+1)/6
    If P is pentagonal, n is an int.
        1. sqrt must return a integer
        2. must be divisble by 6
    """
    from gmpy2 import is_square, sqrt
    sq = 1 + 24*P
    return is_square(sq) and int(sqrt(sq)+1) % 6 == 0

def istriangular(t):
    """Returns true if t is triangular.
    See ispentagonal for analog explenation"""
    from gmpy2 import is_square, sqrt
    sq = 1 + 8*t
    return is_square(sq) and int(sqrt(sq)-1) % 2 == 0

def triangular(n):
    """Gives the n-th triangle number."""
    return n*(n+1)/2

def palindrome(s):
    """Returns true if string s is a palindrome"""
    l = len(s)
    even = int(l % 2 == 0)
    return s[:l//2] == s[-1:l//2-even:-1]
