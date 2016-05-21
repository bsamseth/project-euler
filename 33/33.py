# coding=utf-8
"""
The fraction 49/98 is a curious fraction, as an inexperienced mathematician in attempting to simplify it may incorrectly believe that 49/98 = 4/8, which is correct, is obtained by cancelling the 9s.

We shall consider fractions like, 30/50 = 3/5, to be trivial examples.

There are exactly four non-trivial examples of this type of fraction, less than one in value, and containing two digits in the numerator and denominator.

If the product of these four fractions is given in its lowest common terms, find the value of the denominator.

Solution comment:
Loop over all fractions less than one with two digits in num/den,
ignoring factors of ten. If present, remove common digit, and see
if the fraction is the same.
"""
from fractions import Fraction

fracs = []
for denominator in xrange(12, 100):
    if denominator % 10 == 0:
        continue
    for numerator in xrange(11, denominator):
        num_dig = {dig for dig in str(numerator)}
        den_dig = {dig for dig in str(denominator)}
        if (num_dig & den_dig):
            common_dig = (num_dig & den_dig).pop()
            org_frac = Fraction(numerator, denominator)
            num_short = int(str(numerator).replace(common_dig, '', 1))
            den_short = int(str(denominator).replace(common_dig, '', 1))
            new_frac = Fraction(num_short, den_short)
            if str(org_frac) == str(new_frac):
                print numerator, denominator
                fracs.append(org_frac)

prod = Fraction(1, 1)
for frac in fracs:
    prod *= frac
print prod
