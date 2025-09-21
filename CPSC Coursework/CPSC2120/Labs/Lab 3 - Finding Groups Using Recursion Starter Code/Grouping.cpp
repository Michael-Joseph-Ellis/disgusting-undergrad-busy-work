/*
 * Name: Michael Joseph Ellis 
 * Date Submitted: Feb 17, 2025
 * Lab Section: 004
 * Assignment Name: Finding Groups Using Recursion
 */

#include "Grouping.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

//Implement the (parameterized) constructor and findGroup functions below
Grouping::Grouping(string fileName) {
    ifstream inFile(fileName);
    if (!inFile) {
        cerr << "Error opening file." << endl;
        return;
    }
    
    // Read the file into grid
    for (int i = 0; i < 10; i++) {
        string line;
        std::getline(inFile, line);
        for (int j = 0; j < 10; j++) {
            grid[i][j] = (line[j] == '.') ? 0 : 1;
        }
    }
    inFile.close();
    
    // Find groups using findGroup function
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (grid[i][j] == 1) { // this is if we found a filled square
                vector<GridSquare> group; 
                findGroup(i, j, group);
                groups.push_back(group);
            }
        }
    }
}

// Recursive function to find groups
void Grouping::findGroup(int r, int c, vector<GridSquare>& group) {
    // Base case: Out of bounds or already visited
    if (r < 0 || r >= 10 || c < 0 || c >= 10 || grid[r][c] == 0) {
        return;
    }
    // Mark the square as they arevisited
    grid[r][c] = 0;
    
    // Add to current group
    group.push_back(GridSquare(r, c));
    
    // Recur in four possible directions
    findGroup(r - 1, c, group); // Up
    findGroup(r + 1, c, group); // Down
    findGroup(r, c - 1, group); // Left
    findGroup(r, c + 1, group); // Right
}

//Simple main function to test Grouping
//Be sure to comment out main() before submitting
// int main()
// {
//     Grouping input1("input1.txt");
//     input1.printGroups();
    
//     return 0;
// }

//Do not modify anything below

GridSquare::GridSquare() : row(0), col(0) {} //Default constructor, (0,0) square

GridSquare::GridSquare(int r, int c) : row(r), col(c) {} //(r,c) square

//Compare with == operator, used in test cases
bool GridSquare::operator== (const GridSquare r) const
{
    if ((row == r.row) && (col == r.col))
    {
        return true;
    }
    return false;
}

int GridSquare::getRow() //return row value
{
    return row;
}

int GridSquare::getCol() //return column value
{
    return col;
}

//Output using << operator, used in Grouping::printGroups()
//Function definition for <ostream> << <GridSquare>
ostream& operator<< (ostream& os, const GridSquare obj)
{
    os << "(" << obj.row << "," << obj.col << ")";
    return os;
}

Grouping::Grouping() : grid{},groups() {} //Default constructor, no groups

void Grouping::printGroups() //Displays grid's groups of squares
{
    for(int g=0; g<groups.size(); g++)
    {
        cout << "Group " << g+1 << ": ";
        for(int s=0; s<groups[g].size(); s++)
        {
            cout << " " << groups[g][s];
        }
        cout << endl;
    }
}

vector<vector<GridSquare>> Grouping::getGroups() //Needed in unit tests
{
    return groups;
}