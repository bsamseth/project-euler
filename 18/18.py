"""
By starting at the top of the triangle below and moving to adjacent numbers on the row below, the maximum total from top to bottom is 23.

          That is,  +  +  +  = 23.

Find the maximum total from top to bottom of the triangle below:
"""
inputdata = """
75
95 64
17 47 82
18 35 87 10
20 04 82 47 65
19 01 23 75 03 34
88 02 77 73 07 63 67
99 65 04 28 06 16 70 92
41 41 26 56 83 40 80 70 33
41 48 72 33 47 32 37 16 94 29
53 71 44 65 25 43 91 52 97 51 14
70 11 33 28 77 73 17 78 39 68 17 57
91 71 52 38 17 14 91 43 58 50 27 29 48
63 66 04 68 89 53 67 30 73 16 69 87 40 31
04 62 98 27 23 09 70 98 73 93 38 53 60 04 23
"""

lines = inputdata.splitlines()[1:]
arr = [[int(word) for word in line.split()] for line in lines]
print arr
# simple solution
for i in range(len(arr)-2, -1, -1):
    for j in range(0, i+1):
        arr[i][j] += max(arr[i+1][j], arr[i+1][j+1])
print arr[0][0]


# Below doesn't work, becomes complicated if it should be
# tried to be fixed....
#
# attempt with Djikstras shortest path variant
# Seems to work on simple cases that I can work out by hand. Finds a
# solution that is 10 less than the correct solution, unknown why

class Node:
    """A node is an entry in the triangle tree.
        The graph is a 2D array"""
    def __init__(self, vertex, value, graph):
        self.vertex, self.value, self.graph = vertex, value, graph
        self.dist = 0
        self.prev = None
        self.next = None

    def neighbors(self):
        x, y = self.vertex
        neighbor = []
        if x < len(self.graph.array) - 1:
            neighbor.append((x+1, y))
            neighbor.append((x+1, y+1))
        neighbor = [self.graph.nodes[vertex] for vertex in neighbor]
        return neighbor

    def __str__(self):
        x, y = self.vertex
        return "(%d, %d): dist = %d" % (x, y, self.dist)

    def setPrev(self, prevNode):
        self.prev = prevNode
        prevNode.next = self

    def addToDistAndPropagate(self, addon):
        self.dist += addon
        for v in self.neighbors():
            if v.vertex not in self.graph.Q:
                v.addToDistAndPropagate(addon)

    def getdist(self):
        total = self.value
        n = self.prev
        while n is not None:
            total += n.value
            n = n.prev
        return total

class Graph:
    """The graph represents the whole triangle"""
    def __init__(self, array):
        self.array = array
        self.Q = {}
        for i, row in enumerate(array):  # Initialization
            for j, v in enumerate(row):
                n = Node((i, j), v, self)
                self.Q[n.vertex] = n
        self.nodes = self.Q.copy()

    def maxNode(self, nodeDict):
        mn = nodeDict.itervalues().next()
        for node in nodeDict.values():
            if node.dist > mn.dist:
                mn = node
        return mn

    def __str__(self):
        s = ""
        for node in graph.nodes.values():
            s += str(node) + "\n"
        return s[:-1]

def Dijkstra(arr):
    graph = Graph(arr)  # Initialization
    graph.Q[(0, 0)].dist = graph.Q[(0, 0)].value  # dist from source to source

    while graph.Q:  # while not empty
        u = graph.maxNode(graph.Q)

        for v in u.neighbors():
            alt = u.getdist() + v.value

            if alt > v.getdist():
                # v.addToDistAndPropagate(alt - v.dist)
                v.setPrev(u)
        graph.Q.pop(u.vertex)
    return graph


# works for all of these
arr = [[10],
       [8, 9],
       [7, 6, 5],
       [1, 2, 3, 4]]

arr = [[5],
       [1, 4],
       [2, 1, 1],
       [5, 3, 1, 1]]

arr = [[3],
       [7, 4],
       [2, 4, 6],
       [8, 5, 9, 3]]

arr = [[1],
       [1, 1],
       [1, 1, 1],
       [1, 1, 1, 1]]
#
# get 10 short for the given triangle
arr = [[int(word) for word in line.split()] for line in lines]

# solver
graph = Dijkstra(arr)
print graph

u = graph.maxNode(graph.nodes)
road = []
while u.prev is not None:
    road.append(u)
    u = u.prev
road.append(u)
road = road[::-1]

print "Road:"
total = sum([v.value for v in road])
for node in road:
    print node

u = graph.maxNode(graph.nodes)
print "Max final node:", total
