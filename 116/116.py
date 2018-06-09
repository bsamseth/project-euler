"""
A row of five black square tiles is to have a number of its tiles replaced with
coloured oblong tiles chosen from red (length two), green (length three), or
blue (length four).

If red tiles are chosen there are exactly seven ways this can be done. If
green tiles are chosen there are three ways. And if blue tiles are chosen
there are two ways.

Assuming that colours cannot be mixed there are 7 + 3 + 2 = 12 ways of
replacing the black tiles in a row measuring five units in length.

How many different ways can the black tiles in a row measuring fifty units in
length be replaced if colours cannot be mixed and at least one coloured tile
must be used?

NOTE: This is related to Problem 117.


Solution comment: Very fast, ~1 ms. Very similar to 114, only now the blocks
have a fixed size, not a minimum size. This actually only makes things simpler,
and faster. One important note is that at least one colour must be used, so the
trivial solution should not be counted for the total length. It still needs to
be counted in the subproblems though for the algo. to work. So this extra 1 is
subtracted afterwards. Then we simply do the whole thing for the different
blocks and sum it up.
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
            w += ways(n - m, m)          # Add number of ways to fill the rest.
    return w

def actual_ways(N):
    return sum(ways(N, m) - 1 for m in [2, 3, 4])

if __name__ == "__main__":
    t0 = time()

    print('Answer:', actual_ways(50))

    print('Execution time: {:.3f} ms'.format((time() - t0) * 1e3))
