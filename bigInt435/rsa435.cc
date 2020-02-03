// You need to complete this program for a part of your first project.

// Standard libraries
#include <string>
#include <iostream>
#include <stdlib.h> 
#include <fstream>


// 'BigIntegerLibrary.hh' includes all of the library headers.
#include "BigIntegerLibrary.hh"

// Pre: This function accepts a BigUnsigned number that will be checked to see if it is prime, 
// and also an integer for the number of iterations to try and see if the number is prime.
// Post: This function will return true if the number is prime and false if it is not. 
bool fermatTest(BigUnsigned &number,  int &numIterations);

int main(){
	/* The library throws 'const char *' error messages when things go
	 * wrong.  It's a good idea to catch them using a 'try' block like this
	 * one.  Your C++ compiler might need a command-line option to compile
	 * code that uses exceptions. */

    // Create output file for storing p & q
    std::ofstream pqFile;

	try {

      // Open the file for storing p & q
      pqFile.open("p_q.txt");
      
      std::cout << "a couple of test cases for 3460:435/535 Algorithms!!!\n";
      BigUnsigned big1 = BigUnsigned(1);
      for (int i=0;i<400;i++) {
         big1 = big1*10 +rand();
      }
      std::cout << "my big1 !!!\n";
      std::cout << big1 <<std::endl;

      // Write big1 to pqFile 
      pqFile << big1 << "\n";

      BigUnsigned big2 = BigUnsigned(1);
      for (int i=0;i<400;i++) {
         big2 = big2*10 +rand();
      }
      std::cout << "my big2 !!!\n";
      std::cout << big2 << std::endl;

      // Write big2 to pqFile 
      pqFile << big2 << "\n";

      std::cout << "my big3 = big1*big2 !!!\n";

      // big3 is n
      BigUnsigned big3 = big1*big2;
      std::cout << big3 << std::endl;

      // This is phi of n
      BigUnsigned phiOfn = (big1 - 1) * (big2 - 1);

      /*
      std::cout << "my big3/big2 !!!\n";
      std::cout <<big3/big2 << std::endl;
      */
      
	} catch(char const* err) {
		std::cout << "The library threw an exception:\n"
			<< err << std::endl;
	}

	return 0;
}

// Pre: This function accepts a BigUnsigned number that will be checked to see if it is prime, 
// and also an integer for the number of iterations to try and see if the number is prime.
// Post: This function will return true if the number is prime and false if it is not. 
bool fermatTest(BigUnsigned &number,  int &numIterations)
{
   
}