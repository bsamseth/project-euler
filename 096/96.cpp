/*
Su Doku (Japanese meaning number place) is the name given to a popular puzzle
concept. Its origin is unclear, but credit must be attributed to Leonhard Euler
who invented a similar, and much more difficult, puzzle idea called Latin
Squares. The objective of Su Doku puzzles, however, is to replace the blanks
(or zeros) in a 9 by 9 grid in such that each row, column, and 3 by 3 box
contains each of the digits 1 to 9. Below is an example of a typical starting
puzzle grid and its solution grid.  A well constructed Su Doku puzzle has a
unique solution and can be solved by logic, although it may be necessary to
employ "guess and test" methods in order to eliminate options (there is much
contested opinion over this). The complexity of the search determines
the difficulty of the puzzle; the example above is considered easy because it
can be solved by straight forward direct deduction.

The 6K text file, sudoku.txt (right click and 'Save Link/Target As...'),
contains fifty different Su Doku puzzles ranging in difficulty, but all
with unique solutions (the first puzzle in the file is the example above).

By solving all fifty puzzles find the sum of the 3-digit numbers found in the
top left corner of each solution grid; for example, 483 is the 3-digit number
found in the top left corner of the solution grid above.
*/


#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

const int N = 9;
const int SQRT_N = sqrt(N);
int grid[N][N];


/**
 * Return true if c can be placed at grid[row][col].
 */
bool allowed(int row, int col, int c) {
    // Check row/col.
    for (int i = 0; i < N; ++i) {
        if (grid[i][col] == c or grid[row][i] == c)
            return false;
    }
    // Check box.
    int box_row = row - row % SQRT_N;
    int box_col = col - col % SQRT_N;
    for (int i = box_row; i < box_row + SQRT_N; ++i) {
        for (int j = box_col; j < box_col + SQRT_N; ++j)
            if (grid[i][j] == c)
                return false;
    }
    return true;
}


int solve(int row, int col) {
    if (row == N - 1 and col == N - 1) {
        // Solved!
        int score = 0;
        for (int j = 0; j < SQRT_N; ++j)
            score += grid[0][j] * pow(10, SQRT_N - j - 1);
        return score;
    }

    int incr_row = row + (col + 1)/N;
    int incr_col = (col + 1) % N;
    if (grid[row][col]) {
        // Prefilled cell, continue.
        return solve(incr_row, incr_col);
    }
    else {
        // Empty cell, try every possibility.
        for (int c = 1; c <= 9; ++c) {
            if (!allowed(row, col, c)) continue;
            // Set and solve rest.
            grid[row][col] = c;
            int solved = solve(incr_row, incr_col);
            if (solved) return solved; // Terminate after first solution.
        }
        grid[row][col] = 0;  // Reset
        return 0;
    }
}

int main() {
    ifstream f("/Users/bendik/drive/project-euler/096/p096_sudoku.txt");
    char line[N+1];

    int sum = 0;
    for (int puzzle = 0; puzzle < 50; ++puzzle) {
        // Load puzzle.
        f.getline(line, N+1);
        for (int i = 0; i < N; ++i) {
            f.getline(line, N+1);
            for (int j = 0; j < N; ++j) {
                grid[i][j] = line[j] - '0';
            }
        }
        // Solve.
        sum += solve(0, 0);
    }
    printf("%d\n", sum);
    return 0;
}
