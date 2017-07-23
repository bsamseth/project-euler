/*
 Euler's Totient function, φ(n) [sometimes called the phi function], is used to determine the number of numbers less than n which are relatively prime to n. For example, as 1, 2, 4, 5, 7, and 8, are all less than nine and relatively prime to nine, φ(9)=6.
 
 n	Relatively Prime	φ(n)	n/φ(n)
 2	1	1	2
 3	1,2	2	1.5
 4	1,3	2	2
 5	1,2,3,4	4	1.25
 6	1,5	2	3
 7	1,2,3,4,5,6	6	1.1666...
 8	1,3,5,7	4	2
 9	1,2,4,5,7,8	6	1.5
 10	1,3,7,9	4	2.5
 
 It can be seen that n=6 produces a maximum n/φ(n) for n ≤ 10.
 
 Find the value of n ≤ 1,000,000 for which n/φ(n) is a maximum.
 
 
 Solution comment: Brute force not best, but runs in ~1 sec. 
 Better was to realize that
 
    n/phi(n) = n/(n * prod(1-1/p)) = 1 / prod(1 - 1/p),
 
 where the product is over all the distinct primes of n. This has maximum when the
 product has a minimum. This again happens for a number with the most distinct, small
 prime factors. So better would be
 
    result = 1
    while ((result *= next_prime) < 1000000);
    answer = result / last_prime.
 */

#include <iostream>
#include <ctime>
#include <cmath>
#include <map>
#include <set>
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


int main() {
    clock_t t_start = clock();
    double max_ratio = 0;
    int max_n = 0;
    for (int n = 2; n <= 1000000; ++n) {
        double ratio = n / phi(n);
        if (max_ratio < ratio) {
            max_ratio = ratio;
            max_n = n;
        }
    }
    printf("max(n/phi(n)) = %d, n = %d\n", (int)rint(max_ratio), max_n);
    printf("Time taken: %.2fs\n", ((double) clock() - t_start) / CLOCKS_PER_SEC);
    return 0;
}




