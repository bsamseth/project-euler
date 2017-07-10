/*
 The cube, 41063625 (345^3), can be permuted to produce two other cubes: 56623104 (384^3) and
 66430125 (405^3). In fact, 41063625 is the smallest cube which has exactly three permutations
 of its digits which are also cube.
 
 Find the smallest cube for which exactly five permutations of its digits are cube.
 
 Solution comment: Initial solution was pure brute force. That worked, but the following solution
 is *much* faster. Inspired from http://www.mathblog.dk/project-euler-62-cube-five-permutations/.
 */

#include <iostream>
#include <map>
using namespace std;

/* 
 Hash function to map all anagrams to the same number.
 Permutes the number into the maximum number that can be 
 made with the same digits.
 */
long to_largest_anagram(long n) {
    int digit_counts[10] = {0};
    while (n) { ++digit_counts[n % 10]; n /= 10; }
    
    long res = 0;
    for (int i = 9; i >= 0; --i)
        for (int j = 0; j < digit_counts[i]; ++j)
            res = res * 10 + i;
    return res;
}

struct Cube {
    long smallest;  // Smallest cube anagram.
    long count;     // Number of anagrams of smallest found.
};

int main() {
    map<long, struct Cube> cube_counts;
    
    long i = 0;
    while (++i) {
        long hash = to_largest_anagram(i*i*i);
        if (cube_counts.count(hash) == 0) {  // First time seen.
            struct Cube cube = {i*i*i, 1};
            cube_counts[hash] = cube;
        } else if (++cube_counts[hash].count >= 5) {
            cout << "Smallest cube with 5 anagrams: " << cube_counts[hash].smallest << endl;
            return 0;
        }
    }
}

