/*
 Consider the divisors of 30: 1,2,3,5,6,10,15,30.
 It can be seen that for every divisor d of 30, d+30/d is prime.
 
 Find the sum of all positive integers n not exceeding 100 000 000
 such that for every divisor d of n, d+n/d is prime.
 
 
 Solution comment: Quite slow, ~12 sec. Checking every divisor
                   in a sieve like manner. Possibly not a good idea
                   after all...
 */

#include <iostream>
#include <vector>
using namespace std;

vector<bool> prime_sieve(int n) {
    vector<bool> is_prime (n+1, true);
    is_prime[0] = is_prime[1] = false;
    // Remove all even numbers.
    for (int i = 4; i <= n; i += 2)
        is_prime[i] = false;
    // Iterate over the rest, toggling composites.
    int m = 3;
    while (m * m <= n) {
        if (is_prime[m]) {
            for (int k = m * m; k <= n; k += m)
                is_prime[k] = false;
        }
        m += 2;
    }
    return is_prime;
}

int main() {
    const int upper = 100000000;
    vector<bool> is_prime = prime_sieve(upper);
    vector<bool> special (upper + 1, true);
    
    long sum = 1;
    for (int i = 2; i <= upper; i++) {
        for (int j = i, k = 1; j <= upper; j += i, k++) {
            special[j] = special[j] and is_prime[j+1] and is_prime[i+k];
        }
        if (special[i])
            sum += i;
    }
    
    printf("Sum = %ld\n", sum);
    return 0;
}
