/*
 Consider the fraction, n/d, where n and d are positive integers. If n<d and HCF(n,d)=1, it is called a reduced proper fraction.
 
 If we list the set of reduced proper fractions for d ≤ 8 in ascending order of size, we get:
 
 1/8, 1/7, 1/6, 1/5, 1/4, 2/7, 1/3, 3/8, 2/5, 3/7, 1/2, 4/7, 3/5, 5/8, 2/3, 5/7, 3/4, 4/5, 5/6, 6/7, 7/8
 
 It can be seen that there are 21 elements in this set.
 
 How many elements would be contained in the set of reduced proper fractions for d ≤ 1,000,000?
 
 
 
 Solution comment: The size of a Farey sequence of order n is
        
    F(n) = 1 + sum_{m=1}^n phi(m)
 
 where phi(n) is the Euler totient function. The question is to find F(1e6)-2,
 since the problem doesn't count 0/1 and 1/1. The original version of this
 reused the code from earlier an ran in ~1 sec. This version uses an optimized
 way to calculate phi for a range of n-values. The sieve implemented is inspired
 from mathblog.dk.
 */


#include <iostream>
#include <numeric>
#include <cmath>


long sum_of_phi(int upper) {
    if (upper < 2)
        return upper;
    long *phi = new long[upper+1];
    std::iota(phi, phi + upper+1, 0);  // phi = [0, 1, 2, 3, ..., upper].
    
    long sum = 1;
    for (int i = 2; i <= upper; ++i) {
        if (phi[i] == i) {   // i is prime.
            double factor = (i-1) / (double) i;
            for (int j = i; j <= upper; j += i) {
                phi[j] *= factor;
            }
        }
        sum += phi[i];
    }
    delete[] phi;
    return sum;
}


int main() {
    printf("%ld\n", sum_of_phi(1000000) - 1);
    return 0;
}
