/*
 The smallest number expressible as the sum of a prime square, prime cube, and prime fourth power is 28. In fact, there are exactly four numbers below fifty that can be expressed in such a way:

 28 = 2^2 + 2^3 + 2^4
 33 = 3^2 + 2^3 + 2^4
 49 = 5^2 + 2^3 + 2^4
 47 = 2^2 + 3^3 + 2^4

 How many numbers below fifty million can be expressed as the sum of a prime square, prime cube, and prime fourth power?


 Solution comment: Not much to this, just brute force.
 */

#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <algorithm>

std::vector<int> primes_up_to(int n);

int main()
{
    const int upper = 50000000;
    // Generate all need primes. Max prime is p such that
    //     p^2 + 2^3 + 2^4 = upper
    //  -> p <= sqrt(upper - 24)
    std::vector<int> primes = primes_up_to(std::sqrt(upper - 24));

    std::set<int> results;
    for (int p : primes) {
        int pp = p*p;
        for (int q : primes) {
            int ppqqq = pp+q*q*q;
            if (ppqqq > upper - 16) break;
            for (int r : primes) {
                int tot = ppqqq+r*r*r*r;
                if (tot > upper) break;
                results.insert(tot);
            }
        }
    }
    printf("Count: %lu\n", results.size());
    return 0;
}

std::vector<int> primes_up_to(int n) {
    if (n < 2)
        return {};

    int sqrtn = (int) std::sqrt(n);
    std::vector<bool> isComposite (n+1, false);
    isComposite[0] = isComposite[1] = true;

    std::vector<int> primes = { 2 };

    // Remove all even numbers.
    for (int i = 4; i <= n; i += 2)
        isComposite[i] = true;

    // Iterate over the rest, toggling composites.
    for (int m = 3; m <= sqrtn; m+=2) {
        if (!isComposite[m]) {
            primes.push_back(m);
            for (int k = m * m; k <= n; k += m)
                isComposite[k] = true;
        }
    }
    // All composites have now been toggled, keep any primes > sqrt(n).
    for (int m = (sqrtn & 1) ? sqrtn : sqrtn+1; m <= n; m+=2)
        if (!isComposite[m])
            primes.push_back(m);
    return primes;
}
