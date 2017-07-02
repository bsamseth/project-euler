"""
Using names.txt (right click and 'Save Link/Target As...'), a 46K text file containing over five-thousand first names, begin by sorting it into alphabetical order. Then working out the alphabetical value for each name, multiply this value by its alphabetical position in the list to obtain a name score.

For example, when the list is sorted into alphabetical order, COLIN,
which is worth 3 + 15 + 12 + 9 + 14 = 53, is the 938th name in the list.
So, COLIN would obtain

a score of 938 x 53 = 49714.

What is the total of all the name scores in the file?
"""
with open("p022_names.txt", 'r') as f:
    names = f.read()

names = names.split('","')
names[0] = names[0].replace('"', '')
names[-1] = names[-1].replace('"', '')
names.sort()


alph = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
alphValue = { char: value for (char, value) in zip(alph, range(1, len(alph)+1))}

s = 0
for i, name in enumerate(names):
    alphScore = sum([alphValue[char] for char in name])
    placeScore = i+1
    s += alphScore * placeScore

print 'total =', s
