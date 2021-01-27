Nathaniel Shetler <br>
Class: Algorithms <br>

# Algorithms Project 2

## How To Run:

This program can be run using cmake. A CMakeLists.txt file is included with the project.
To run it you may want to create a build folder. You can do this by typing: "mkdir build"
After that, go into that build folder. Once in the build folder, type: "cmake .."
following that, "type: make"

This will compile the progam and make the object file that can be run. Once you've done
this, make sure that you've put a "test.txt" file inside of the build folder. Once you've
done that, type: "./convexHull435 G test.txt" to run Graham Scan, "./convexHull435 J test.txt"
to run Jarvis March, and "./convexHull435 Q test.txt" to run Quickhull.

<b> Note: </b> To test the time it takes one of the convex hull solving algorithms to run, one can simply
add "time" in front of the normal things. For example, to test the time it takes Graham Scan to 
run, one can type: "time ./convexHull435 G test.txt"

<b> Additional Note:</b> There is a folder called "Point Test Files" under the "GUI4ConvexHall" folder.
This folder has files with points corresponding to the different shapes and number of points that
were used for testing. Feel free to use these for your testing of my program if you'd like.

-------------------------------------------------------------------------------------------------

## Description of Program:

This program consists of three different algorithms for finding the convex hull; Graham Scan, 
Jarvis March, and Quickhull. 

In accordance with the project directions provided by Dr. Duan, the implementations for these were adapted from the ones found at
geeksforgeeks.com. 
* The Graham Scan was adapted from: https://www.geeksforgeeks.org/convex-hull-set-2-graham-scan/ .
* The Jarvis March was adapted from: https://www.geeksforgeeks.org/convex-hull-set-1-jarviss-algorithm-or-wrapping/ . 
* The Quickhull was adapted from: https://www.geeksforgeeks.org/quickhull-algorithm-convex-hull/ and https://stackoverflow.com/questions/53072989/sort-2d-points-counter-clockwise . 

The adpatations made it so that the algorithms would function for our Project 2. Quickhull was the 
most difficult one to adapt. It originally gave the points out of order so the convex hull didn't 
work correctly, but this was fixed by sorting the points clockwise. The sorting part of the quickhull
implemenation was done by using the pointComparison function adapted from a questions asked at: 
https://stackoverflow.com/questions/53072989/sort-2d-points-counter-clockwise 
and by using the standard sort function. Graham Scan and Jarvis March didn't recquire as many changes, 
with the only main change being that it now had to store the convex hull into a vector instead of 
simply printing the points out. This change was actually made to all three convex hull solving algorithms.

   
The main function was started with the program template given to us by Dr. Duan. First off, this 
function will read the data points located in the "test.txt" file. It will store these in a vector. 
After doing this, it will call the corresponding convex hull solving algorithm based on the user's 
input (G for Graham Scan, J for Jarvis March, and Q for Quickhull). After calling the correct quick
hull solving algorithm, the convex hull will be found and stored in a vector. The convex hull from 
the vector will then be written to a file called "hull_G.txt" for Graham Scan, "hull_J.txt" for 
Jarvis March, and "hull_Q.txt" for Quickhull. 
