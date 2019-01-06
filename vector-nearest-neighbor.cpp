/**
 * Design a C++ solution to compute the nearest neighbour for a point in a vector of points. 
 * Clearly state the interface, and provide an implementation.  
 * Your solution should allow computing the distance using either Euclidean or Manhattan Distances.
 */

#include <math.h>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>

using namespace std;

/**
 * create a new point
 */
struct Point
{
  int x, y;
};

/**
 * manhattan method for calculating distance between two points
 */
float manhattan(int px, int py, int qx, int qy)
{
  return abs(py - qy) + abs(px - qx);
} // end manhattan

/**
 * euclidean method for calculating distance between two points
 */
float euclidean(int px, int py, int qx, int qy)
{
  return sqrt(pow((py - qy), 2) + pow((px - qx), 2));
} // end euclidean

/**
 * prompt user to create a point (x, y)
 */
Point createUserPoint()
{
  int x, y;
  cout << "Enter x coordinate: ";
  cin >> x;
  cout << "Enter y coordinate: ";
  cin >> y;
  Point p;
  p.x = x;
  p.y = y;
  return p;
} // end createUserPoint

/**
 * create random Point
 */
Point createRandomPoint()
{
  Point p;
  p.x = rand() % 21 - 10; // random number between -10 and 10 inclusively
  p.y = rand() % 21 - 10; // random number between -10 and 10 inclusively
  return p;
} // end createRandomPoint

/**
 * print coordinate point (x, y)
 */
string printCoordinatePoint(int x, int y)
{
  return "(" + to_string(x) + ", " + to_string(y) + ")";
} // end printCoordinatePoint

int main(void)
{
  float eucDistance, closestEucDistance, manDistance, closestManDistance;
  int formulaSelection;
  Point closestEucPoint, closestManPoint;

  srand(time(NULL)); // seed random number

  vector<Point> points; // vector to hold random Points
  for (int i = 0; i < 10; i++)
    points.push_back(createRandomPoint()); // generate random Points

  Point userPoint = createUserPoint(); // have user create his/her point

  // print all points along with the user selected point
  cout << "\nYour chosen point: " << printCoordinatePoint(userPoint.x, userPoint.y) << endl;
  cout << "\nAll other points: ";
  for (int i = 0; i < points.size(); i++)
    cout << "(" << points[i].x << ", " << points[i].y << ")" << ((i < points.size() - 1) ? ", " : "");
  cout << endl; // new line

  cout << "\nEnter [1] to calculate nearest neighbor using Euclidean formula, \nor [2] to calculate nearest neighbor using Manhattan formula: ";
  cin >> formulaSelection;

  // calculate euclidean distances
  if (formulaSelection == 1)
  {
    closestEucDistance = euclidean(userPoint.x, userPoint.y, points[0].x, points[0].y);
    // cout << "Euclidean Distance: " << closestEucDistance << endl;
    closestEucPoint = points[0];
    for (int j = 1; j < points.size(); j++)
    {
      eucDistance = euclidean(userPoint.x, userPoint.y, points[j].x, points[j].y);
      // cout << "Euclidean Distance: " << eucDistance << endl;
      if (eucDistance < closestEucDistance)
      {
        closestEucDistance = eucDistance;
        closestEucPoint = points[j];
      }
    }

    // print results of closest manhattan point
    cout << "\nClosest Euclidean distance to point "
         << printCoordinatePoint(userPoint.x, userPoint.y) << " is point "
         << printCoordinatePoint(closestEucPoint.x, closestEucPoint.y) << " with a distance of "
         << closestEucDistance << " units." << endl;
  }

  // calculate manhattan distances
  if (formulaSelection == 2)
  {
    closestManDistance = manhattan(userPoint.x, userPoint.y, points[0].x, points[0].y);
    // cout << "Manhattan Distance: " << closestManDistance << endl;
    closestEucPoint = points[0];
    for (int j = 1; j < points.size(); j++)
    {
      manDistance = manhattan(userPoint.x, userPoint.y, points[j].x, points[j].y);
      // cout << "Manhattan Distance: " << manDistance << endl;
      if (manDistance < closestManDistance)
      {
        closestManDistance = manDistance;
        closestManPoint = points[j];
      }
    }

    // print results of closest manhattan point
    cout << "\nClosest Manhattan distance to point "
         << printCoordinatePoint(userPoint.x, userPoint.y) << " is point "
         << printCoordinatePoint(closestManPoint.x, closestManPoint.y) << " with a distance of "
         << closestManDistance << " units." << endl;
  }

  if (formulaSelection != 1 && formulaSelection != 2)
  {
    cout << "\nThat was an invalid selection." << endl;
  }
  return 0;
} // end main