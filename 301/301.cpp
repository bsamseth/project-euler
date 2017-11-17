/*
 Nim is a game played with heaps of stones, where two players take it in turn to
 remove any number of stones from any heap until no stones remain.
 
 We'll consider the three-heap normal-play version of Nim, which works as follows:
 - At the start of the game there are three heaps of stones.
 - On his turn the player removes any positive number of stones from any single heap.
 - The first player unable to move (because no stones remain) loses.
 
 If (n1,n2,n3) indicates a Nim position consisting of heaps of size n1, n2 and n3
 then there is a simple function X(n1,n2,n3) — that you may look up or attempt to deduce for yourself — that returns:
 
 zero if, with perfect strategy, the player about to move will eventually lose; or
 non-zero if, with perfect strategy, the player about to move will eventually win.
 For example X(1,2,3) = 0 because, no matter what the current player does, his opponent
 can respond with a move that leaves two heaps of equal size, at which point every move
 by the current player can be mirrored by his opponent until no stones remain; so the
 current player loses. To illustrate:
 - current player moves to (1,2,1)
 - opponent moves to (1,0,1)
 - current player moves to (0,0,1)
 - opponent moves to (0,0,0), and so wins.
 
 For how many positive integers n ≤ 230 does X(n,2n,3n) = 0 ?
 
 Solution comment: X(x1, x2, x3) = x1 ^ x2 ^ x3. Searching all values <= 2^30 runs in
                   < 3 sec without optimization, < 0.3 sec with.
 
                   Turns out that cases where X(n, 2n, 3n)=0 is when n has no consecutive
                   active bits, which turns out to sum to the fib(n+2) when counting the
                   number of n's less than 2^n have this property. Not sure one why.
 */

#include <iostream>

int main() {
//    const int upper = 1L<<30;
//    int count = 0;
//    for (int n = 1; n <= upper; n++) {
//        if (!(n ^ (2*n) ^ (3*n)))
//            count++;
//    }
    int f1 = 0, f2 = 1;
    for (int i = 0; i <= 30; i++) {
        f2 += f1;
        f1 = f2 - f1;
    }
    printf("%d\n", f2);
    return 0;
}
