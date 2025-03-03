/*
 * Name: Michael Ellis
 * Date Submitted: 3/10/2025
 * Lab Section: 004 
 * Assignment Name: Finding the Closest Pair of Points
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>

using namespace std;

struct Point
{
    double x;
    double y;
};

// Function to compute the distance between two points
double computeDistance(const Point& p1, const Point& p2) {
  return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

/*Implement the following function
  Reads in a file specified by the parameter
  Format of file: #of points on first line
                  remaining (#of points) lines: x-value and y-value of point
                  one point per line
                  x-value and y-value are double-precision values and
                  bounded by the unit square 0.0 <= x,y < 1.0
  Should use "spatial hashing" where the #of cells scales with the #of points
  and find the distance between the closest pair of points which will be
  returned as a double type value
*/
double closestPair(string filename) {
  ifstream file(filename);
  if (!file) {
      cerr << "Error opening file." << endl;
      return -1;
  }

  int n;
  file >> n;

  // Determine b (number of divisions for the grid)
  /*
  * Choosing b = sqrt(n) is a good heuristic because:
  * - It ensures a balance between the number of cells and the number of points per cell.
  * - Too small a b results in too many points per cell, making comparisons inefficient.
  * - Too large a b results in many empty cells, leading to redundant comparisons with adjacent cells.
  */
  int b = sqrt(n);  // A reasonable choice balancing grid size and point density
  vector<vector<vector<Point>>> grid(b, vector<vector<Point>>(b));

  // Read points and hash them into grid
  vector<Point> points(n);
  for (int i = 0; i < n; ++i) {
      file >> points[i].x >> points[i].y;
      int cellX = min(b - 1, static_cast<int>(points[i].x * b));
      int cellY = min(b - 1, static_cast<int>(points[i].y * b));
      grid[cellX][cellY].push_back(points[i]);
  }
  file.close();

  // Find the closest pair
  double minDist = numeric_limits<double>::max();
  for (int i = 0; i < b; ++i) {
      for (int j = 0; j < b; ++j) {
          // Compare points in the current cell
          for (size_t p1 = 0; p1 < grid[i][j].size(); ++p1) {
              for (size_t p2 = p1 + 1; p2 < grid[i][j].size(); ++p2) {
                  minDist = min(minDist, computeDistance(grid[i][j][p1], grid[i][j][p2]));
              }
          }
          // Compare with neighboring cells
          for (int di = -1; di <= 1; ++di) {
              for (int dj = -1; dj <= 1; ++dj) {
                  int ni = i + di, nj = j + dj;
                  if (ni >= 0 && ni < b && nj >= 0 && nj < b && (di != 0 || dj != 0)) {
                      for (const auto& p1 : grid[i][j]) {
                          for (const auto& p2 : grid[ni][nj]) {
                              minDist = min(minDist, computeDistance(p1, p2));
                          }
                      }
                  }
              }
          }
      }
  }
  return minDist;
}


// int main()
// {
//     double min;
//     string filename;
//     cout << "File with list of points within unit square: ";
//     cin >> filename;
//     min = closestPair(filename);
//     cout << setprecision(16);
//     cout << "Distance between closest pair of points: " << min << endl;
//     return 0;
// }