"""
The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.

Find the sum of all the primes below two million.
"""
from math import sqrt
def isprime(n):
    if n % 2 == 0 and n != 2:
        return False
    div = 3
    while div <= int(sqrt(n)):
        if n % div == 0:
            return False
        div += 2
    return True

def prime_sum_below(n):
    if n <= 2:
        return 0

    num = 3
    s = 2
    while num < n:
        s += num * int(isprime(num))
        num += 2
    return s

print prime_sum_below(2000000)
