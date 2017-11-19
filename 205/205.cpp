/*
 Peter has nine four-sided (pyramidal) dice, each with faces numbered 1, 2, 3, 4.
 Colin has six six-sided (cubic) dice, each with faces numbered 1, 2, 3, 4, 5, 6.
 
 Peter and Colin roll their dice and compare totals: the highest total wins.
 The result is a draw if the totals are equal.
 
 What is the probability that Pyramidal Pete beats Cubic Colin? Give your
 answer rounded to seven decimal places in the form 0.abcdefg
 
 
 Solution comment:
 Probability of rolling a sum of p on n s-sided dice is (mathworld.wolfram.com/Dice.html)
    f(p, n, s) =  1/(s^n) sum_(k=0)^(floor((p-n)/s))(-1)^k (n choose k)(p-sk-1 choose n-1)
 Then denote Peters- and Colins sums by P and C, respectively, and Z = P - C.
 Then Z has the pmf. given by the convolution of P and C:
    Pr(Z = z) = sum_p ( Pr(P = p) * Pr(C = p - z) ),
 with
    Pr(P=p) = f(p, 9, 4)
    Pr(C=c) = f(c, 6, 6).
 We then find P(Z > 0), which is the probability of Peter rolling a higher sum than Colin:
    Pr(Z > 0) = sum_(z > 0) Pr(Z=z).
 
 Note that P in [9, 36], C in [6, 36] and Z in [-27, 30].
 */
#include <iostream>
#include <map>
#include <cmath>
using namespace std;

/*
 Return n choose k.
 Equivalent to the following, but optimized with memoization.
 Quite unneccessary for the problem numbers, shaves ~1ms of the
 total ~5ms it takes without this. Still a 20% speed up, which
 would be much larger for larger problem parameters.
 choose(n, k) = if k == 0 -> 1
                else -> n * choose(n-1, k-1)
 */
map<pair<int, int>, uint64_t> _memory;
uint64_t choose(int n, int k) {
    if (k == 0) return 1;
    pair<int, int> nk = {n , k};
    if (not _memory.count(nk)) {
        _memory[nk] = (n * choose(n-1, k-1)) / k;
    }
    return _memory[nk];
}

double Pr(int p, int n, int s) {
    int sum = 0;
    for (int k = 0; k <= (p-n)/s; k++) {
        sum += (1 - 2*(k&1)) * choose(n, k) * choose(p - s*k - 1, n - 1);
    }
    return sum / (double) pow(s, n);
}

double Pz(int z) {
    double prob = 0;
    for (int p = 9; p <= 36; p++) {
        prob += Pr(p, 9, 4) * Pr(p-z, 6, 6);
    }
    return prob;
}

int main() {
    double prob = 0;
    for (int z = 1; z <= 30; z++) {
        prob += Pz(z);
    }
    printf("%1.7f\n", prob);
    return 0;
}
