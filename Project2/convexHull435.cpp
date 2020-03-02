// Nathaniel Shetler
// ID: 4015423
// UANet ID: nds39
// Class: Algorithms 3460:435

// Standard libraries
#include <string>
#include <iostream>
#include <stdlib.h> 
#include <stack>
#include <fstream>
#include <vector>

// ----------------------------------------------------------------------------------------
// The following block of code has been adapted from the code found at: https://www.geeksforgeeks.org

struct Point 
{ 
    int x, y; 
}; 
  
// A global point needed for  sorting points with reference 
// to  the first point Used in compare function of qsort() 
Point p0; 
  
// A utility function to find next to top in a stack 
Point nextToTop(std::stack<Point> &S) 
{ 
    Point p = S.top(); 
    S.pop(); 
    Point res = S.top(); 
    S.push(p); 
    return res; 
} 
  
// A utility function to swap two points 
int swap(Point &p1, Point &p2) 
{ 
    Point temp = p1; 
    p1 = p2; 
    p2 = temp; 
} 
  
// A utility function to return square of distance 
// between p1 and p2 
int distSq(Point p1, Point p2) 
{ 
    return (p1.x - p2.x)*(p1.x - p2.x) + 
          (p1.y - p2.y)*(p1.y - p2.y); 
} 
  
// To find orientation of ordered triplet (p, q, r). 
// The function returns following values 
// 0 --> p, q and r are colinear 
// 1 --> Clockwise 
// 2 --> Counterclockwise 
int orientation(Point p, Point q, Point r) 
{ 
    int val = (q.y - p.y) * (r.x - q.x) - 
              (q.x - p.x) * (r.y - q.y); 
  
    if (val == 0) return 0;  // colinear 
    return (val > 0)? 1: 2; // clock or counterclock wise 
} 
  
// A function used by library function qsort() to sort an array of 
// points with respect to the first point 
int compare(const void *vp1, const void *vp2) 
{ 
   Point *p1 = (Point *)vp1; 
   Point *p2 = (Point *)vp2; 
  
   // Find orientation 
   int o = orientation(p0, *p1, *p2); 
   if (o == 0) 
     return (distSq(p0, *p2) >= distSq(p0, *p1))? -1 : 1; 
  
   return (o == 2)? -1: 1; 
} 

// -------------------------------------------------------------------------------
// This is the graham scan algorithm adapted from: https://www.geeksforgeeks.org/convex-hull-set-2-graham-scan/

// Prints convex hull of a set of n points. 
void grahamConvexHull(Point points[], int n, std::vector<Point> &grahamScanList) 
{ 
   // Find the bottommost point 
   int ymin = points[0].y, min = 0; 
   for (int i = 1; i < n; i++) 
   { 
     int y = points[i].y; 
  
     // Pick the bottom-most or chose the left 
     // most point in case of tie 
     if ((y < ymin) || (ymin == y && 
         points[i].x < points[min].x)) 
        ymin = points[i].y, min = i; 
   } 
  
   // Place the bottom-most point at first position 
   swap(points[0], points[min]); 
  
   // Sort n-1 points with respect to the first point. 
   // A point p1 comes before p2 in sorted output if p2 
   // has larger polar angle (in counterclockwise 
   // direction) than p1 
   p0 = points[0]; 
   qsort(&points[1], n-1, sizeof(Point), compare); 
  
   // If two or more points make same angle with p0, 
   // Remove all but the one that is farthest from p0 
   // Remember that, in above sorting, our criteria was 
   // to keep the farthest point at the end when more than 
   // one points have same angle. 
   int m = 1; // Initialize size of modified array 
   for (int i=1; i<n; i++) 
   { 
       // Keep removing i while angle of i and i+1 is same 
       // with respect to p0 
       while (i < n-1 && orientation(p0, points[i], 
                                    points[i+1]) == 0) 
          i++; 
  
  
       points[m] = points[i]; 
       m++;  // Update size of modified array 
   } 
  
   // If modified array of points has less than 3 points, 
   // convex hull is not possible 
   if (m < 3) return; 
  
   // Create an empty stack and push first three points 
   // to it. 
   std::stack<Point> S; 
   S.push(points[0]); 
   S.push(points[1]); 
   S.push(points[2]); 
  
   // Process remaining n-3 points 
   for (int i = 3; i < m; i++) 
   { 
      // Keep removing top while the angle formed by 
      // points next-to-top, top, and points[i] makes 
      // a non-left turn 
      while (orientation(nextToTop(S), S.top(), points[i]) != 2) 
         S.pop(); 
      S.push(points[i]); 
   } 
  
   // Now stack has the output points, print contents of stack 
   while (!S.empty()) 
   { 
       Point p = S.top(); 
       std::cout << "(" << p.x << ", " << p.y <<")" << std::endl; 

       // Put the point on the vector
       grahamScanList.push_back(p);

       S.pop(); 
   } 
}

//---------------------------------------------------------------------------------
// This is the jarvis march algorithm adapted from: https://www.geeksforgeeks.org/convex-hull-set-1-jarviss-algorithm-or-wrapping/

// Prints convex hull of a set of n points. 
void jarvisConvexHull(Point points[], int n, std::vector<Point> &jarvisList) 
{ 
    // There must be at least 3 points 
    if (n < 3) return; 
  
    // Initialize Result 
    std::vector<Point> hull; 
  
    // Find the leftmost point 
    int l = 0; 
    for (int i = 1; i < n; i++) 
        if (points[i].x < points[l].x) 
            l = i; 
  
    // Start from leftmost point, keep moving counterclockwise 
    // until reach the start point again.  This loop runs O(h) 
    // times where h is number of points in result or output. 
    int p = l, q; 
    do
    { 
        // Add current point to result 
        hull.push_back(points[p]); 
  
        // Search for a point 'q' such that orientation(p, x, 
        // q) is counterclockwise for all points 'x'. The idea 
        // is to keep track of last visited most counterclock- 
        // wise point in q. If any point 'i' is more counterclock- 
        // wise than q, then update q. 
        q = (p+1)%n; 
        for (int i = 0; i < n; i++) 
        { 
           // If i is more counterclockwise than current q, then 
           // update q 
           if (orientation(points[p], points[i], points[q]) == 2) 
               q = i; 
        } 
  
        // Now q is the most counterclockwise with respect to p 
        // Set p as q for next iteration, so that q is added to 
        // result 'hull' 
        p = q; 
  
    } while (p != l);  // While we don't come to first point 
  
    // Print Result 
    for (int i = 0; i < hull.size(); i++)
    {
       // Put the point on the vector
       jarvisList.push_back(hull[i]);

       // Output the point
       std::cout << "(" << hull[i].x << ", " << hull[i].y << ")\n";
    } 

} 
  
// -------------------------------------------------------------------------------
// The following code is devoloped using the program template provided to us by Dr. Duan

int main(int argc, char *argv[])
{   
   if (argc < 3) 
      std::cout << "wrong format! should be \"a.exe algType dataFile\"";
   else {
      std::string algType = argv[1];
      std::string dataFilename = argv[2];

      std::string outputFile = "";

      //read your data points from dataFile (see class example for the format)
      std::vector<Point> pointsVec;
      
      // X and Y for reading in the file
      int xNum, yNum;
      
      //Point for reading in the file
      Point point;

      // Create infine and open the dataFile
      std::ifstream inFile;
      inFile.open(dataFilename);

      while (!inFile.eof())
      {
          inFile >> xNum;
          inFile >> yNum;

          point = {xNum, yNum};
          pointsVec.push_back(point);
          std::cout << xNum << " " << yNum << std::endl;
      }
      
      // Close the file
      inFile.close();

      // Empty array of size of the number of points in vector
      Point points[pointsVec.size()];

      // Make vector into an array of points
      for (int i = 0; i < pointsVec.size(); ++i)
      {
         points[i] = pointsVec[i];
      }
      
      // This is the convexHull that will be created using one of the following methods
      std::vector<Point> convexHull;

      if (algType[0]=='G') {
         // This block will do the graham scan

         // Output file name
         outputFile = "hull_G.txt";

         // Create the n (number of points) that is needed for the grahamConvexHall function
         int n = sizeof(points)/sizeof(points[0]);

         // Create the graham scan convexHull and fill it
         grahamConvexHull(points, n, convexHull);
         
      } 
      else if (algType[0]=='J') {
         // This block will do the Javis March algorithm

         // Output file name
         outputFile = "hull_J.txt";

         // Create the n (number of points) that is needed for the jarvis function
         int n = sizeof(points)/sizeof(points[0]);

         // Create the graham scan convexHull and fill it
         jarvisConvexHull(points, n, convexHull);
      }
      else { //default 
         //call your Quickhull algorithm to solve the problem
         outputFile = "hull_Q.txt";
      }
      
      // Create the ofstream object and open output file
      std::ofstream outFile;
      outFile.open(outputFile);

      // Write convex hull to the outputFile 
      for (int i = 0; i < convexHull.size(); ++i)
      {
         // Put x of the point in file
         outFile << convexHull[i].x;

         // Put a space in between the numbers
         outFile << " ";

         // Put y of the point in file
         outFile << convexHull[i].y;
         
         outFile << "\n";
      }
      //you should be able to visulize your convex hull using the "ConvexHull_GUI" program.
	}
	return 0;
}

 
