/*
In the game of darts a player throws three darts at a target board which is
split into twenty equal sized sections numbered one to twenty.

The score of a dart is determined by the number of the region that the dart
lands in. A dart landing outside the red/green outer ring scores zero. The
black and cream regions inside this ring represent single scores. However, the
red/green outer ring and middle ring score double and treble scores
respectively.

At the centre of the board are two concentric circles called the bull region,
or bulls-eye. The outer bull is worth 25 points and the inner bull is a double,
worth 50 points.

There are many variations of rules but in the most popular game the players
will begin with a score 301 or 501 and the first player to reduce their running
total to zero is a winner. However, it is normal to play a "doubles out"
system, which means that the player must land a double (including the double
bulls-eye at the centre of the board) on their final dart to win; any other
dart that would reduce their running total to one or lower means the score for
that set of three darts is "bust".

When a player is able to finish on their current score it is called a
"checkout" and the highest checkout is 170: T20 T20 D25 (two treble 20s and
double bull).

There are exactly eleven distinct ways to checkout on a score of 6:

            D3
            D1	D2
            S2	D2
            D2	D1
            S4	D1
            S1	S1	D2
            S1	T1	D1
            S1	S3	D1
            D1	D1	D1
            D1	S2	D1
            S2	S2	D1

Note that D1 D2 is considered different to D2 D1 as they finish on different
doubles. However, the combination S1 T1 D1 is considered the same as T1 S1 D1.

In addition we shall not include misses in considering combinations; for
example, D3 is the same as 0 D3 and 0 0 D3.

Incredibly there are 42336 distinct ways of checking out in total.

How many distinct ways can a player checkout with a score less than 100?


Solution comment: Search space very small, brute force solves in ~1 ms.
                  Only thing of note is that we only count (A, B, C) once,
                  and skip (B, A, C).
*/


#include <iostream>
#include <vector>
#include <chrono>

using namespace std::chrono;

int main() {
    constexpr int upper = 100;

    auto start = high_resolution_clock::now();

    std::vector<int> doubles;
    std::vector<int> targets;
    for (int i = 1; i <= 20; ++i) {
        targets.emplace_back(i * 1);
        targets.emplace_back(i * 2);
        targets.emplace_back(i * 3);
        doubles.emplace_back(i * 2);
    }
    targets.emplace_back(25 * 1);
    targets.emplace_back(25 * 2);
    doubles.emplace_back(25 * 2);
    targets.emplace_back( 0 * 1);

    int checkouts = 0;
    for (int checkout_score = 2; checkout_score < upper; ++checkout_score) {

        // Iterating on the doubles as the outer loop saves some time, as
        // these are the only options here. The doubles are also auto-sorted,
        // so we can early quit _some_ of the times.
        for (auto last = doubles.begin(); last != doubles.end(); ++last) {
            if (*last > checkout_score)
                break;
            for (auto first = targets.begin(); first != targets.end(); ++first) {
                auto outer_sum = *last + *first;
                for (auto second = first; second != targets.end(); ++second) {
                    if (outer_sum + *second == checkout_score)
                        ++checkouts;
                }
            }
        }
    }

    auto time = duration_cast<nanoseconds>(high_resolution_clock::now() - start).count() / (double) 1e6;
    printf("# checkouts from < %d = %d\n", upper, checkouts);
    printf("Found in %.3f ms\n", time);

}
