"""
The number 512 is interesting because it is equal to the sum of its digits
raised to some power: 5 + 1 + 2 = 8, and 83 = 512. Another example of a number
with this property is 614656 = 284.

We shall define an to be the nth term of this sequence and insist that a number
must contain at least two digits to have a sum.

You are given that a2 = 512 and a10 = 614656.

Find a30.


Solution comment: Well, this number is on oeis.org. So kinda cheating, but...
Other solution is simple brute force. The search space was just manually set quite a
bit larger than what is set now, then just reduced a bit afterwards. Terms not generated
in order, so need to generate some more terms than just 30.
"""


# from urllib.request import urlopen
# data = urlopen('https://oeis.org/A023106/b023106.txt').read().splitlines()
# answer = int(data[30 + 9].split()[-1])  # Skip first 10 single digit terms.
# print('Answer:', answer)


from time import time

def digit_sum(n):
    s = 0
    while n:
        s += n % 10
        n //= 10
    return s

t0 = time()
terms = []
for b in range(2, 100):
    x = b
    for _ in range(2, 30):
        x *= b
        if digit_sum(x) == b:
            terms.append(x)
    if len(terms) >= 40:
        break

print('Answer:', sorted(terms)[29])
print('Execution time: {:.3f} ms'.format((time() - t0) * 1e3))
