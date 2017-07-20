# Based on https://math.stackexchange.com/a/89661

from projecteuler.prime import primes_up_to

primes = primes_up_to(100)
prime_set = set(primes)
is_prime = lambda p: p in prime_set

def memoize(f):
    seen = dict()
    def g(*args, **kwargs):
        if args not in seen:
            seen[args] = f(*args, **kwargs)
        return seen[args]
    return g

@memoize
def prime_divisor_sum(n):
    s = 0
    for p in primes:
        if p > n: break
        if n % p == 0: s += p
    return s

@memoize
def prime_partition_count(n):
    if n <= 1: return 0
    s = prime_divisor_sum(n)
    for j in range(1, n):
        s += prime_divisor_sum(j) * prime_partition_count(n-j)
    return s // n

n = 1
while True:
    if prime_partition_count(n) > 5000:
        print(n, prime_partition_count(n))
        break
    n += 1


