/*
 Consider the fraction, n/d, where n and d are positive integers. If n<d and HCF(n,d)=1, it is called a reduced proper fraction.
 
 If we list the set of reduced proper fractions for d ≤ 8 in ascending order of size, we get:
 
 1/8, 1/7, 1/6, 1/5, 1/4, 2/7, 1/3, 3/8, 2/5, 3/7, 1/2, 4/7, 3/5, 5/8, 2/3, 5/7, 3/4, 4/5, 5/6, 6/7, 7/8
 
 It can be seen that there are 3 fractions between 1/3 and 1/2.
 
 How many fractions lie between 1/3 and 1/2 in the sorted set of reduced proper fractions for d ≤ 12,000?
 
 
 Solution comment: If we have two neighboring terms in the Faray sequence, a/b < c/d,
 the the next term, p/q, is given as (from wiki):
 
    k = floor( (n + b) / d )
    p = k * c - a
    q = k * d - b.
 
 This gives us a fast way to produce all the terms for a given upper limit n. We
 need two terms to start. a/b = 1/3 is given, the next term, c/d, must satisfy
 
    bc - ad = 1.
 
 If we maximize this in terms of d, we have in this case (since a = 1).
 
    c = floor( (n + 1) / 3 )
    d = 3 * c - 1.
 
 Then we can iterate, finding new terms p/q as long as p/q < 1/2.
 */

#include <iostream>

int main() {
    
    int n = 12000;
    int a = 1, b = 3;  // Lower bound, a/b = 1/3.
    int c = (n + 1) / b, d = 3 * c - 1;  // c/d is next term in Faray seq.
    int p = 1, q = 2;  // Upper bound, p/q = 1/2
    
    int count = 0;
    while (q * c <  p * d) {
        int k = (n + b) / d;
        int c_tmp = c, d_tmp = d;
        c = k*c-a;
        d = k*d-b;
        a = c_tmp;
        b = d_tmp;
        ++count;
    }
    
    printf("%d fractions between 1/3 and 1/2 for d <= %d\n", count, n);
    return 0;
}
