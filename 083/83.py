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

Solution comment: Dijkstra's algorithm, implemented in a very non-optimized fashion. Takes about ~4s...
"""

import numpy as np
from itertools import chain


class Cell(object):
    def __init__(self, index):
        self.neighbors = []
        self.index = index
        self.value = A[index]
        self.dist = float('inf')
        self.prev = None

    def __repr__(self):
        return 'Cell({}, value={}, dist={})'.format(self.index, self.value, self.dist)

A = np.array([  [131, 201, 630, 537, 805],
             [673,  96, 803, 699, 732],
             [234, 342, 746, 497, 524],
             [103, 965, 422, 121,  37],
             [18, 150, 111, 956, 331]  ]).T
A = np.loadtxt('p082_matrix.txt', delimiter=',')

cells = [[Cell((i,j)) for j in range(A.shape[1])] for i in range(A.shape[0])]


for i in range(A.shape[0]):
    for j in range(A.shape[1]):
        if i > 0:
            cells[i][j].neighbors.append(cells[i-1][j])
        if j > 0:
            cells[i][j].neighbors.append(cells[i][j-1])
        if i < A.shape[0] - 1:
            cells[i][j].neighbors.append(cells[i+1][j])
        if j < A.shape[1] - 1:
            cells[i][j].neighbors.append(cells[i][j+1])


def min_dist_vertex(Q):
    min_vertex = Cell((0,0))
    for u in Q:
        if u.dist < min_vertex.dist:
            min_vertex = u
    Q.remove(min_vertex)
    return min_vertex

def one_to_all(cells, source):
    Q = list(chain.from_iterable(cells))

    for v in Q:
        v.dist = float('inf')
        v.prev = None

    source.dist = source.value

    while Q:
        u = min_dist_vertex(Q)
        # print(u)
        for n in u.neighbors:
            # print('\tUpdating {}'.format(n))
            if n in Q:
                alt = u.dist + n.value
                if alt < n.dist:
                    n.dist = alt
                    n.prev = u
one_to_all(cells, cells[0][0])
print(cells[-1][-1].dist)
