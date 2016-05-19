"""
By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we can see that the 6th prime is 13.

What is the 10 001st prime number?
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

def nthprime(n):
    prime, nprimes = 2, 1
    potprime = 3
    while nprimes < n:
        if isprime(potprime):
            prime = potprime
            nprimes += 1
        potprime += 2
    return prime

print nthprime(10001)
