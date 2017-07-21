# For a number written in Roman numerals to be considered valid there are basic
# rules which must be followed. Even though the rules allow some numbers to be
# expressed in more than one way there is always a "best" way of writing a
# particular number.
#
# For example, it would appear that there are at least six ways of writing the
# number sixteen:
#
# IIIIIIIIIIIIIIII
# VIIIIIIIIIII
# VVIIIIII
# XIIIIII
# VVVI
# XVI
#
# However, according to the rules only XIIIIII and XVI are valid, and the last
# example is considered to be the most efficient, as it uses the least number of
# numerals.
#
# The 11K text file, roman.txt (right click and 'Save Link/Target As...'),
# contains one thousand numbers written in valid, but not necessarily minimal,
# Roman numerals; see About... Roman Numerals for the definitive rules for this
# problem.
#
# Find the number of characters saved by writing each of these in their minimal
# form.
#
# Note: You can assume that all the Roman numerals in the file contain no more
# than four consecutive identical units.
#
#
# Solution comment: Number->Roman covered by roman package. The package does not
# handle the bad roman numerals, so Roman->Number has to be made to work with this.

def fromRoman(r):
    """Return the numeric value of a valid roman numeral."""
    # Handle subtractions by trying to match two characters first.
    # If this fails, match only one character.
    romanMap = dict((('M', 1000), ('CM', 900), ('D', 500),
                     ('CD', 400), ('C', 100), ('XC', 90),
                     ('L', 50), ('XL', 40), ('X', 10),
                     ('IX', 9), ('V', 5), ('IV', 4), ('I', 1)))
    num, i = 0, 0
    try:
        while i < len(r) - 1:
            if r[i:i+2] in romanMap:
                num += romanMap[r[i:i+2]]
                i += 2
            else:
                num += romanMap[r[i]]
                i += 1
        if i < len(r):
            num += romanMap[r[i]]
        return num
    except KeyError as e:
        raise ValueError('Bad roman numeral: ' + r)

if __name__ == "__main__":
    import roman
    with open('roman.txt', 'r') as f:
        lines = f.read().strip().split('\n')
        numbers = [fromRoman(line.strip()) for line in lines]
        inRoman = ''.join(roman.toRoman(n) for n in numbers)
        print('Characters saved:', len(''.join(lines)) - len(inRoman))






