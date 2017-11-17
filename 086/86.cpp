/*
 A spider, S, sits in one corner of a cuboid room, measuring 6 by 5 by 3, and a fly, F,
 sits in the opposite corner. By travelling on the surfaces of the room the shortest
 "straight line" distance from S to F is 10 and the path is shown on the diagram.
 
 However, there are up to three "shortest" path candidates for any given cuboid
 and the shortest route doesn't always have integer length.
 
 It can be shown that there are exactly 2060 distinct cuboids, ignoring rotations,
 with integer dimensions, up to a maximum size of M by M by M, for which the shortest
 route has integer length when M = 100. This is the least value of M for which the
 number of solutions first exceeds two thousand; the number of solutions when M = 99 is 1975.
 
 Find the least value of M such that the number of solutions first exceeds one million.
 
 
 Solution comment: Assuming the cuboid has side lengths a >= b >= c, the shortest path
                   can be found to be sqrt(a^2 + (b + c)^2) by minimizing the
                   distance as dist(a,b,c) = sqrt((a-x)^2 + b^2) + sqrt(x^2+c^2),
                   found as the sum of the two surface distances. Optimizing this gives
                   x = ac/(b+c), which yields the solution. Easier is to see this by
                   unfolding the cuboid onto the plane, at which point the solution
                   is obvious.
                   We have solutions if the number in the root is a perfect square.
                   We can avoid the inner loop over c by just considering the sum b+c,
                   and if a solution exists, add to solutions the number of ways we may
                   get b+c == bc.
 */
 
#include <iostream>
#include <cmath>
using namespace std;

bool is_square(long n) {
    long root = sqrt(n) + 0.5;
    return root * root == n;
}

int main() {
    int integer_sols = 0;
    for (int a = 1; ; a++) {
        for (int bc = 2; bc <= 2*a; bc++) {
            long d2 = a*a + bc*bc;
            if (is_square(d2)) {
                integer_sols += bc <= a ? bc/2 : a - (bc+1)/2 + 1;
                if (integer_sols >= 1e6) {
                    printf("%d %d\n", a, integer_sols);
                    return 0;
                }
            }
        }
    }
}
