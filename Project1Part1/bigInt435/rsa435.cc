// Nathaniel Shetler
// ID: 4015423
// Class: Algorithms 3460:435

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

// Pre: This function accepts no parameters
// Post: This function will generate a prime number and then return it.
BigUnsigned createPrime();

// Pre: This function acccepts in the phi, e, divisor, x, & y values
// Post: This function will find the correct e value and set the x & y values used to find d
void generateE(BigUnsigned &phi, BigUnsigned &e);

int main(){
	/* The library throws 'const char *' error messages when things go
	 * wrong.  It's a good idea to catch them using a 'try' block like this
	 * one.  Your C++ compiler might need a command-line option to compile
	 * code that uses exceptions. */

   // Create output file for storing p & q
   std::ofstream pqFile, enFile, dnFile;

	try {
      
      // Seeding so numbers are more random
      srand(time(NULL));

      // Open the file for storing p & q, e & n, d & n
      pqFile.open("p_q.txt");
      enFile.open("e_n.txt");
      dnFile.open("d_n.txt");
      
      // Generateing P
      BigUnsigned pNumber;
      pNumber = createPrime();

      // Write pNumber to pqFile 
      pqFile << pNumber << "\n";

      // Generating Q
      BigUnsigned qNumber;
      qNumber = createPrime();

      // Write qNumber to pqFile 
      pqFile << qNumber << "\n";

      // Output that P & Q have been generated
      std::cout << "The p & q values have been generated and stored to the p_q.txt file." << std::endl;

      // Generating N 
      BigUnsigned nNumber = pNumber * qNumber;

      // Output that N has been generated
      std::cout << "The n value has been calculated." << std::endl;

      // This is phi of n
      BigUnsigned phiOfn = (pNumber - 1) * (qNumber - 1);

      // Create e variable
      BigUnsigned e = 0;

      // Generate the e value
      generateE(phiOfn, e);

      // Write e & n to the en file
      enFile << e << "\n";
      enFile << nNumber << "\n";

      // Output that e has been generated
      std::cout << "The e value has been generated, and e & n have been stored in the e_n.txt file." << std::endl;

      // Get the d value
      BigUnsigned d = modinv(e, phiOfn);

      // Write d & n to the dn file
      dnFile << d << "\n";
      dnFile << nNumber << "\n";

      // Output that d has been generated
      std::cout << "The d value has been generated, and d & n have been stored in the d_n.txt file." << std::endl;

      // Close the files
      pqFile.close();
      enFile.close();
      dnFile.close();

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
   // The bases for the test
   BigInteger base1 = 2;
   BigInteger base2 = 5;

   // This is the exponent value (p - 1)
   BigUnsigned exponent = number - 1;

   // This will be the answer returned by modex (the remainder)
   BigUnsigned answer = 0;

   // This call modexp and do the calculation to get the remainder
   answer = modexp(base1, exponent, number);

   // If the remainder is not 1 return false
   if (answer != 1)
   { 
      return false;
   }

   // Otherwise we will try again
   answer = modexp(base2, exponent, number);

   // If the remainder is not 1 return false
   if (answer != 1)
   {
      return false;
   }

   // Otherwise the remainder is 1 so the number is most likely prime
   return true;

}

// Pre: This function accepts no parameters
// Post: This function will generate a prime number and then return it.
BigUnsigned createPrime()
{
   // Boolean for determining when a prime is found
   bool foundPrime = false;

   // number that will be used for the prime number
   BigUnsigned number;

   std::string stringNum;
   int stringLength = 0;

   // Loop that will go until a prime number is found
   while (!foundPrime || stringLength < 155)
   {
      // Reseting number
      number = 0;

      // Generate random number of 155 digits 
      for (int i = 0; i < 146; i++) {
         number = number * 10 + rand();
      }
      stringNum = bigIntegerToString(number);
      stringLength = stringNum.length();

      // Run fermats test to see if the number is prime
      foundPrime = fermatTest(number);
   }

   return number;
}

// Pre: This function acccepts in the phi, e, divisor, x, & y values
// Post: This function will find the correct e value and set the x & y values used to find d
void generateE(BigUnsigned &phi, BigUnsigned &e)
{
   // Create e, divisor, x, & y
   BigInteger divisor = 0, x = 0, y = 0;

   // Set e's initial value
   e = 151;

   // Find the correct e value that is relatively prime to phi
   while (divisor != 1)
   {  
      // Run the extended euclidean algorithm
      extendedEuclidean(phi, e, divisor, x, y);

      // If divisor is not 1 add to e
      if (divisor != 1)
      {
         e = e + 2;
      }
   }
}