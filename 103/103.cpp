/*
Let S(A) represent the sum of elements in set A of size n. We shall call it a
special sum set if for any two non-empty disjoint subsets, B and C, the
following properties are true:

    1. S(B) ≠ S(C); that is, sums of subsets cannot be equal.
    2. If B contains more elements than C then S(B) > S(C).

If S(A) is minimised for a given n, we shall call it an optimum special sum
set. The first five optimum special sum sets are given below.

    n = 1: {1}
    n = 2: {1, 2}
    n = 3: {2, 3, 4}
    n = 4: {3, 5, 6, 7}
    n = 5: {6, 9, 11, 12, 13}

It seems that for a given optimum set, A = {a1, a2, ... , an}, the next optimum
set is of the form B = {b, a1+b, a2+b, ... ,an+b}, where b is the "middle"
element on the previous row.

By applying this "rule" we would expect the optimum set for n = 6 to be A =
{11, 17, 20, 22, 23, 24}, with S(A) = 117. However, this is not the optimum
set, as we have merely applied an algorithm to provide a near optimum set. The
optimum set for n = 6 is A = {11, 18, 19, 20, 22, 25}, with S(A) = 115 and
corresponding set string: 111819202225.

Given that A is an optimum special sum set for n = 7, find its set string.

NOTE: This problem is related to Problem 105 and Problem 106.

Solution comment: Brute forcing, with some efficient checking of the rules.
                  The provided near-optimal algorithm gives some psudoe bounds
                  on the search space. From this, we should search every n = 7
                  set with numbers in ~[20, 45], maybe with pluss minus a few
                  on each end.

                  If compiled with optimization, solution searches [20, 45] in ~200 ms.
 */
#include <iostream>
#include <cmath>
#include <chrono>
#include <vector>
#include <numeric>

#include "combinations.hpp"
#include "range.hpp"


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

    // Try every combination of 7 numbers in some range.
    // The range is based on a little trial and error, but
    // mostly a guess based on the provided near-optimal algorithm.
    for (auto &&A : iter::combinations(iter::range(20, 46), 7)) {
        if (is_special(A)) {
            auto sum = std::accumulate(A.begin(), A.end(), 0);
            for (auto &&elem : A) {
                std::cout << elem;
            }
            std::cout << " is special, with sum " << sum << "\n";
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / (double) 1e6;
    printf("Found in time: %g ms\n", time);
}
