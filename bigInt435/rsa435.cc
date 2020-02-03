// You need to complete this program for a part of your first project.

// Standard libraries
#include <string>
#include <iostream>
#include <stdlib.h> 
#include <fstream>
#include <time.h>


// 'BigIntegerLibrary.hh' includes all of the library headers.
#include "BigIntegerLibrary.hh"

// Pre: This function accepts a BigUnsigned number that will be checked to see if it is prime.
// Post: This function will return true if the number is prime and false if it is not. 
bool fermatTest(BigUnsigned &number);

int main(){
	/* The library throws 'const char *' error messages when things go
	 * wrong.  It's a good idea to catch them using a 'try' block like this
	 * one.  Your C++ compiler might need a command-line option to compile
	 * code that uses exceptions. */

    // Create output file for storing p & q
    std::ofstream pqFile;

	try {
      
      // Seeding so numbers are more random
      srand(time(NULL));

      // Open the file for storing p & q
      pqFile.open("p_q.txt");
      
      // Generateing P
      BigUnsigned pNumber = BigUnsigned(1);
      for (int i = 0; i < 146; i++) {
         pNumber = pNumber * 10 + rand();
      }
      std::cout << "This is P\n";
      std::cout << pNumber <<std::endl;

      // Write pNumber to pqFile 
      pqFile << pNumber << "\n";

      // Generating Q
      BigUnsigned qNumber = BigUnsigned(1);
      for (int i = 0; i < 146; i++) {
         qNumber = qNumber * 10 + rand();
      }
      std::cout << "This is Q\n";
      std::cout << qNumber << std::endl;

      // Write qNumber to pqFile 
      pqFile << qNumber << "\n";

      std::cout << "N = P * Q\n";

      // Generating N
      BigUnsigned nNumber = pNumber * qNumber;
      std::cout << nNumber << std::endl;

      // This is phi of n
      BigUnsigned phiOfn = (pNumber - 1) * (qNumber - 1);
      
      // This is a test block for checking the fermatTest function. REMOVE AFTER TESTING--------
      bool isPrime = false;
      isPrime = fermatTest(pNumber);
      std::cout << isPrime << std::endl;

	} catch(char const* err) {
		std::cout << "The library threw an exception:\n"
			<< err << std::endl;
	}

	return 0;
}

// Pre: This function accepts a BigUnsigned number that will be checked to see if it is prime.
// Post: This function will return true if the number is prime and false if it is not. 
bool fermatTest(BigUnsigned &number)
{
   // This is the exponent value (p - 1)
   BigUnsigned exponent = number - 1;

   // This will be the answer returned by modex (the remainder)
   BigUnsigned answer = 0;

   answer = modexp(2, exponent, number);

   // REMOVE AFTER TESTING-------------------------------------
   std::cout << "modexp answer 1: " << answer << std::endl;

   // If the remainder is not 1 return false
   if (answer != 1)
   { 
      return false;
   }

   // Otherwise we will try again
   answer = modexp(5, exponent, number);

   // If the remainder is not 1 return false
   if (answer != 1)
   {
      return false;
   }

   // Otherwise the remainder is 1 so the number is most likely prime
   return true;

}