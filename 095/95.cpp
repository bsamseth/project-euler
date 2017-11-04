/*
 The proper divisors of a number are all the divisors excluding the number itself.
 For example, the proper divisors of 28 are 1, 2, 4, 7, and 14. As the sum of
 these divisors is equal to 28, we call it a perfect number.
 
 Interestingly the sum of the proper divisors of 220 is 284 and the sum of the
 proper divisors of 284 is 220, forming a chain of two numbers. For this reason,
 220 and 284 are called an amicable pair.
 
 Perhaps less well known are longer chains. For example, starting with 12496,
 we form a chain of five numbers:
 
 12496 → 14288 → 15472 → 14536 → 14264 (→ 12496 → ...)
 
 Since this chain returns to its starting point, it is called an amicable chain.
 
 Find the smallest member of the longest amicable chain with no element exceeding one million.

 
 Solution comment: Quite fast (~.3s), due to use of sieve to calclate S(n) for 0 <= n <= 1e6.
                   Then a matter of finding longest chain efficiently. Make sure to only
                   consider each number once, as it may only be part of at most one chain.
                   Smallest member necessarily the first repeating number occuring when we
                   iterate in acending order.
                   High gain by compiling with 
 */

#include <iostream>
#include <unordered_map>

using namespace std;

const int UPPER = 1000000;
int S[UPPER+1];

/*
 * Fill S with s(n) for 0 <= n <= UPPER.
 * Add every number less than UPPER to each multiple of it self.
 * Need then only do this for the UPPER/2 first numbers.
 */
void sum_proper_divisors_sieve() {
    S[0] = S[1] = 0;
    for (int i = 1; i <= UPPER/2; ++i) {
        for (int j = 2*i; j <= UPPER; j += i) {
            S[j] += i;
        }
    }
}


int main() {
    // Init. S array.
    sum_proper_divisors_sieve();
    // Each number need only be considered once, bool array to mark seen.
    bool dead[UPPER+1] = {0};
    int longest_chain = 0, smallest_member = 0;
    for (int n = 2; n < UPPER; ++n) {
        // Need to know what numbers are part of the current chain.
        // Storing numbers, with their index in the chain.
        unordered_map<int, int> chain;
        int loop_length = 0;
        int m = n;
        bool found_chain = false;
        while (m < UPPER and !dead[m]) {
            dead[m] = true;
            chain[m] = loop_length++;
            m = S[m];
            if (chain.find(m) != chain.end())
                found_chain = true;  // Implicit break.
        }
        if (found_chain) {
            // Chain may be entered from outside chain,
            // so subtract the path length into the chain.
            // Smallest member is necessarily m, as chain
            // would be found earlier if it wasn't.
            loop_length -= chain[m];
            if (longest_chain < loop_length) {
                longest_chain = loop_length;
                smallest_member = m;
            }
        }
    }
    printf("Chain length: %d, smallest member: %d\n", longest_chain, smallest_member);
    return 0;
}
