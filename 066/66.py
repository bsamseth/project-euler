# Originaly solved by OEIS lookup. This solution inspired from mathblog.dk.
# The minimal solution to the Pell Equation is (x, y) = (n_i, d_i) where
# n_i/d_i is the i-th convergent of sqrt(D).


from math import sqrt

def find_cf(x):
    """Return successive convergents of sqrt(x) as n_i/d_i.
       Square numbers return only the pair (int(sqrt(x)), 1)."""
    limit = int(sqrt(x))
    if limit * limit == D: return limit, 1
    m, d, a = 0, 1, limit
    num_prev, num = 1, a
    den_prev, den = 0, 1
    while True:
        m = d * a - m
        d = (D - m*m) // d
        a = (limit + m) // d

        num_prev, num = num, a*num + num_prev
        den_prev, den = den, a*den + den_prev

        yield num, den

result = 0;
pmax = 0;
for D in range(2, 1000+1):
    limit = int(sqrt(D))
    if limit * limit == D: continue

    for num, den in find_cf(D):
        if num*num - D*den*den == 1:
            break
    if num > pmax:
        pmax = num
        result = D
print(result)
