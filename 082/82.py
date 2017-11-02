"""
The minimal path sum in the 5 by 5 matrix below, by starting in any cell in the
left column and finishing in any cell in the right column, and only moving up,
down, and right, is indicated in red and bold; the sum is equal to 994.

 A = np.array([  [131, 201, 630, 537, 805],
                 [673,  96, 803, 699, 732],
                 [234, 342, 746, 497, 524],
                 [103, 965, 422, 121,  37],
                 [18, 150, 111, 956, 331]  ]).T

Find the minimal path sum, in matrix.txt (right click and "Save Link/Target
As..."), a 31K text file containing a 80 by 80 matrix, from the left column to
the right column.

Solution comment: Solve column by column, each time only considering a (N x 2) matrix.
Best path either straight right, or any number of steps up or down followed by a right step.
If at any point the column sum going up/down exceeds the best known path, we can stop going
up/down.

Time complexity is O(N x N x (N/2 + N/2) = O(N^3) worst case, but
the up/down search will terminate much quicker than (N/2 + N/2) on average. Runs in ~0.23s.
"""

import numpy as np

A = np.loadtxt('p082_matrix.txt', delimiter=',')
B = np.zeros(A.shape[0])  # Buffer for the column being solved.

for j in reversed(range(A.shape[1]-1)):
    for i in range(A.shape[0]):
        c_best = A[i,j] + A[i,j+1]
        # Down search
        col_sum = A[i,j]
        for k in range(i+1, A.shape[0]):
            col_sum += A[k,j]
            if col_sum >= c_best:
                break
            c_best = min(c_best, col_sum + A[k,j+1])

        # Up search
        col_sum = A[i,j]
        for k in reversed(range(i)):
            col_sum += A[k,j]
            if col_sum >= c_best:
                break
            c_best = min(c_best, col_sum + A[k,j+1])

        B[i] = c_best
    A[:,j] = B

print(np.min(A[:,0]))
