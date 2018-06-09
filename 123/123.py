"""
Let pn be the nth prime: 2, 3, 5, 7, 11, ..., and let r be the remainder when
(pn−1)n + (pn+1)n is divided by pn2.

For example, when n = 3, p3 = 5, and 43 + 63 = 280 ≡ 5 mod 25.

The least value of n for which the remainder first exceeds 109 is 7037.

Find the least value of n for which the remainder first exceeds 1010.


Solution comment: Simple to brute force, takes about ~200 ms.
Had troubles with this in C++ due to overflow, even with uint64_t. So
Python to the rescue.
"""

from time import time
from projecteuler.prime import prime_stream

t0 = time()

for n, p in enumerate(prime_stream(), start=1):
    r = (pow(p+1, n, p*p) + pow(p-1, n, p*p)) % (p*p)
    if r > 1e10:
        print('Answer:', n)
        break

print('Execution time: {:.3f} ms'.format((time() - t0) * 1e3))
