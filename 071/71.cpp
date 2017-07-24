/*
Consider the fraction, n/d, where n and d are positive integers. If n<d and
HCF(n,d)=1, it is called a reduced proper fraction.

If we list the set of reduced proper fractions for d ≤ 8 in ascending order of
size, we get:

1/8, 1/7, 1/6, 1/5, 1/4, 2/7, 1/3, 3/8, 2/5, 3/7, 1/2, 4/7, 3/5, 5/8, 2/3, 5/7,
3/4, 4/5, 5/6, 6/7, 7/8

It can be seen that 2/5 is the fraction immediately to the left of 3/7.

By listing the set of reduced proper fractions for d ≤ 1,000,000 in ascending
order of size, find the numerator of the fraction immediately to the left of
3/7.


Solution comment: This type of series is called a Farey sequence of order d.
It is known for neighboring terms, a/b and c/d, where a/b<c/d, that their
difference

        bc - ad = 1.

The order of the corresponding sequence thay are neighbors in is max(b,d).

In this case this implies

        b = (1 + 7*a) / 3.

This means that we need to find a solution to this equation that maximizes b.
We get this by using the largest possible a. Conditions are then that b <= N,
and that 1+7*a === 0 (mod 3).

Solution is found more or less instant.
*/

#include <iostream>

int main(void)
{
    int c = 3, d = 7, upper = 1000000;
    for (int a = upper-1; ; --a) {
        int b = (1 + a*d) / c;
        if (b <= upper and b * c - a*d == 1) {
            printf("a/b = %d/%d\n", a, b);
            return 0;
        }
    }
}
