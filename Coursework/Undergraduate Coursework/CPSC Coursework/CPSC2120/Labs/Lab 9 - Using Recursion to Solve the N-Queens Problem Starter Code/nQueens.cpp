/*
 * Name: Michael Joseph Ellis
 * Date Submitted: 4/14/2025
 * Lab Section: 004
 * Assignment Name: Using Recursion to Solve the N-Queens Problem
 */

#include <iostream>
#include <vector>

using namespace std;

// Helper recursive function to count solutions
void solve(int row, int n, vector<bool>& cols, vector<bool>& diag1, vector<bool>& diag2, int& count) {
    if (row == n) {
        count++;
        return;
    }
    for (int col = 0; col < n; ++col) {
        if (cols[col] || diag1[row - col + n - 1] || diag2[row + col])
            continue;
        // Place queen
        cols[col] = diag1[row - col + n - 1] = diag2[row + col] = true;
        solve(row + 1, n, cols, diag1, diag2, count);
        // Remove queen (backtrack)
        cols[col] = diag1[row - col + n - 1] = diag2[row + col] = false;
    }
}

//Uses recursion to count how many solutions there are for
//placing n queens on an nxn chess board
int nQueens(int n)
{
    if (n <= 0) return 0;
    int count = 0;
    vector<bool> cols(n, false);              // Column occupied?
    vector<bool> diag1(2 * n - 1, false);     // / diagonal
    vector<bool> diag2(2 * n - 1, false);     // \ diagonal
    solve(0, n, cols, diag1, diag2, count);
    return count;
}

// int main()
// {
//     cout << "1: " << nQueens(1) << endl;
//     cout << "2: " << nQueens(2) << endl;
//     cout << "3: " << nQueens(3) << endl;
//     cout << "4: " << nQueens(4) << endl;
//     cout << "5: " << nQueens(5) << endl;
//     cout << "6: " << nQueens(6) << endl;
//     cout << "7: " << nQueens(7) << endl;
//     cout << "8: " << nQueens(8) << endl;
//     cout << "9: " << nQueens(9) << endl;
//     cout << "10: " << nQueens(10) << endl;
//     cout << "11: " << nQueens(11) << endl;
//     cout << "12: " << nQueens(12) << endl;
//     return 0;
// }