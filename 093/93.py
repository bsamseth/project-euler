"""
By using each of the digits from the set, {1, 2, 3, 4}, exactly once, and
making use of the four arithmetic operations (+, −, *, /) and
brackets/parentheses, it is possible to form different positive integer
targets.

For example,

        8 = (4 * (1 + 3)) / 2
        14 = 4 * (3 + 1 / 2)
        19 = 4 * (2 + 3) − 1
        36 = 3 * 4 * (2 + 1)

Note that concatenations of the digits, like 12 + 34, are not allowed.

Using the set, {1, 2, 3, 4}, it is possible to obtain thirty-one different
target numbers of which 36 is the maximum, and each of the numbers 1 to 28 can
be obtained before encountering the first non-expressible number.

Find the set of four distinct digits, a < b < c < d, for which the longest set
of consecutive positive integers, 1 to n, can be obtained, giving your answer
as a string: abcd.

Solution comment: ~1.2s. Brute force, itertools bonanza. Placement of brackets can be
                  thought of as choosing the order of operations. With four
                  numbers and three operations, there are five possibly different
                  ways to place the brackets, for every permutation of the numbers.
                  Each of these are just typed out in the code below. The code
                  runs for every unique combination of the digits, then for every
                  permutation of them, and for every possible set of operands.
                  In the latter, duplicate operations are allowed, so product is used.
                  Streaks counted, and the maximum printed.
"""


from itertools import permutations, product, count, combinations

add = lambda a, b: a+b
sub = lambda a, b: a-b
mul = lambda a, b: a*b
div = lambda a, b: a/b if b != 0 else float('inf')
ops = [add, sub, mul, div]

streaks = dict()
for numbers in combinations(range(10), 4):
    sums = set()
    for a, b, c, d in permutations(numbers, 4):
        for op1, op2, op3 in product(ops, repeat=3):
            sums.add(op1(a, op2(b, op3(c, d))))
            sums.add(op1(a, op3(op2(b,c), d)))
            sums.add(op3(op2(op1(a, b), c), d))
            sums.add(op3(op1(a, op2(b, c)), d))
            sums.add(op2(op1(a,b), op3(c, d)))
    streak = 0
    for i in count(1):
        if not i in sums:
            break
        streak += 1

    streaks[''.join(str(d) for d in numbers)] = streak
print(max(streaks.items(), key=lambda item: item[1]))
