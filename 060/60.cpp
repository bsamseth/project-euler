
#include <iostream>
#include <cmath>
#include <vector>
#include <set>

std::vector<bool> is_prime_up_to(int n) {
    int sqrtn = (int) std::sqrt(n);
    std::vector<bool> is_prime (n+1, true);
    is_prime[0] = is_prime[1] = false;
    // Remove all even numbers.
    for (int i = 4; i <= n; i += 2)
        is_prime[i] = false;
    // Iterate over the rest, toggling composites.
    for (int m = 3; m <= sqrtn; m+=2) {
        if (is_prime[m]) {
            for (int k = m * m; k <= n; k += m)
                is_prime[k] = false;
        }
    }
    return is_prime;
}

int concat(int a, int b) {
    return b ? pow(10, floor(log10(b))+1) * a + b : 10 * a;
}


int main() {
    const int N = 1000000;
    std::vector<bool> is_prime = is_prime_up_to(N);
    std::vector<int> primes;
    for (int i = 0; i < N; ++i)
        if (is_prime[i])
            primes.push_back(i);
    printf("Prepared primes\n");
    int n_primes = (int) primes.size();
    int largest = primes[n_primes-1];
    
    for (int i = 1; i < n_primes; ++i) {

        int p = primes[i];
        int group[6] = {p};
        int group_count = 1;
        for (int j = i + 1; j < n_primes; ++j) {
            int q = primes[j];
            bool good_j = true;
            for (int g = 0; g < group_count; ++g) {
                int gp = group[g];
                int gpq = concat(gp, q), qgp = concat(q, gp);
                if ((gpq > largest or qgp >= largest) or
                    (!is_prime[gpq] or !is_prime[qgp])) {
                    good_j = false;
                    break;
                }
            }
            if (good_j) {
                group[group_count++] = q;
            }
            if (group_count == 4)
                break;
        }
        if (group_count == 4) {
            for (int g = 0; g < group_count; ++g) {
                printf("%d ", group[g]);
            }
            printf("\n");
            break;
        }
    }
    
    printf("%d\n", (int) primes.size());
    return 0;
}
