/*
 Find the unique positive integer whose square has the form 1_2_3_4_5_6_7_8_9_0,
 where each “_” is a single digit.
 
 Solution comment: Squares ending in 0 must have root ending in 0.
                   Search space is [sqrt(102030...), sqrt(192939...)],
                   i.e. all zeros or all nines. Can be done in steps of
                   10 from lower bound. Turns out solution is close to
                   upper bound, so much faster to search down.
                   Upper^2 is just smaller than LONG_MAX.
 */
#include <iostream>
using namespace std;

int main() {
    const int required[10] = {0, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    for (long n = 1389026620; n >= 1010101010; n -= 10) {  // Starting at the max is ~100 times faster.
        long n2 = n*n;
        int i = 0;
        do {
            long digit = n2 % 10;
            if (digit != required[i++])
                break;
            n2 /= 100;  // Skip irrelevant digit.
        } while (n2 > 0);
        
        if (n2 == 0) { // All divisions were made -> passed test.
            printf("%ld\n", n);
            return 0;
        }
    }
}
