from itertools import count

def r(a, n):
    return int((a+1)**n + (a-1)**n) % (a*a)

def find_cycle(seq):
    if len(seq) & 1:
        return None
    split = len(seq) // 2
    if seq[:split] == seq[split:]:
        return seq[split:]
    else:
        return None

r_sum = 0
for a in range(3, 1000+1):
    print('a = {} -> r_sum = {}                           '.format(a, r_sum), end='\r')
    seq = []
    for n in count():
        seq.append(r(a, n))
        cycle = find_cycle(seq)
        if cycle:
            r_sum += max(cycle)
            break

print('\n', r_sum)

