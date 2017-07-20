/*
 It turns out that 12 cm is the smallest length of wire that can be bent to form an integer sided right angle triangle in exactly one way, but there are many more examples.
 
 12 cm: (3,4,5)
 24 cm: (6,8,10)
 30 cm: (5,12,13)
 36 cm: (9,12,15)
 40 cm: (8,15,17)
 48 cm: (12,16,20)
 
 In contrast, some lengths of wire, like 20 cm, cannot be bent to form an integer sided right angle triangle, and other lengths allow more than one solution to be found; for example, using 120 cm it is possible to form exactly three different integer sided right angle triangles.
 
 120 cm: (30,40,50), (20,48,52), (24,45,51)
 
 Given that L is the length of the wire, for how many values of L ≤ 1,500,000 can exactly one integer sided right angle triangle be formed?
 
 
 Solution comment: The solution is based on Euclids formaula for pythagorian triplets. Here we only care about the sum of the
 side lengths, so the expression for an L that can form a pythagorian triplet can be simplified to just 
            L = k * 2(m+n)*m,
 where m > n > 0 are coprime and not both odd, and k > 0 is an integer.
 
 We note that since the sum L > 2*m*m, the loop over possible m values can be limited to sqrt(L)/2, where L is the upper bound for the sum.
 This makes the algorithm O(sqrt(L) * sqrt(L) * (k + O(gcd))). Euclids algorithm for gcd is O(h), where h is the number of digits of the smaller number.
 For k we have that k * sum <= upper -> k <= upper/sum -> O(k) = O(upper) = O(L).
 This gives
            
            O(L * (log(sqrt(L)) + L)) = O(L * log L + L * L) = O(L^2).
 This is, however, a _very_ generous upper bound, as many n values are skipped, and the values that k can take are much less than upper for most m,n.
 */

#include <iostream>
#include <ctime>

int gcd(int a, int b) {
    int tmp;
    while (b) {
        tmp = b;
        b = a%b;
        a = tmp;
    }
    return a;
}

int main() {
    const clock_t t_start = clock_t();
    const int upper = 1500000;
    int L [upper+1] = {0};

    for (int m = 2; m * m < upper / 2; ++m) {
        for (int n = 1; n < m; ++n) {
            if ((~(m^n) & 1) or gcd(m, n) != 1) continue;;
            int sum = 2 * (m+n) * m;
            if (sum > upper) break;
            for (int ksum = sum, k = 1; ksum <= upper; ksum = sum * ++k) {
                ++L[ksum];
            }
        }
    }

    int count = 0;
    for (int i = 0; i <= upper; ++i)
        if (L[i] == 1)
            ++count;
    
    printf("Number of L's <= %d with exactly 1 pythagorian triplet: %d\n", upper, count);
    printf("Time spent: %f\n", (clock() - t_start) / (double) CLOCKS_PER_SEC);
    return 0;
}
