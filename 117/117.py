"""
Using a combination of black square tiles and oblong tiles chosen from: red
tiles measuring two units, green tiles measuring three units, and blue tiles
measuring four units, it is possible to tile a row measuring five units in
length in exactly fifteen different ways.

How many ways can a row measuring fifty units in length be tiled?

NOTE: This is related to Problem 116.


Solution comment: Again, very fast, ~1.5 ms. Very similar to the previous problems.
Only addition compared to 114 is that block sizes are given ahead of time, which means
that the blocks suggested in the inner loop sometimes are to big. At this point we simply break.
Also, the trivial solution is allowed again, so we don't subtract 1 from the final answer.
"""

from time import time
from functools import lru_cache
from itertools import count

@lru_cache(maxsize=None)
def ways(N, blocks):
    w = 1
    smallest_block = blocks[0]
    if N >= smallest_block:
        for offset in range(N - smallest_block + 1):
            n = N - offset
            for b in blocks:
                if n - b < 0:
                    break
                w += ways(n - b, blocks)
    return w

if __name__ == "__main__":
    t0 = time()

    print('Answer:', ways(50, (2, 3, 4)))

    print('Execution time: {:.3f} ms'.format((time() - t0) * 1e3))
