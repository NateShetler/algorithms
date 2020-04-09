// Nathaniel Shetler
// ID: 4015423
// UANet ID: nds39
// Class: Algorithms 3460:435

// Standard libraries
#include <string>
#include <iostream>
#include <stdlib.h> 
#include <fstream>
#include <vector>
#include <cmath>


int main(int argc, char *argv[])
{   
    if (argc < 4 || argc > 4)
    {
        std::cout << "Wrong format! It should be \"a.exe image.pgm horizontal vertical\"";
    }
   else
   {
        std::string imageFilename = argv[1];
        std::string xValue = argv[2];
        std::string yValue = argv[3];
    	
        // File for reading the data
        std::ifstream imageFile;
        imageFile.open(imageFilename.c_str());

        // See if file is open
        if (imageFile.is_open())
        {
            // String for holding line of input
            std::string fileLine = "";

            // Get the first line
            std::getline(imageFile, fileLine);

            // Check to make sure it is 'P2'
            if (fileLine == "P2")
            {
                
                // Get second line and do nothing with it
                // (Line is a comment)
                std::getline(imageFile, fileLine);

                // Variables for horizontal and vertical values in pgm file
                int fileHorizontal = 0;
                int fileVertical = 0;

                // Get the horizontal and vertical values from file
                imageFile >> fileHorizontal >> fileVertical;
               
                // Get max grayscale value
                int maxGrayscale = 0;
                imageFile >> maxGrayscale;

                // Vector for reading in the other values in the file
                std::vector<std::vector<int>> fileNumbers(fileHorizontal, std::vector<int>(fileVertical, 0));

                // Get all of the numbers from the file
                for (int i = 0; i < fileHorizontal; ++i)
                {
                    for (int j = 0; j < fileVertical; ++j)
                    { 
                        imageFile >> fileNumbers[i][j];
                    }
                } 


                // Output items from file
                std::cout << "Horizontal: " << fileHorizontal << std::endl;
                std::cout << "Vertical: " << fileVertical << std::endl;
                std::cout << "Max Grayscale value: " << maxGrayscale << std::endl;

                for (int i = 0; i < fileHorizontal; ++i)
                {
                    for (int j = 0; j < fileVertical; ++j)
                    {
                        std::cout << fileNumbers[i][j] << " ";
                    }
                    std::cout << std::endl;
                }  
            }
        }
        else
        {
            std::cout << "There was a problem opening up the file." << std::endl;
        }
      
	}
	return 0;
}

 
