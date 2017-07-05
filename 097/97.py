

def two_to_n_mod_10_to_m(n, m):
    """Successive squaring. Very fast and handles very large numbers.

    1. Rewrite 2^n so that n is a sum of powers of two.
    2. Create a list of powers 2^(2^i) mod 10^m, by repeatedly squaring the prior result.
    3. Combine, with multiplication mod 10^m, the powers in the list that make up 2^n.

    Based on: http://www.exploringbinary.com/how-to-find-the-last-digits-of-a-positive-power-of-two/
    """
    mod = 10**m

    # Step 1. one_bits is a list of the powers (exponents) of two that make up n.
    one_bits = [i for i, bit in enumerate(reversed(bin(n)[2:])) if bit == '1']

    # Step 2. powers_of_two_mod is a list of 2^(2^i) mod 10^m with i
    #         such that 2^i <= n for all i.
    powers_of_two_mod = []
    power, number = 1, 2
    while power <= n:
        powers_of_two_mod.append(number)
        power, number = power*2, number**2 % mod

    # Step 3. 2^n === prod(powers_of_two[i]) mod 10^m.
    res = 1
    for b in one_bits:
        res = (res * powers_of_two_mod[b]) % mod
    return res

def alt1(n, m):
    """Build up number, taking modulo as you go. Slow but simple."""
    mod = 10**m
    res = 1
    for _ in range(n):
        res = (res << 1) % mod
    return res

def alt2(n, m):
    """As simple as it gets, and fast for somewhat reasonable values of n."""
    return 2**n % 10**m

print((28433 * two_to_n_mod_10_to_m(7830457, 10) + 1) % 10**10)
print((28433 * alt1(7830457, 10) + 1) % 10**10)
print((28433 * alt2(7830457, 10) + 1) % 10**10)
