/*
 Let p(n) represent the number of different ways in which n coins can be separated into piles. For example, five coins can be separated into piles in exactly seven different ways, so p(5)=7.
 
 OOOOO
 OOOO   O
 OOO   OO
 OOO   O   O
 OO   OO   O
 OO   O   O   O
 O   O   O   O   O
 
 Find the least value of n for which p(n) is divisible by one million.
 
 
 
 Solution comment: This solution uses a way of generating the partitions of n based on the last few problems. It requires an upper bound,
 this was set through trial an error, as a to low bound gives no result. 
 
 An important note is that we only need the value of p(n) mod 10^6. This way we don't run into overflow issues. It is allowed to take 
 the modulo term by term, it will not affect the total sum.
 
 There are faster ways of evaluating the partition funciton (see the use of pentagonal numbers on wiki).
 */

#include <iostream>

int main() {
    const int n = 60000;
    int ways [n+1] = {0};
    ways[0] = 1;
    for (int i = 1; i < n; ++i) {
        for (int j = i; j <= n; ++j) {
            ways[j] = (ways[j] + ways[j-i]) % 1000000;
        }
        if (ways[i] == 0) {
            printf("ways[%d]=0 mod 10^6\n", i);
            return 0;
        }
    }
    return -1;
}
