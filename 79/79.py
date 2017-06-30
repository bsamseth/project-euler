"""
A common security method used for online banking is to ask the user for three random characters from a passcode. For example, if the passcode was 531278, they may ask for the 2nd, 3rd, and 5th characters; the expected reply would be: 317.

The text file, keylog.txt, contains fifty successful login attempts.

Given that the three characters are always asked for in order, analyse the file so as to determine the shortest possible secret passcode of unknown length.
"""


with open('input.txt', 'r') as f:
    seqs = f.read().strip().split('\n')

    # Dict of symbols with a set of symbols less than itself.
    symbols = { d : set() for d in set(''.join(seqs)) }

    for seq in seqs:
        for i in range(1, len(seq)):
            symbols[seq[i]].update(seq[:i])

    print(''.join(pair[0] for pair in sorted(symbols.items(), key=lambda i: len(i[1]))))



