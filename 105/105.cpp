/*
Let S(A) represent the sum of elements in set A of size n. We shall call it a
special sum set if for any two non-empty disjoint subsets, B and C, the
following properties are true:

    1. S(B) ≠ S(C); that is, sums of subsets cannot be equal.
    2. If B contains more elements than C then S(B) > S(C).

For example, {81, 88, 75, 42, 87, 84, 86, 65} is not a special sum set because
65 + 87 + 88 = 75 + 81 + 84, whereas {157, 150, 164, 119, 79, 159, 161, 139,
158} satisfies both rules for all possible subset pair combinations and S(A) =
1286.

Using sets.txt (right click and "Save Link/Target As..."), a 4K text file with
one-hundred sets containing seven to twelve elements (the two examples given
above are the first two sets in the file), identify all the special sum sets,
A1, A2, ..., Ak, and find the value of S(A1) + S(A2) + ... + S(Ak).

NOTE: This problem is related to Problem 103 and Problem 106.

Solution comment: ~15 ms. Purely reuse of code from 103. Only thing of note
                  was to remember to sort the set before testing, as
                  the code from 103 assumed to set to be in ascending
                  order for some efficient checks.
 */
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cmath>
#include <chrono>
#include <vector>
#include <numeric>
#include <algorithm>

/*
 * Return a vector of sums, where sum[i] is the sum of the set
 * containing A[k] where k is the index of all the set bits in i.
 *
 * Example:
 *   A = {1, 2, 3}
 *   sum[3] = sum[0b011] = A[0] + A[1]
 *   sum[4] = sum[0b100] = A[3]
 */
template<typename Container>
auto all_subset_sums(const Container &A) {
    const auto n = std::distance(A.begin(), A.end());
    std::vector<int> subset_sums((std::size_t) std::pow(2, n));
    for (std::size_t i = 1; i < subset_sums.size(); i++) {
        auto selector = i;
        for (int element : A) {
            if (selector & 1) {
                subset_sums[i] += element;
            }
            selector >>= 1;
        }
    }
    return subset_sums;
}

template<typename Container>
bool is_special(const Container &A) {
    // Computing size of A. Workaround for cppitertools classes
    // which don't have a .size() method.
    const auto n = std::distance(A.begin(), A.end());

    // Rule 1: Smaller subsets have smaller sums.
    // Shortcut, since A is sorted: a1 + a2 > an, a1+a2+a3 > a(n-1) + an etc.
    // is a sufficient condition to check.
    // We check this first, as this is _much_ easier to do.
    int left_sum = A[0];
    int right_sum = 0;
    for (int i = 0; i < n / 2; i++) {
        left_sum += A[i + 1];
        right_sum += A[n - 1 - i];

        if (left_sum <= right_sum)
            return false;
    }

    // Rule 2: No duplicate subset sums.
    // If two duplicate sums are found, we check if
    // the corresponding sets are disjoint (meaning
    // set i and set k have no common set bits). If
    // both conditions are met, no special sum for you.
    const auto sums = all_subset_sums(A);
    auto n_sums = std::distance(sums.begin(), sums.end());
    for (int i = 0; i < n_sums; ++i) {
        auto k = std::distance(sums.begin(),
                               std::find(sums.begin() + i + 1,
                                         sums.end(),
                                         sums[i])
        );
        if (k != n_sums and not (i & k))
            return false;
    }
    return true;
}


int main() {
    auto start = std::chrono::high_resolution_clock::now();

    long total = 0;

    std::ifstream input("../../105/p105_sets.txt");
    std::string line;
    while (std::getline(input, line)) {
        std::stringstream linestream(line);
        std::vector<int> A;
        std::string number;
        while (std::getline(linestream, number, ',')) {
            A.push_back(std::stoi(number));
        }

        // Important! Needs to be sorted!
        std::sort(A.begin(), A.end());
        if (is_special(A)) {
            total = std::accumulate(A.begin(), A.end(), total);
        }
    }
    printf("Answer: %ld\n", total);

    auto end = std::chrono::high_resolution_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / (double) 1e6;
    printf("Found in time: %g ms\n", time);
}
