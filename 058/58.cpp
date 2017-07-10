/*
 Starting with 1 and spiralling anticlockwise in the following way, a square spiral with side 
 length 7 is formed.
 
 37 36 35 34 33 32 31
 38 17 16 15 14 13 30
 39 18  5  4  3 12 29
 40 19  6  1  2 11 28
 41 20  7  8  9 10 27
 42 21 22 23 24 25 26
 43 44 45 46 47 48 49
 
 It is interesting to note that the odd squares lie along the bottom right diagonal, but what is more
 interesting is that 8 out of the 13 numbers lying along both diagonals are prime; that is, a ratio of
 8/13 ≈ 62%.
 
 If one complete new layer is wrapped around the spiral above, a square spiral with side length 9 will be
 formed. If this process is continued, what is the side length of the square spiral for which the ratio of
 primes along both diagonals first falls below 10%?
 */

#include <iostream>

bool is_prime(int n);


int main() {
    int n = 1;
    int add = 2, add_count = 0;
    int side_length = 1;
    int prime_count = 0, diag_count = 0;
    
    while (true) {
        n += add;
        
        prime_count += is_prime(n) ? 1 : 0;
        ++diag_count;
        
        if (++add_count == 4) {
            if (prime_count * 10 < diag_count) {
                printf("Smallest side length with p/n < 0.1: %d\n", side_length);
                return 0;
            }
            add += 2;
            side_length += 2;
            add_count = 0;
        }
    }
}

/* O(sqrt(n)) */
bool is_prime(int n) {
    if (n < 2)
        return false;
    if (n == 2 or n == 3)
        return true;
    if (n % 2 == 0 or n % 3 == 0)
        return false;
    
    int i = 5, w = 2;
    while (i * i <= n) {
        if (n % i == 0)
            return false;
        i += w;
        w = 6 - w;
    }
    return true;
}
