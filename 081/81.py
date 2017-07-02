"""
In the 5 by 5 matrix below, the minimal path sum from the top left to the
bottom right, by only moving to the right and down, is indicated in bold red
and is equal to 2427.

 A = np.array([  [131, 201, 630, 537, 805],
                 [673,  96, 803, 699, 732],
                 [234, 342, 746, 497, 524],
                 [103, 965, 422, 121,  37],
                 [18, 150, 111, 956, 331]  ]).T

Find the minimal path sum, in matrix.txt, a 31K text file containing a 80 by 80
matrix, from the top left to the bottom right by only moving right and down.

Solution comment: Solved using dynamic programming. If the shortest path from
your neighbors are known, then a cells shortest path is its own value added to
the minimum of its neighbors. Starting at the end of the path allows us to
build towards having the neighbors of the starting position solved. Iteration
is done diagonally, bottom left to top right.
"""

import numpy as np

def select_min(A, x, y):
    """Add to A[x, y] its minimum neighbor."""
    n, m = A.shape
    if x == n - 1:
        min_val = A[x, y+1]
    elif y == m - 1:
        min_val = A[x+1, y]
    else:
        min_val = min(A[x+1, y], A[x, y+1])
    A[x, y] += min_val


A = np.loadtxt('matrix.txt', dtype=int, delimiter=',')
print(A)
n, m = A.shape

for j in reversed(range(m-1)):
    for k in range(m-j):
        select_min(A, n-k-1, j+k)

for i in reversed(range(n-1)):
    for k in range(m-(n-i-1)):
        select_min(A, i-k, k)

print('Minimum path sum:', A[0,0])
