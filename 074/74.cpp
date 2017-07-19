/*
 The number 145 is well known for the property that the sum of the factorial of its digits is equal to 145:
 
 1! + 4! + 5! = 1 + 24 + 120 = 145
 
 Perhaps less well known is 169, in that it produces the longest chain of numbers that link back to 169; it turns out that there are only three such loops that exist:
 
 169 → 363601 → 1454 → 169
 871 → 45361 → 871
 872 → 45362 → 872
 
 It is not difficult to prove that EVERY starting number will eventually get stuck in a loop. For example,
 
 69 → 363600 → 1454 → 169 → 363601 (→ 1454)
 78 → 45360 → 871 → 45361 (→ 871)
 540 → 145 (→ 145)
 
 Starting with 69 produces a chain of five non-repeating terms, but the longest non-repeating chain with a starting number below one million is sixty terms.
 
 How many chains, with a starting number below one million, contain exactly sixty non-repeating terms?
 
 
 Solution comment: This is just pure brute force, and not super fast. Could be much
 faster by implementing caching of the chain lengths.
 */

#include <iostream>
#include <set>

const long *make_factorials() {
    static long fac[10] = {1};
    for (int i = 1; i < 10; ++i)
        fac[i] = fac[i-1] * i;
    return fac;
}
const long * fac = make_factorials();

long fac_sum(long n) {
    long sum = 0;
    while (n) {
        sum += fac[n % 10];
        n /= 10;
    }
    return sum;
}

bool chain_length_60(long n) {
    std::set<long> seen;
    while (seen.count(n) == 0 and seen.size() < 60) {
        seen.insert(n);
        n = fac_sum(n);
    }
    return seen.size() == 60;
}

int main() {
    int count = 0;
    for (int i = 0; i < 1000000; ++i)
        if (chain_length_60(i))
            ++count;
    printf("Number of chains of length 60 with starting"
           "number under 1e6: %d\n", count);
}
