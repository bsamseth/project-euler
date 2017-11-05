"""
The primes 3, 7, 109, and 673, are quite remarkable. By taking any two
primes and concatenating them in any order the result will always be prime. For
example, taking 7 and 109, both 7109 and 1097 are prime. The sum of these four
primes, 792, represents the lowest sum for a set of four primes with this
property.

Find the lowest sum for a set of five primes for which any two primes
concatenate to produce another prime.

Solution comment: Ooh so slow, but works after a good long time (~ 1min).
                  Recursively try to add a new prime to a set, trying all
                  primes up to some fixed limit (set by guessing). If it does
                  not work with the starting prime, remove that prime from
                  consideration and build a new set with the next prime.

                  Important note is that primes list is not used for checking
                  primality, as the primes list would need to be *much* bigger
                  in order to check the concatenated candidates.
"""

from projecteuler.prime import primes_up_to, isprime
from itertools import permutations

primes = list(primes_up_to(10000))

def add_prime_to_list(lst, size=5):
    if len(lst) >= size:
        return lst
    for p in primes:
        if all(isprime(int('{}{}'.format(*pair))) for pair in permutations(lst+[p], 2)):
            filled_lst = add_prime_to_list(lst + [p], size=size)
            if filled_lst:
                return filled_lst
    return None

lst = None
while not lst:
    lst = add_prime_to_list([primes.pop(0)])

print(lst, sum(lst))

