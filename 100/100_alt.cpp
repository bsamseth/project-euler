/*
Alternative solution comment:
Iterative solution generator, based on http://www.alpertron.com.ar/QUAD.HTM
Equally fast, as sqrt and pow are quite slow.
*/

#include <iostream>
using namespace std;

int main() {
    long lower = 1e12;
    long a = 15;
    long n = 21;
    while (n < lower) {
        long tmp_a = 3 * a + 2 * n - 2;
        long tmp_n = 4 * a + 3 * n - 3;
        a = tmp_a;
        n = tmp_n;
    }
    printf("%ld\n", a);
    return 0;
}
