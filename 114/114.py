"""
A row measuring seven units in length has red blocks with a minimum length of
three units placed on it, such that any two red blocks (which are allowed to be
different lengths) are separated by at least one black square. There are
exactly seventeen ways of doing this.

How many ways can a row measuring fifty units in length be filled?

NOTE: Although the example above does not lend itself to the possibility, in
general it is permitted to mix block sizes. For example, on a row measuring
eight units in length you could use red (3), black (1), and red (4).


Solution comment: Fast for Python, ~4 ms. This somehow worked on first
try.  Idea was to describe the number of ways to place the blocks with N units,
and use this to build larger solutions. A baseline fact is that there is only
one way to do it if N < 3 (i.e. the trivial solution). Then we can place a
block of ever increasing size (until no more room), and then add the number of
ways to place blocks on the remaining units. We can place the block either at
the start, or at some offset. Trying all blocksizes and all offsets we generate
the solution.

The memoization is essential for building the solution recursively like this.
Could be translated to DP with a simple array, but that would take some more
accurate indexing. The simplicity of this approach is the most appealing part.
And somehow I got the ±1 parts right on the first go.
"""

from time import time
from functools import lru_cache

@lru_cache()
def ways(N):
    w = 1   # The trivial solution is always possible.
    if N >= 3:
        for offset in range(N - 3 + 1):  # Start placing block at each offset.
            n = N - offset               # The remaining units after the offset.
            for b in range(3, n + 1):    # Add the ways after placing a block of size b.
                w += ways(n - b - 1)
    return w

if __name__ == "__main__":
    t0 = time()
    print('Answer: {}\nExecution time: {:.3f} ms'.format(ways(50), (time() - t0) * 1e3))
