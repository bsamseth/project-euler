"""
2520 is the smallest number that can be divided by each of the numbers from 1 to 10 without any remainder.

What is the smallest positive number that is evenly divisible by all of the numbers from 1 to 20?

Solution comments:
Answer is the product of all primes in all the divisors, with each
prime beeing included only as many times as the maximum multiplisity of that
prime in the divisors.
"""

def primes(n):
    """Return dict with primes and multiplisities.
            primes(20) -> {2:2, 5:1}
    """
    primfac = {}
    d = 2
    while d*d <= n:
        primfac[d] = 0
        while (n % d) == 0:
            primfac[d] += 1
            n //= d
        d += 1
    if n > 1:
        primfac[n] = 1
    return primfac

def smallest_commondivisor_for_less_than(n):
    s = primes(n)
    x = n - 1
    while x > 1:
        q = primes(x)
        for key in q:
            if key in s:
                s[key] = max(s[key], q[key])
            else:
                s[key] = q[key]
        x -= 1
    res = 1
    for key in s:
        res *= key**s[key]
    return res

print smallest_commondivisor_for_less_than(20)
