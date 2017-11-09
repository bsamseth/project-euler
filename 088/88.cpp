/*
A natural number, N, that can be written as the sum and product of a given
set of at least two natural numbers, {a1, a2, ... , ak} is called a product-sum
number: N = a1 + a2 + ... + ak = a1 × a2 × ... × ak.

For example, 6 = 1 + 2 + 3 = 1 × 2 × 3.

For a given set of size, k, we shall call the smallest N with this property a
minimal product-sum number. The minimal product-sum numbers for sets of size,
k = 2, 3, 4, 5, and 6 are as follows.

k=2: 4 = 2 × 2 = 2 + 2
k=3: 6 = 1 × 2 × 3 = 1 + 2 + 3
k=4: 8 = 1 × 1 × 2 × 4 = 1 + 1 + 2 + 4
k=5: 8 = 1 × 1 × 2 × 2 × 2 = 1 + 1 + 2 + 2 + 2
k=6: 12 = 1 × 1 × 1 × 1 × 2 × 6 = 1 + 1 + 1 + 1 + 2 + 6

Hence for 2≤k≤6, the sum of all the minimal product-sum numbers is 4+6+8+12 = 30;
note that 8 is only counted once in the sum.

In fact, as the complete set of minimal product-sum numbers for 2≤k≤12 is
{4, 6, 8, 12, 15, 16}, the sum is 61.

What is the sum of all the minimal product-sum numbers for 2≤k≤12000?

Solution comment: Very quick.
                  For any set of n integers >= 1, the product is equal to the sum
                  if k = prod - sum + n, when n >= 2. The maximum factor in any such set
                  is k, as {2, k} is a solution for k.

                  The code generates all sets of factors with product [2, 2 * 12000],
                  keeping the smallest solution for each k.
*/

#include <iostream>
#include <limits>
#include <algorithm>
#include <unordered_set>
using namespace std;

const int max_k = 12000;
int numbers[max_k];
int results[max_k+1];

void solve(int prod, int sum, int n) {
    int mul = 2;
    int p = prod, s = sum;
    int k;
    while ((k = (p *= mul) - (s += mul) + n+1) <= max_k) {
        solve(p, s, n+1);
        results[k] = min(results[k], p);
        p /= mul;
        s -= mul;
        mul++;
    }
}

int main() {
    for (int i = 2; i <= max_k; i++)
        results[i] = numeric_limits<int>::max();

    for (int p = 2; p <= max_k; p++)
        solve(p, p, 1);

    unordered_set<int> seen;
    for (int i = 0; i <= max_k; i++)
        seen.insert(results[i]);

    long long sum = 0;
    for (int a : seen)
        sum += a;
    printf("%lld\n", sum);
    return 0;
}
