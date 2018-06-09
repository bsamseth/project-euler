/*
The most naive way of computing n15 requires fourteen multiplications:

n × n × ... × n = n15

But using a "binary" method you can compute it in six multiplications:

n × n = n2
n2 × n2 = n4
n4 × n4 = n8
n8 × n4 = n12
n12 × n2 = n14
n14 × n = n15

However it is yet possible to compute it in only five multiplications:

n × n = n2
n2 × n = n3
n3 × n3 = n6
n6 × n6 = n12
n12 × n3 = n15

We shall define m(k) to be the minimum number of multiplications to
compute n^k; for example m(15) = 5.

For 1 ≤ k ≤ 200, find ∑ m(k).


Solution comment: Fast, ~2 ms The idea was to build a tree
of possible exponentiation paths, thereby finding all the ways to reach
a given k, and keeping the shortest. Large optimization was to only expand nodes
where the path length was at least as short as one seen before. Not entirely obvious
that this will include all the best paths, as the available ancestors could be
different. But it works. The search depth limit was set high enough so that
all k's could be reached. Another large speed boost was to not keep track of children
in the nodes (original implementation did this). Yet another speed boost was to use a
simple array to store the best path lengths, instead of using a map.
*/

#include <iostream>
#include "timing.hpp"

struct Node {
    const int power;
    const Node *parent;
};

void expand_node(const Node &node, int depth, int limit);

constexpr int depth_limit = 12;
constexpr int power_limit = 200;
int node_count = 0;
int best[power_limit + 1] = {0};

int main() {
    euler::Timer timer{};

    // Expand the root node (n^1).
    expand_node({1, nullptr}, depth_limit, power_limit);

    // Results now stored in best.
    int m_sum = depth_limit * power_limit;
    for (int i = 0; i <= power_limit; ++i) {
        m_sum -= best[i];
    }

    timer.stop();
    printf("Answer: %d\n", m_sum);
}

void expand_node(const Node &node, int depth, int limit) {
    node_count++;
    if (depth > 0 and best[node.power] <= depth) {
        best[node.power] = depth;
        // Add direct child (square).
        if (2 * node.power <= limit)
            expand_node({2 * node.power, &node}, depth - 1, limit);

        // Combine with any one ancestor, walking up the tree.
        auto ancestor = node.parent;
        while (ancestor != nullptr) {
            if (node.power + ancestor->power <= limit)
                expand_node({node.power + ancestor->power, &node}, depth - 1, limit);
            ancestor = ancestor->parent;
        }
    }
}
