/*
 Euler's Totient function, φ(n) [sometimes called the phi function], is used to
 determine the number of positive numbers less than or equal to n which are
 relatively prime to n. For example, as 1, 2, 4, 5, 7, and 8, are all less than
 nine and relatively prime to nine, φ(9)=6.  The number 1 is considered to be
 relatively prime to every positive number, so φ(1)=1.

 Interestingly, φ(87109)=79180, and it can be seen that 87109 is a permutation
 of 79180.

 Find the value of n, 1 < n < 107, for which φ(n) is a permutation of n and the
 ratio n/φ(n) produces a minimum.


 Solution comment: Pure brute force. Takes about ~20 secs...
 */

#include <iostream>
#include <ctime>
#include <cmath>
#include <vector>

using std::cout;
using std::endl;

/* Return vector of unique prime factors of n. */
std::vector<int> prime_factors(int n) {
    std::vector<int> primfac;
    int d = 2;
    while (d*d <= n) {
        bool not_inserted = true;
        while (n % d == 0) {
            if (not_inserted) {
                primfac.push_back(d);
                not_inserted = false;
            }
            n /= d;
        }
        ++d;
    }
    if (n > 1)
        primfac.push_back(n);
    return primfac;
}

double phi(int n) {
    double s = n;
    for (auto pair : prime_factors(n)) {
        s *= (1 - 1.0/(double) pair);
    }
    return s;
}

bool is_permutation(int a, int b) {
    int c[10] = {0};

    while (a) { ++c[a%10]; a/=10; }
    while (b) { --c[b%10]; b/=10; }

    int res = 0;
    for (int i=0;i<10;i++) res |= c[i];
    return res == 0;
}

int main() {
    clock_t t_start = clock();
    double min_ratio = INT_MAX;
    int min_n = -1;
    for (int n = 2; n <= 10000000; ++n) {
        double p = phi(n);
        double ratio = n / p;
        if (ratio < min_ratio and is_permutation(n, (int) rint(p))) {
            min_ratio = ratio;
            min_n = n;
        }
    }
    printf("min(n/phi(n)) = %f, n = %d\n", min_ratio, min_n);
    printf("Time taken: %.2fs\n", ((double) clock() - t_start) / CLOCKS_PER_SEC);
    return 0;
}



