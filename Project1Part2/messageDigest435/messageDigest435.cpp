// Nathaniel Shetler
// ID: 4015423
// Class: Algorithms

#include <string.h>
#include <iostream>
#include <fstream>
#include "sha256.h"
#include "BigIntegerLibrary.hh"
#include <math.h>

 
int main(int argc, char *argv[])
{
   
   //Second part of your project starts here
   if (argc < 3 || argc > 4 || (argv[1][0]!='s' && argv[1][0]!='v')) 
      std::cout << "wrong format! should be \"a.exe s filename\" or \"a.exe v filename signatureFile\"" << std::endl;
   else {
      std::string filename = argv[2];
      
      //read the file
      std::streampos begin,end;
      std::ifstream myfile (filename.c_str(), std::ios::binary);
      begin = myfile.tellg();
      myfile.seekg (0, std::ios::end);
      end = myfile.tellg();
      std::streampos size = end-begin;
      //std::cout << "size of the file: " << size << " bytes.\n"; //size of the file

      myfile.seekg (0, std::ios::beg);
      char * memblock = new char[size];
      myfile.read (memblock, size); //read file; it's saved in the char array memblock
      myfile.close();
        
      if (argv[1][0]=='s') {
         
         // Create infile
         std::ifstream dnFile;
         
         // Open the file
         dnFile.open("d_n.txt");

         // Get the d value
         std::string dValue;
         std::getline(dnFile, dValue);

         // Get the n value
         std::string nValue;
         std::getline(dnFile, nValue);

         // Use sha256 to create the hash value
         std::string sha256SignValue = sha256(memblock);

         // Convert the string numbers to BigUnsigned numbers
         BigUnsigned sha256Number = BigUnsignedInABase(sha256SignValue, 16);
         BigUnsigned dNumber = stringToBigUnsigned(dValue);
         BigUnsigned nNumber = stringToBigUnsigned(nValue);

         // Create the digital signature
         BigUnsigned digitalSignature = modexp(sha256Number, dNumber, nNumber);

         // Create new signature file
         std::string signatureName = filename + ".signature";

         // Create ostream for signature file
         std::ofstream signatureFile (signatureName.c_str(), std::ios::binary);

         // Write the signature from the file
         signatureFile << digitalSignature;

         // Output that the file has been signed
         std::cout << "The file has been signed." << std::endl;

         // Close the signature & dn files 
         signatureFile.close();
         dnFile.close();

      }
      else {
         
         // Make sure that there are all 4 arguments that need to be provided for verifying the file
         if (argc != 4)
         {
            std::cout << "wrong format! should be \"a.exe v filename signatureFile\"" << std::endl;
         }
         else
         {
            // Create infiles
            std::ifstream dnFile, signatureFile, enFile;

            // Open the file
            dnFile.open("d_n.txt");

            // Open the en file
            enFile.open("e_n.txt");

            // Get the e value
            std::string eValue;
            std::getline(enFile, eValue);

            // Get the d value
            std::string dValue;
            std::getline(dnFile, dValue);

            // Get the n value
            std::string nValue;
            std::getline(dnFile, nValue);

            // Convert e, d, & n to BigUnsigned
            BigUnsigned eNumber = stringToBigUnsigned(eValue);
            BigUnsigned dNumber = stringToBigUnsigned(dValue);
            BigUnsigned nNumber = stringToBigUnsigned(nValue);

            // Use sha256 to create the hash value
            std::string sha256SignValue = sha256(memblock);

            // Convert to BigUnsigned
            BigUnsigned sha256Number = BigUnsignedInABase(sha256SignValue, 16);

            // Open the signature file
            std::string signatureFileName = argv[3];
            signatureFile.open(signatureFileName);

            // Get the signature and put it in string
            std::string signature;
            std::getline(signatureFile, signature);

            // Convert string to BigUnsigned
            BigUnsigned signatureNumber = stringToBigUnsigned(signature);

            // Encrypt signature using e
            BigUnsigned encryptedSignature = modexp(signatureNumber, eNumber, nNumber);

            // Check to see if the file is authentic or if it has been modified
            if (sha256Number == encryptedSignature)
            {
               std::cout << "The file has been verified and it is authentic." << std::endl;
            }
            else
            {
               std::cout << "The file has been modified." << std::endl;
            }

            // Close the files
            dnFile.close();
            enFile.close();
            signatureFile.close();
         }
      }
      delete[] memblock;
    }
    return 0;
}