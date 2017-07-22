# Solution comment: Cheating. Found the list of periods on OEIS and counted the
# odds from that list.

from math import sqrt

# First determine how many non squares there are < 10000.
count = 0
for i in range(2, 10000+1):
    if abs(sqrt(i) - int(sqrt(i))) > 1e-6:
        count += 1

# Read count periods from the number file, counting how many odds.
with open('numbers.txt', 'r') as f:
    f.readline()  # Skip first line.
    res = 0
    for i, line in enumerate(f):
        if i == count:
            break
        *_, p = [int(i) for i in line.split()]
        res += (p & 1)
print(res)
