/*
 It is possible to write five as a sum in exactly six different ways:
 
 4 + 1
 3 + 2
 3 + 1 + 1
 2 + 2 + 1
 2 + 1 + 1 + 1
 1 + 1 + 1 + 1 + 1
 
 How many different ways can one hundred be written as a sum of at least two positive integers?
 
 
 Solution comment: Counting all the partitions of 100 (minus the trivial one (100 = 100)), based on the 
 fastest known algorithm for generating all the partitions. This is likely not close to the best way,
 since we only need the _count_, not the actual partitions.
 
 The function better_algo is taken from mathblog.dk. It uses dynamic programming, and is _much_ faster for this case.
 */

#include <iostream>

int number_of_partitions(int n) {
    int *a = new int[n+1]();
    int k = 1, count = 0;
    a[1] = n;
    while (k) {
        int x = a[k-1] + 1;
        int y = a[k] - 1;
        --k;
        while (x <= y) {
            a[k] = x;
            y -= x;
            ++k;
        }
        a[k] = x+y;
        ++count;
    }
    free(a);
    return count;
}

int better_algo(int n) {
    int *ways = new int[n+1]();
    ways[0] = 1;
    for (int i = 1; i < n; ++i)
        for (int j = i; j <= n; ++j)
            ways[j] += ways[j-i];
    int res = ways[n];
    free(ways);
    return res;
}

int main() {
    int n = 100;
    //printf("It is possible to write %d as the sum of >1 integers in %d ways.\n", n, number_of_partitions(n)-1);
    printf("It is possible to write %d as the sum of >1 integers in %d ways.\n", n, better_algo(n));
    
    
    return 0;
}
