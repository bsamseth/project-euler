/*
A number chain is created by continuously adding the square of the digits in a number to form a new number until it has been seen before.

For example,

44 → 32 → 13 → 10 → 1 → 1
85 → 89 → 145 → 42 → 20 → 4 → 16 → 37 → 58 → 89

Therefore any chain that arrives at 1 or 89 will become stuck in an endless loop. What is most amazing is that EVERY starting number will eventually arrive at 1 or 89.

How many starting numbers below ten million will arrive at 89?
 */

#include <cstdio>
#include <string>

using std::to_string;

int sum_squared_digits(int n) {
    int sum = 0;
    for (char c : to_string(n)) {
        int d = c - '0';
        sum += d * d;
    }
    return sum;
}

int chain(int n) {
    while (n != 89 && n != 1) {
        n = sum_squared_digits(n);
    }
    return n;
}

int main() {
    int upper = 10000000, count = 0;
    for (int i = 1; i <= upper; ++i) {
        if (chain(i) == 89)
            ++count;
    }

    printf("Starting with the numbers [1, %d], %d arrives at 89.\n", upper, count);

    return 0;
}
