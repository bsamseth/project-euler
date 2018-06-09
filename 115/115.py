"""
NOTE: This is a more difficult version of Problem 114.

A row measuring n units in length has red blocks with a minimum length of m
units placed on it, such that any two red blocks (which are allowed to be
different lengths) are separated by at least one black square.

Let the fill-count function, F(m, n), represent the number of ways that a row
can be filled.

For example, F(3, 29) = 673135 and F(3, 30) = 1089155.

That is, for m = 3, it can be seen that n = 30 is the smallest value for which
the fill-count function first exceeds one million.

In the same way, for m = 10, it can be verified that F(10, 56) = 880711 and
F(10, 57) = 1148904, so n = 57 is the least value for which the fill-count
function first exceeds one million.

For m = 50, find the least value of n for which the fill-count function first
exceeds one million.


Solution comment: Very easy to solve, just porting 114 by subs. all 3's with
m's.  Fast enough, < 100 ms. Optimizing the search space does not really help,
as the caching makes sure that results obtained when running for smaller n
still contribute.  Again, to make this faster we would have to (barring porting
to C++) make it non-recrusive, but this is simple, easy and efficient.
"""

from time import time
from functools import lru_cache
from itertools import count

@lru_cache(maxsize=None)
def ways(N, m):
    w = 1   # The trivial solution is always possible.
    if N >= m:
        for offset in range(N - m + 1):  # Start placing block at each offset.
            n = N - offset               # The remaining units after the offset.
            for b in range(m, n + 1):    # Add the ways after placing a block of size b.
                w += ways(n - b - 1, m)
    return w

if __name__ == "__main__":
    t0 = time()

    limit = int(1e6)
    m = 50
    for n in count(m):
        w = ways(n, m)
        if w > limit:
            print('Answer: F(m = {}, n = {}) = {} > {}'.format(m, n, w, limit))
            break

    print('Execution time: {:.3f} ms'.format((time() - t0) * 1e3))
