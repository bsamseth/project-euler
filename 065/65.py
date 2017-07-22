# Solution comment: Note the sequence of numerators, n_i
#      2, 3, 8, 11, 19, 87, 106, 193, 1264, 1457,...
# With the sequence of a_i:
#            2,  1,  1,  4,   1,   1,   6,     1,...
# For n_i, i >= 2, we have
#            n_i = a_i * n_{i-1} + n_{i-2}

# Start with n_1 and n_2, compute n_3... n_100 (98 iterations)
np, n = 2, 3
for i in range(3, 100+1):
    a_i = 2 * (i//3) if i % 3 == 0 else 1
    np, n = n, a_i * n + np

dig_sum = 0
while n:
    dig_sum += n % 10
    n //= 10

print('Sum of the digits in the numerator of the 100th convergent\n'
      'of the continued fraction of e:', dig_sum)

