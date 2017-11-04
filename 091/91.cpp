/*
The points P (x1, y1) and Q (x2, y2) are plotted at integer co-ordinates
and are joined to the origin, O(0,0), to form ΔOPQ.
 
There are exactly fourteen triangles containing a right angle that can
be formed when each co-ordinate lies between 0 and 2 inclusive;
that is, 0 ≤ x1, y1, x2, y2 ≤ 2.

Given that 0 ≤ x1, y1, x2, y2 ≤ 50, how many right triangles can be formed?

Solution comment: Brute force, after some pruning of possibilities.
                  May say that x2 ≤ x1, and y1 ≤ y2, as ΔOPQ == ΔOQP.
                  Right angles checked by checking dot products of all
                  three vectors. Loop counts (x1=x2 and y1=y2), so subtract
                  all these from count. Equals N*N.
*/


#include <iostream>

using namespace std;


#define DOT(x1, y1, x2, y2) ((x1) * (x2) + (y1) * (y2))

int main() {
    int N = 50;
    int count = 0;
    for (int x1 = 1; x1 <= N; ++x1) {
        for (int y2 = 1; y2 <= N; ++y2) {
            for (int x2 = 0; x2 <= x1; ++x2) {
                for (int y1 = 0; y1 <= y2; ++y1) {
                    if (!DOT(x1, y1, x2, y2) or
                        !DOT(x1, y1, x2 - x1, y2 - y1) or
                        !DOT(x2, y2, x2 - x1, y2 - y1)) {
                        ++count;
                    }
                }
            }
        }
    }
    printf("%d\n", count - N*N);
    return 0;
}
