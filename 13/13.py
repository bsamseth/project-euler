"""
Work out the first ten digits of the sum of the following one-hundred 50-digit numbers.

Numbers in file data.dat
"""
numbers = []
with open("data.dat", 'r') as f:
    for line in f.readlines():
        numbers.append(float(line))

s = sum(numbers)
print "Sum = %d" % s
print "First 10 digits = %s" % str(s)[:11].replace('.', '')
