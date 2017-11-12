/*
If a box contains twenty-one coloured discs, composed of fifteen blue discs and
six red discs, and two discs were taken at random, it can be seen that the
probability of taking two blue discs, P(BB) = (15/21)×(14/20) = 1/2.

The next such arrangement, for which there is exactly 50% chance of taking two
blue discs at random, is a box containing eighty-five blue discs and
thirty-five red discs.

By finding the first arrangement to contain over 1012 = 1,000,000,000,000 discs
in total, determine the number of blue discs that the box would contain.

Solution comment: Problem to solve is
                    b/n * (b-1)/(n-1) = 1/2
                  This can be solved analytically by Wolfram Alpha, specifying
                  'over the integers' after this expression. Then just a matter of
                  chosing a solution that has total discs > 1e12, which can be done
                  by trial and error or by any equation solver.
*/

#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int x = 17;
    double sqrt2 = sqrt(2);
    long long blue = ((2 + sqrt2)*pow(3-2*sqrt2, x)
                      + (2 - sqrt2)*pow(3+2*sqrt2, x) + 4)/8 + 0.5;  // +0.5 to ensure correct rounding.
    printf("%lld\n", blue);
    return 0;
}
