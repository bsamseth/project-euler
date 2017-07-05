/*
 Comparing two numbers written in index form like 2^11 and 3^7 is not difficult,
 as any calculator would confirm that 2^11 = 2048 < 3^7 = 2187.
 
 However, confirming that 632382^518061 > 519432^525806 would be much more difficult,
 as both numbers contain over three million digits.
 
 Using base_exp.txt, a 22K text file containing one thousand lines with a base/exponent 
 pair on each line, determine which line number has the greatest numerical value.
 
 NOTE: The first two lines in the file represent the numbers in the example given above.
 
 Solution comment: If a > b then log a > log b for any positive integer.
 */

#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;


int main() {
    std::ifstream infile("p099_base_exp.txt", ifstream::in);

    int lineno = 1, max_line = 0;
    double max = -1, numb;
    int base, exponent;
    char delim;

    while (infile >> base >> delim >> exponent) {
        numb = exponent * log10(base);
        if (numb > max) {
            max = numb;
            max_line = lineno;
        }
        ++lineno;
    }
    printf("The largest base-exponent pair is on line %d\n", max_line);
    infile.close();
    
    return 0;
}
