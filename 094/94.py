"""
It is easily proved that no equilateral triangle exists with integral length
sides and integral area. However, the almost equilateral triangle 5-5-6 has an
area of 12 square units.

We shall define an almost equilateral triangle to be a triangle for which two
sides are equal and the third differs by no more than one unit.

Find the sum of the perimeters of all almost equilateral triangles with
integral side lengths and area and whose perimeters do not exceed one billion
(1,000,000,000).


Solution comment: Instant time.
                  Area is A = ((a ± 1) * h) / 2, and from Pythagoras
                  a^2 = ((a ± 1)/2)^2 + h^2
            =>    ((3a ± 1)/2)^2 - 3h^2 = 1
            =>    x^2 - 3y^2 = 1  -> Bell equation.
                  Wolfram Alpha then helpfully supplies integer solutions, with
                  x_n = 1/2 ((2 - √3)**n + (2 + √3)**n))
                  Only n >= 2 are valid for us. Then get side length from
                  a = (2x ± 1) / 3,
                  making sure to pick the sign that makes the division work.
"""


from math import sqrt

upper = int(1e9)
s = 0
sqrt3 = sqrt(3)
n = 2
while True:
    x = int(round(0.5 * ((2 - sqrt3)**n + (2 + sqrt3)**n)))
    a = 2*x-1
    if a >= upper + 1:
        break
    if a % 3 == 0:
        a = a//3
        s += 3*a - 1
        print(a, a, a-1)
    else:
        a = (a + 2) // 3
        s += 3*a + 1
        print(a, a, a+1)
    n += 1
print(s)
