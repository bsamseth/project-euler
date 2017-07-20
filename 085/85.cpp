/*
 By counting carefully it can be seen that a rectangular grid measuring 3 by 2 contains eighteen rectangles.
 Although there exists no rectangular grid that contains exactly two million rectangles, find the area of the grid with the nearest solution.

 Solution comment: Googling lead to https://stackoverflow.com/a/17927830/3377926,
 which has the formula for the number of rectangles that can be made in a
 m x n grid. Then just try all the grids untill we get really close.
 */

#include <algorithm>
#include <iostream>

int main()
{
    const int target = 2000000;
    int best_diff = target, area;
    for (int m = 1; ; ++m) {
        for (int n = 1; n <= m; ++n) {
            int rects = (m*(m+1)*n*(n+1))/4;
            int diff = std::abs(target - rects);
            if (diff < best_diff) {
                printf("new best: %d, m=%d, n=%d, area=%d\n", rects, m, n, m*n);
                best_diff = diff;
                area = m*n;
            }
            // Guessing that if we are of by 100 times, then we can stop.
            else if (diff > 100*target) {
                return 0;
            }
        }
    }
}
