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


Solution comment: Slow implementation, about 150ms. The idea was to build a tree
of possible exponentiation paths, thereby finding all the ways to reach
a given k, and keeping the shortest. Large optimization was to only expand nodes
where the path length was at least as short as one seen before. Not entirely obvious
that this will include all the best paths, as the available ancestors could be
different. But it works. The search depth limit was set high enough so that
all k's could be reached.
*/

#include <iostream>
#include <vector>
#include <map>

#include "prettyprint.hpp"
#include "timing.hpp"

int node_count = 0;
std::map<int, int> best;

struct Node {
    const int power;
    std::vector<Node> children;
    Node *parent;

    Node(int k, Node *p, int depth, int limit) : power(k), parent(p) {
        node_count++;
        if (depth > 0 and best[power] <= depth) {
            best[power] = depth;
            // Add direct child (square).
            if (2 * power <= limit)
                children.emplace_back(2 * power, this, depth - 1, limit);

            // Combine with any one ancestor, walking up the tree.
            Node *ancestor = parent;
            while (ancestor != nullptr) {
                if (power + ancestor->power <= limit)
                    children.emplace_back(power + ancestor->power, this, depth - 1, limit);
                ancestor = ancestor->parent;
            }
        }
    }
};

int main() {
    euler::Timer timer{};

    constexpr int depth_limit = 12;
    constexpr int power_limit = 200;

    // Expand the root node (n^1).
    Node root(1, nullptr, depth_limit, power_limit);

    // Results now stored in best.
    int m_sum = 0;
    for (const auto &[power, depth] : best) {
        m_sum += depth_limit - depth;
    }

    timer.stop();
    printf("Answer: %d\n", m_sum);
    printf("Map size: %lu\n", best.size());
}

