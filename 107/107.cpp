/*
 The following undirected network consists of seven vertices and twelve edges
 with a total weight of 243.

The same network can be represented by the matrix below.

    A	B	C	D	E	F	G
A	-	16	12	21	-	-	-
B	16	-	-	17	20	-	-
C	12	-	-	28	-	31	-
D	21	17	28	-	18	19	23
E	-	20	-	18	-	-	11
F	-	-	31	19	-	-	27
G	-	-	-	23	11	27	-

However, it is possible to optimise the network by removing some edges and
still ensure that all points on the network remain connected. The network which
achieves the maximum saving is shown below. It has a weight of 93, representing
a saving of 243 − 93 = 150 from the original network.

Using network.txt (right click and 'Save Link/Target As...'), a 6K text file
containing a network with forty vertices, and given in matrix form, find the
maximum saving which can be achieved by removing redundant edges whilst
ensuring that the network remains connected.

Solution comment: Problem is just to find a minimum spanning tree. Implemented
                  is a version of Kruskal's algorithm. Takes about ~2 ms, most
                  of which is file reading.
 */


#include <vector>
#include <queue>
#include <unordered_set>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

/*
 * Representation of an edge in the graph.
 */
struct Edge {
    int u, v, w;
};
/*
 * Comparison operator, for use with a priority queue.
 */
bool operator> (const Edge &lhs, const Edge &rhs) {
    return lhs.w > rhs.w;
}

/*
 * Read matrix from the file.
 */
void read_matrix(std::string filename, std::vector<std::vector<int>> &matrix) {
    std::ifstream input(filename);
    if (!input.is_open()) {
        throw 1; // problem.
    }
    std::string line;
    while (std::getline(input, line)) {
        std::stringstream linestream(line);
        std::string value;
        std::vector<int> row;
        while (std::getline(linestream, value, ',')) {
            row.push_back(value == "-" ? 0 : std::stoi(value));
        }
        matrix.push_back(row);
    }
}

/*
 * Fill a queue with all unique edges denoted by matrix.
 * @return The total weight of all the edges.
 */
template<typename Matrix, typename Queue>
long get_edges(const Matrix &matrix, Queue &edges) {
    long total_weight = 0;
    for (int u = 0; u < (int) matrix.size(); u++) {
        const auto &row = matrix[u];
        for (int v = u + 1; v < (int) row.size(); v++) {
            if (row[v]) {
                edges.push({u, v, row[v]});
                total_weight += row[v];
            }
        }
    }
    return total_weight;
};

int main() {

    auto start = std::chrono::high_resolution_clock::now();

    // Load matrix.
    std::vector<std::vector<int>> matrix;
    read_matrix("../../107/p107_network.txt", matrix);

    // Load edges.
    std::priority_queue<Edge, std::vector<Edge>, std::greater<>> edges;
    long total_weight = get_edges(matrix, edges);

    // Start with a forrest where each tree is one vertex.
    std::vector<std::unordered_set<int>> msf;
    for (int v = 0; v < (int) matrix.size(); v++) {
        msf.push_back({v});
    }

    // Loop while the msf is not a single tree, and there are more edges.
    long weight = 0;
    while (msf.size() > 1 and not edges.empty()) {
        const Edge edge = edges.top(); edges.pop();

        // Locate which trees edge.u and edge.v belong to.
        int u_tree, v_tree;
        for (int i = 0; i < (int) msf.size(); i++) {
            if (msf[i].count(edge.u))
                u_tree = i;
            if (msf[i].count(edge.v))
                v_tree = i;
        }

        // If the edge connects two different trees, we keep it.
        // This means joining the two trees: Copy v_tree into u_tree
        // and delete v_tree.
        if (u_tree != v_tree) {
            for (int v : msf[v_tree]) {
                msf[u_tree].insert(v);
            }
            msf.erase(msf.begin() + v_tree);
            weight += edge.w;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::nanoseconds> (end - start).count() / (double) 1e6;
    printf("Answer: %ld\n", total_weight - weight);
    printf("Found in time: %g ms\n", time);
}
