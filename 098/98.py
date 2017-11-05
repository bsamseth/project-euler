"""
By replacing each of the letters in the word CARE with 1, 2, 9, and 6
respectively, we form a square number: 1296 = 362. What is remarkable is that,
by using the same digital substitutions, the anagram, RACE, also forms a square
number: 9216 = 962. We shall call CARE (and RACE) a square anagram word pair
and specify further that leading zeroes are not permitted, neither may a
different letter have the same digital value as another letter.

Using words.txt (right click and 'Save Link/Target As...'), a 16K text file
containing nearly two-thousand common English words, find all the square
anagram word pairs (a palindromic word is NOT considered to be an anagram of
itself).

What is the largest square number formed by any member of such a pair?

NOTE: All anagrams formed must be contained in the given text file.

Solution comment: Slow. Try anagrams of decreasing length, as the largest anagram square
                  must correspond to the longest words. Just brute force from there.
                  Spends the majority of the time looking for squares in the larger
                  words, when it gets to ~5 chars it is quite quick.
"""
import csv
from collections import defaultdict
from itertools import permutations
from math import sqrt

def anagram(a, b):
    counts = defaultdict(int)
    for c in a:
        counts[c] += 1
    for c in b:
        counts[c] -= 1
    for c in counts.values():
        if c:
            return False
    return True
def map_word(word, ordering):
    s = ''
    for c in word:
        s += str(ordering[c])
    return int(s)
def is_square(n):
    root = int(sqrt(n) + 0.5)
    return root * root == n

def find_largest_anagram(all_words):
    length = len(max(all_words, key=len))
    while length > 1:
        words = [word for word in all_words if len(word) == length]
        anagrams = []
        for i in range(len(words)):
            for j in range(i+1, len(words)):
                word, other = words[i], words[j]
                if word != other and anagram(word, other):
                    anagrams.append((word, other))
        for word, other in anagrams:
            print('Considering:', word, other)
            letters = set(word)
            for perm in permutations(range(10), len(letters)):
                ordering = dict(zip(letters, perm))
                if ordering[word[0]] == 0 or ordering[other[0]] == 0: continue
                for num in (map_word(word, ordering), map_word(other, ordering)):
                    if not is_square(num):
                        break
                else:
                    return word, other, map_word(word, ordering), map_word(other, ordering)
        length -= 1


with open('p098_words.txt', 'r') as f:
    all_words = list(csv.reader(f))[0]

print(find_largest_anagram(all_words))

