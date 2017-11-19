/*
 70 colored balls are placed in an urn, 10 for each of the seven rainbow colors.
 
 What is the expected number of distinct colors in 20 randomly picked balls?
 
 Give your answer with nine digits after the decimal point (a.bcdefghij).
 
 
 Solution comment: Instant solution.
                   Let P(k, n) be the prob. of having k different color
                   after n drawn. By definition we have P(0, 0) = 1. We
                   The probability of picking a new color, given k and n,
                   is (70 - 10*k) / (70 - n), as there are 70-10*k balls
                   with a new color, and 70 - n balls left. We then have
                   the following two relations, following intuitively from
                   this result:
                     P(k+1, n+1) = P(k, n) * ( 70 - 10*k ) / (70 - n)
                     P(k, n+1)   =   P(k, n) * max(0, (10*k - n) / (70 - n))
                                   + P(k-1, n) * ( 70 - 10*(k-1) ) / (70 - n)
 
                   The expectation is then
                        sum_k( k * P(k, 20) )
 
 */

#include <iostream>
#include <array>
#include <algorithm>
using namespace std;


int main() {
    const int n_colors = 7;
    const int n_each   = 10;
    const int n_total  = n_colors * n_each;
    const int n_draw   = 20;
    
    array<array<double, n_draw + 1>, n_colors + 1> P;
    P[0][0] = 1;
    for (int k = 1; k <= n_colors; k++) {
        P[k][k] = P[k-1][k-1] * (n_total - n_each * (k-1)) / ((double) n_total - (k - 1));
        for (int n = k; n < n_draw; n++) {
            P[k][n+1] =   P[k][n] * max(0.0, (n_each * k - n) / ((double) n_total - n))
                        + P[k-1][n] * (n_total - n_each * (k - 1)) / ((double) n_total - n);
        }
    }
    double expectation = 0;
    for (int k = 1; k <= n_colors; k++) {
        expectation += k * P[k][n_draw];
    }
    printf("%1.9f\n", expectation);
    
    
    return 0;
}
