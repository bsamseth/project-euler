"""
The prime module makes available several functions for prime operations.
Included are prime tests, prime lists, and prime factorization
"""

def isprime(n):
    """Returns True if n is prime. O(sqrt(n))"""
    if n < 2:
        return False
    if n == 2 or n == 3:
        return True
    if n % 2 == 0 or n % 3 == 0:
        return False
    i = 5
    w = 2
    while i * i <= n:
        if n % i == 0:
            return False
        i += w
        w = 6 - w
    return True

def primes_up_to(n):
    """Return a numpy.ndarray of all primes <= n.
    Uses Sieve of Eratosthenes, O(n log log n) """
    import numpy as np
    if n < 2:
        return np.zeros(n+1, dtype=bool)

    A = np.ones(n+1, dtype=bool)
    A[0] = A[1] = False
    for i in xrange(2, int(np.sqrt(n))+1):
        if A[i]:
            for j in xrange(i**2, n+1, i):
                A[j] = False
    return np.where(A)[0]

def primes_dict(n):
    """Return a dictionary with the prime factorization of n.
    Format of (key, value) is (prime, multiplicity)"""
    primfac = {}
    d = 2
    while d*d <= n:
        while n % d == 0:
            if d in primfac:
                primfac[d] += 1
            else:
                primfac[d] = 1
            n /= d
        d += 1
    if n > 1:
        primfac[n] = 1
    return primfac

def primes_list(n):
    """Return a dictionary with the prime factorization of n.
    Format of (key, value) is (prime, multiplicity)"""
    primfac = []
    d = 2
    while d*d <= n:
        while n % d == 0:
            primfac.append(d)
            n /= d
        d += 1
    if n > 1:
        primfac.append(n)
    return primfac
