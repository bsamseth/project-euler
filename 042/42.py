# coding=utf-8
"""
The nth term of the sequence of triangle numbers is given by, tn = ½n(n+1); so the first ten triangle numbers are:

1, 3, 6, 10, 15, 21, 28, 36, 45, 55, ...

By converting each letter in a word to a number corresponding to its alphabetical position and adding these values we form a word value. For example, the word value for SKY is 19 + 11 + 25 = 55 = t10. If the word value is a triangle number then we shall call the word a triangle word.

Using words.txt (right click and 'Save Link/Target As...'), a 16K text file containing nearly two-thousand common English words, how many are triangle words?

Solution comment:
Given a maximum word value t, we need to compute the sqrt(1+8t)/2 + 1
first triangle numbers (from abc-formula on t(n)).

Then simply count the number of times the word value is in the set of
triangle numbers.
"""
from math import sqrt

alphabet = 'abcdefghijklmnopqrstuvwxyz'.upper()
alphvalue = { char: i+1 for i, char in enumerate(alphabet)}

with open('p042_words.txt', 'r') as f:
    data = f.read()
    words = data.split('","')
    words[0], words[-1] = words[0][1:], words[-1][:-1]

word_values = [ sum((alphvalue[char] for char in word)) for word in words ]
max_word = max(word_values)
max_n = int(sqrt(1 + 8*max_word) // 2) + 1
triangle_numbers = { n*(n+1)/2 for n in xrange(max_n+1) }

print sum(wv in triangle_numbers for wv in word_values)
