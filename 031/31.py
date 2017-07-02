# coding=utf-8
"""
In England the currency is made up of pound, £, and pence, p, and there are eight coins in general circulation:

1p, 2p, 5p, 10p, 20p, 50p, £1 (100p) and £2 (200p).
It is possible to make £2 in the following way:

1×£1 + 1×50p + 2×20p + 1×5p + 1×2p + 3×1p
How many different ways can £2 be made using any number of coins?

Solution comment:

Decomposition question:
If we want to change n pennies, and we give one coin of x pennies,
how many ways can we give back the remaining n-x pennies using only
coins of x or smaller?

`ways` is an array containing how many ways you can give back i pennies,
using the coins available.

In the loop we give back a coin of x, then use the previously known
answers to find how many ways we can give back the remainder.
"""
from numpy import zeros

def coin_combinations(target, coins):
    ways = zeros(target+1, dtype=int)
    ways[0] = 1

    for coin in coins:
        for j in xrange(coin, target+1):
            ways[j] += ways[j - coin]
    return ways[-1]

target = 200
coins = [1, 2, 5, 10, 20, 50, 100, 200]
print coin_combinations(target, coins)
