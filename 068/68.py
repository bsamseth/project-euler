# Solution comment: Best solved by hand. This a little messy and brute force...
from itertools import permutations

dig_sum = lambda seq: sum(int(i) for i in seq)
toInt = lambda s: int(''.join(s))

biggest = 0
for perm in permutations(str(i) for i in range(1, 11)):
    digits = (i for i in perm)
    s = [next(digits) for _ in range(3)]
    same_sum = dig_sum(s)
    concat = s[:]
    ss = s
    for _ in range(3):
        ss = [next(digits), ss[-1], next(digits)]
        concat += ss[:]
        if dig_sum(ss) != same_sum or toInt(s) > toInt(ss):
            break
    else:
        ss = [next(digits), ss[-1], s[1]]
        concat += ss[:]
        if dig_sum(ss) == same_sum and toInt(s) < toInt(ss)\
                and len(''.join(concat)) == 16:
            print(''.join(concat))
            biggest = max(biggest, toInt(concat))
print('Biggest:', biggest)


