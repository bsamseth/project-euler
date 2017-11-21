/*
 The largest integer ≤ 100 that is only divisible by both the primes 2 and 3 is 96,
 as 96=32*3=25*3. For two distinct primes p and q let M(p,q,N) be the largest
 positive integer ≤N only divisible by both p and q and M(p,q,N)=0 if such a
 positive integer does not exist.
 
 E.g. M(2,3,100)=96.
 M(3,5,100)=75 and not 90 because 90 is divisible by 2 ,3 and 5.
 Also M(2,73,100)=0 because there does not exist a positive integer ≤ 100 that
 is divisible by both 2 and 73.
 
 Let S(N) be the sum of all distinct M(p,q,N). S(100)=2262.
 
 Find S(10 000 000).
 
 Solution comment:
 Quite quick, ~0.1 sec. Pure search of all (p, q) pairs with p < q and p * q <= N.
 M(p, q, N) is rather quick, O( log(N)^2 / log(p) / log(q) ). About 25% spent on
 finding the primes. Pitfall that took some time to realise was that we get overflow
 in M(p, q, N) if just using int, causing an error.
 */

#include <iostream>
#include <vector>
using namespace std;

vector<int> prime_sieve(int n) {
    vector<int> primes = {2};
    vector<bool> is_prime (n+1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 4; i <= n; i += 2)
        is_prime[i] = false;
    int m = 3;
    while (m * m <= n) {
        if (is_prime[m]) {
            primes.push_back(m);
            for (int k = m * m; k <= n; k += m)
                is_prime[k] = false;
        }
        m += 2;
    }
    for (; m <= n; m += 2) {
        if (is_prime[m]) {
            primes.push_back(m);
        }
    }
    return primes;
}
uint64_t M(int p, int q, int N) {
    if (q >= N or p * q > N) return 0;
    uint64_t found = 0;
    for (uint64_t p_i = p; p_i < N; p_i *= p) {
        for (uint64_t q_i = q; q_i < N; q_i *= q) {
            if (p_i * q_i <= N) {
                found = max(found, p_i * q_i);
            }
        }
    }
    return found;
}

int main() {
    const int N = 10000000;
    const vector<int> primes = prime_sieve(N / 2);
    uint64_t S = 0;
    for (int i = 0; i < primes.size() - 1; i++) {
        int p = primes[i];
        for (int j = i + 1; j < primes.size(); j++) {
            int q = primes[j];
            if (p * q > N) break;
            S += M(p, q, N);
        }
    }
    printf("S(%d) = %lld\n", N, S);
    return 0;
}
