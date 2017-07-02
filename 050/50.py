# coding=utf-8
"""
The prime 41, can be written as the sum of six consecutive primes:

41 = 2 + 3 + 5 + 7 + 11 + 13
This is the longest sum of consecutive primes that adds to a prime below one-hundred.

The longest sum of consecutive primes below one-thousand that adds to a prime, contains 21 terms, and is equal to 953.

Which prime, below one-million, can be written as the sum of the most consecutive primes?

Solution comment:
Bad. Solution found by assuming the solution to be in the very upper part of the
prime list, and runs in about 2 mins. Should implement a cumulative sum list, so that
the adding is not needed to be done over and over.
"""

from projecteuler.prime import primes_up_to


upper = int(1e6)

primes = primes_up_to(upper)
search_above = int(0.995*len(primes))

prime_sums = { p: 0 for p in primes }
for i, p in enumerate(primes):
    if i < search_above:
        continue
    for start in xrange(i-1):
        s = 0
        for j in xrange(start, i):
            s += primes[j]
            if s == p:
                prime_sums[p] = max(j-start + 1, prime_sums[p])
                break
            elif s > p:
                break

prime_sums = { key: prime_sums[key] for key in prime_sums if prime_sums[key] != 0 }
max_prime = max(prime_sums, key=prime_sums.get)
print max_prime, prime_sums[max_prime]
