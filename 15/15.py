"""
Starting in the top left corner of a 2x2 grid, and only being able to move to the right and down, there are exactly 6 routes to the bottom right corner.

How many such routes are there through a 20x20 grid?
"""
import numpy as np
from math import factorial as fac

# combinatorics
print fac(2 * 20) / (fac(20) * fac(20))

# or computational
size = 20 + 1
grid = np.ones((size, size), dtype=int)

for upper in range(2, 2*size - 1):
    for i in range(1, min(upper, size)):
        for j in range(1, min(upper, size)):
            if i + j == upper:
                grid[i, j] = grid[i-1, j] + grid[i, j-1]

print grid[-1, -1]
