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

// Pre: This function will accept in an ifstream, and variables for storing information recieved from the file
// Post: This function will set the variable based on the information recieved from the file and also fill the matrix
// with the numbers from the file
std::vector<std::vector<int>> getFileData(std::ifstream &imageFile, int &fileHorizontal, int &fileVertical, int &maxGrayscale);

// Pre: This function will accept in the horizontal and vertical values obtained from the file.
// It will also accept the vector (matrix) of the numbers from the file and vector (matrix) for storing the energy values
// Post: This function will fill the energy matrix
void createEnergyMatrix(int &fileHorizontal, int &fileVertical, std::vector<std::vector<int>> &energyNumbers, std::vector<std::vector<int>> &fileNumbers);

// Pre: This function will accept in the horizontal and vertical values obtained from the file.
// It will also accept the vector (matrix) of the energy values and vector (matrix) for storing the cumulative energy values
// Post: This function will fill the cumulative energy matrix
void createCumulativeEnergy(int &fileHorizontal, int &fileVertical, std::vector<std::vector<int>> &energyNumbers, std::vector<std::vector<int>> &cumulativeEnergy);

int main(int argc, char *argv[])
{   
    if (argc < 4 || argc > 4)
    {
        std::cout << "Wrong format! It should be \"a.exe image.pgm horizontal vertical\"" << std::endl;
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
            // Variables for horizontal and vertical values in pgm file
            int fileHorizontal = 0;
            int fileVertical = 0;

            // Variable for max grayscale value
            int maxGrayscale = 0;

            // Vector for reading in the other values in the file
            std::vector<std::vector<int>> fileNumbers;

            // Get the information from the file
            fileNumbers = getFileData(imageFile, fileHorizontal, fileVertical, maxGrayscale);

            // Vector for holding energy calculations
            std::vector<std::vector<int>> energyNumbers(fileNumbers);

            // Get the energy matrix
            createEnergyMatrix(fileHorizontal, fileVertical, energyNumbers, fileNumbers);

            // Vector for holding cumulative energy calculations
            std::vector<std::vector<int>> cumulativeEnergy(energyNumbers);

            createCumulativeEnergy(fileHorizontal, fileVertical, energyNumbers, cumulativeEnergy);
        }
        else
        {
            std::cout << "There was a problem opening up the file." << std::endl;
        }
      
	}
	return 0;
}

// Pre: This function will accept in an ifstream, and variables for storing information recieved from the file
// Post: This function will set the variable based on the information recieved from the file and also fill the matrix
// with the numbers from the file
std::vector<std::vector<int>> getFileData(std::ifstream &imageFile, int &fileHorizontal, int &fileVertical, int &maxGrayscale)
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

        // Get the horizontal and vertical values from file
        imageFile >> fileHorizontal >> fileVertical;
        
        // Vector for reading in the other values in the file (Original Image)
        std::vector<std::vector<int>> fileNumbers(fileVertical, std::vector<int>(fileHorizontal, 0));

        // Get max grayscale value
        imageFile >> maxGrayscale;
        
        // Get all of the numbers from the file and store in fileNumbers matrix
        for (int i = 0; i < fileVertical; ++i)
        {
            for (int j = 0; j < fileHorizontal; ++j)
            { 
                imageFile >> fileNumbers[i][j];
            }
        } 

        // Output items from file
        std::cout << "Horizontal: " << fileHorizontal << std::endl;
        std::cout << "Vertical: " << fileVertical << std::endl;
        std::cout << "Max Grayscale value: " << maxGrayscale << std::endl;

        std::cout << "Contents of the file: " << std::endl;
        for (int i = 0; i < fileVertical; ++i)
        {
            for (int j = 0; j < fileHorizontal; ++j)
            {
                std::cout << fileNumbers[i][j] << " ";
            }
            std::cout << std::endl;
        }  

        return fileNumbers;
    }
    else
    {
        std::cout << "The file is not in the correct format" << std::endl;
    }
}

// Pre: This function will accept in the horizontal and vertical values obtained from the file.
// It will also accept the vector (matrix) of the numbers from the file and vector (matrix) for storing the energy values
// Post: This function will fill the energy matrix
void createEnergyMatrix(int &fileHorizontal, int &fileVertical, std::vector<std::vector<int>> &energyNumbers, std::vector<std::vector<int>> &fileNumbers)
{
    // For keeping track of difference in x and y
    int diffX = 0;
    int diffY = 0;

    for (int i = 0; i < fileVertical; ++i)
    {
        for (int j = 0; j < fileHorizontal; ++j)
        {   
            
            if (j == 0  && i == 0) // This handles the top left corner
            {
                // Set difference in x and y
                diffX = std::abs(fileNumbers[i][j] - fileNumbers[i][j + 1]);
                diffY = std::abs(fileNumbers[i + 1][j] - fileNumbers[i][j]);

                // Set the energy 
                energyNumbers[i][j] = diffX + diffY; 
            }
            else if ((j == fileHorizontal - 1) && i == 0) // This handles the top right corner
            {
                diffX = std::abs(fileNumbers[i][j - 1] - fileNumbers[i][j]);
                diffY = std::abs(fileNumbers[i + 1][j] - fileNumbers[i][j]);

                // Set the energy 
                energyNumbers[i][j] = diffX + diffY; 
            }
            else if ((j == 0) && (i == fileVertical - 1)) // This handles the bottom left corner
            {
                // Set difference in x and y
                diffX = std::abs(fileNumbers[i][j] - fileNumbers[i][j + 1]);
                diffY = std::abs(fileNumbers[i - 1][j] - fileNumbers[i][j]);

                // Set the energy 
                energyNumbers[i][j] = diffX + diffY; 
            }
            else if ((j == fileHorizontal - 1) && (i == fileVertical - 1)) // This handles the bottom right corner
            {
                // Set difference in x and y
                diffX = std::abs(fileNumbers[i][j] - fileNumbers[i][j - 1]);
                diffY = std::abs(fileNumbers[i - 1][j] - fileNumbers[i][j]);

                // Set the energy 
                energyNumbers[i][j] = diffX + diffY; 
            }
            else if ((j != 0) && (j != fileHorizontal - 1) && (i != 0) && (i != fileVertical - 1)) // This handles the bulk of the numbers (anything not on edges)
            {
                // Set difference in x and y
                diffX = std::abs(fileNumbers[i][j - 1] - fileNumbers[i][j]) + std::abs(fileNumbers[i][j] - fileNumbers[i][j + 1]);
                diffY = std::abs(fileNumbers[i - 1][j] - fileNumbers[i][j]) + std::abs(fileNumbers[i + 1][j] - fileNumbers[i][j]);

                // Set the energy 
                energyNumbers[i][j] = diffX + diffY; 

            }
            else if (j == 0) // Handles the left side (not corner)
            {
                // Set difference in x and y
                diffX = std::abs(fileNumbers[i][j] - fileNumbers[i][j + 1]);
                diffY = std::abs(fileNumbers[i - 1][j] - fileNumbers[i][j]) + std::abs(fileNumbers[i + 1][j] - fileNumbers[i][j]);

                // Set the energy 
                energyNumbers[i][j] = diffX + diffY;

            }
            else if (j == fileHorizontal - 1) // Handles the right side (not corner)
            {
                // Set difference in x and y
                diffX = std::abs(fileNumbers[i][j - 1] - fileNumbers[i][j]);
                diffY = std::abs(fileNumbers[i - 1][j] - fileNumbers[i][j]) + std::abs(fileNumbers[i + 1][j] - fileNumbers[i][j]);

                // Set the energy 
                energyNumbers[i][j] = diffX + diffY;
            }
            else if (i == 0) // This handles the top (not corner)
            {
                // Set difference in x and y
                diffX = std::abs(fileNumbers[i][j - 1] - fileNumbers[i][j]) + std::abs(fileNumbers[i][j] - fileNumbers[i][j + 1]);
                diffY = std::abs(fileNumbers[i + 1][j] - fileNumbers[i][j]);

                // Set the energy 
                energyNumbers[i][j] = diffX + diffY;
            }
            else if (i == fileVertical - 1) // This handles the bottom (not corner)
            {
                // Set difference in x and y
                diffX = std::abs(fileNumbers[i][j - 1] - fileNumbers[i][j]) + std::abs(fileNumbers[i][j] - fileNumbers[i][j + 1]);
                diffY = std::abs(fileNumbers[i - 1][j] - fileNumbers[i][j]);

                // Set the energy 
                energyNumbers[i][j] = diffX + diffY;
            }
        }
    }

    
    std::cout << "Energy matrix: " << std::endl;
    // Print out energy matrix
    for (int i = 0; i < fileVertical; ++i)
    {
        for (int j = 0; j < fileHorizontal; ++j)
        {
            std::cout << energyNumbers[i][j] << " ";
        }
        std::cout << std::endl;
    } 
    
}

// Pre: This function will accept in the horizontal and vertical values obtained from the file.
// It will also accept the vector (matrix) of the energy values and vector (matrix) for storing the cumulative energy values
// Post: This function will fill the cumulative energy matrix
void createCumulativeEnergy(int &fileHorizontal, int &fileVertical, std::vector<std::vector<int>> &energyNumbers, std::vector<std::vector<int>> &cumulativeEnergy)
{
    // For keeping track of minumum
    int minNumber = 0;

    // This will create the cumulative energy matrix
    for (int i = 0; i < fileVertical; ++i)
    {
        for (int j = 0; j < fileHorizontal; ++j)
        {
            if (i == 0) // Set the first row
            {
                cumulativeEnergy[i][j] = energyNumbers[i][j];
            }
            else if (j == 0) // This will handle the left hand side
            {
                if (cumulativeEnergy[i - 1][j] < cumulativeEnergy[i - 1][j + 1])
                {
                    cumulativeEnergy[i][j] += cumulativeEnergy[i - 1][j];
                }
                else
                {
                    cumulativeEnergy[i][j] += cumulativeEnergy[i - 1][j + 1];
                }
            }
            else if (j == (fileHorizontal - 1)) // This will handle the right hand side
            {
                if (cumulativeEnergy[i - 1][j - 1] < cumulativeEnergy[i - 1][j])
                {
                    cumulativeEnergy[i][j] += cumulativeEnergy[i - 1][j - 1];
                }
                else
                {
                    cumulativeEnergy[i][j] += cumulativeEnergy[i - 1][j];
                }  
            }
            else // This will handle everything else in the middle
            {
                // This runs through the three options and finds the smallest

                if (cumulativeEnergy[i - 1][j - 1] < cumulativeEnergy[i - 1][j])
                {
                    // Smallest is first
                    cumulativeEnergy[i][j] += cumulativeEnergy[i - 1][j - 1];
                }
                else
                {   
                    if (cumulativeEnergy[i - 1][j] < cumulativeEnergy[i - 1][j + 1])
                    {
                        // Smallest is second
                        cumulativeEnergy[i][j] += cumulativeEnergy[i - 1][j];
                    }
                    else
                    {
                        // Smallest is third
                        cumulativeEnergy[i][j] += cumulativeEnergy[i - 1][j + 1];
                    }
                    
                }
            }
        }
    } 

    std::cout << "Cumulative energy matrix: " << std::endl;
    // Print out energy matrix
    for (int i = 0; i < fileVertical; ++i)
    {
        for (int j = 0; j < fileHorizontal; ++j)
        {
            std::cout << cumulativeEnergy[i][j] << " ";
        }
        std::cout << std::endl;
    } 
}