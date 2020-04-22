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
#include <utility>


//--------------------------------------------------------------------------------------------------------------------//
//FUNCTION PROTOTYPES:


// Pre: This function will accept in an ifstream, and variables for storing information recieved from the file
// Post: This function will set the variable based on the information recieved from the file and also fill the matrix
// with the numbers from the file
std::vector<std::vector<int>> getFileData(std::ifstream &imageFile, int &fileHorizontal, int &fileVertical, int &maxGrayscale);

// Pre: This function will accept the vector (matrix) of the numbers from the file and vector (matrix) for storing the energy values
// Post: This function will fill the energy matrix
void createEnergyMatrix(std::vector<std::vector<int>> &energyNumbers, std::vector<std::vector<int>> &fileNumbers);

// Pre: This function will accept the vector (matrix) of the energy values and vector (matrix) for storing the cumulative energy values.
// Post: This function will fill the cumulative energy matrix
void createCumulativeEnergy(std::vector<std::vector<int>> &energyNumbers, std::vector<std::vector<int>> &cumulativeEnergy);

// Pre: This function will accpet the horizontal and vertical dimensions as well as the vector (matrix)
// containing the cumulative energy calculations. It will also accept in the vector (matrix) to store the new image data.
// Post: This function will fill create the new image by removing the vertical seam.
void removeVerticalSeam(int &fileHorizontal, int &fileVertical, std::vector<std::vector<int>> &cumulativeEnergy, std::vector<std::vector<int>> &newImage);

// Pre: This function will take in the horizontal and vertical dimentions and also the vector (matrix) 
// that contains the data for the image.
// Post: This file will write the data to a file
void writeImageToFile(int &fileHorizontal, int &fileVertical, std::vector<std::vector<int>> &newImage);

// Pre: This function will accept the image vector (matrix)
// Post: This function will return the transposed vector (matrix)
std::vector<std::vector<int>> transposeMatrix(std::vector<std::vector<int>> &newImage);

// END FUNCTION PROTOTYPES
//--------------------------------------------------------------------------------------------------------------------//


int main(int argc, char *argv[])
{   
    if (argc < 4 || argc > 4)
    {
        std::cout << "Wrong format! It should be \"a.exe image.pgm vertical horizontal\"" << std::endl;
    }
   else
   {
        std::string imageFilename = argv[1];
        std::string numVerticalString = argv[2];
        std::string numHorizontalString = argv[3];
    	
        // Convert to integers
        int numVertical = std::stoi(numVerticalString);
        int numHorizontal = std::stoi(numHorizontalString);

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

            // Will hold the new image
            std::vector<std::vector<int>> newImage(fileNumbers);

            if (numVertical > 0)
            {
                // Run the vertical seam removal
                for (int i = 0; i < numVertical; ++i)
                {

                    // Vector for holding energy calculations
                    // (Will change size overtime to accommodate removal of seams)
                    std::vector<std::vector<int>> energyNumbers(fileVertical, std::vector<int>(fileHorizontal, 0));

                    // Get the energy matrix
                    createEnergyMatrix(energyNumbers, newImage);

                    // Vector for holding cumulative energy calculations
                    // (Will change size overtime to accommodate removal of seams)
                    std::vector<std::vector<int>> cumulativeEnergy(energyNumbers);

                    // Get the cumulative energy matrix
                    createCumulativeEnergy(energyNumbers, cumulativeEnergy);

                    // Remove the vertical seam
                    removeVerticalSeam(fileHorizontal, fileVertical, cumulativeEnergy, newImage);
                }
            }
            

            // If there are also horizontal seams
            if (numHorizontal > 0)
            {

                // Transpose the matrix
                newImage = transposeMatrix(newImage);

                for (int i = 0; i < numHorizontal; ++i)
                {

                    // Vector for holding energy calculations
                    // (Will change size overtime to accommodate removal of seams)
                    std::vector<std::vector<int>> energyNumbers(fileHorizontal, std::vector<int>(fileVertical, 0));

                    // Get the energy matrix
                    createEnergyMatrix(energyNumbers, newImage); 

                    // Vector for holding cumulative energy calculations
                    // (Will change size overtime to accommodate removal of seams)
                    std::vector<std::vector<int>> cumulativeEnergy(energyNumbers);  

                    // Get the cumulative energy matrix
                    createCumulativeEnergy(energyNumbers, cumulativeEnergy);   
                    
                    // Remove the vertical seam
                    removeVerticalSeam(fileVertical, fileHorizontal, cumulativeEnergy, newImage);

                }

                // Transpose the matrix back to normal
                newImage = transposeMatrix(newImage);

            }

            // Write the new image to a file
            writeImageToFile(fileHorizontal, fileVertical, newImage);
            
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

        return fileNumbers;
    }
    else
    {
        std::cout << "The file is not in the correct format" << std::endl;
    }
}

// Pre: This function will accept the vector (matrix) of the numbers from the file and vector (matrix) for storing the energy values
// Post: This function will fill the energy matrix
void createEnergyMatrix(std::vector<std::vector<int>> &energyNumbers, std::vector<std::vector<int>> &fileNumbers)
{
    // For keeping track of difference in x and y
    int diffX = 0;
    int diffY = 0;

    for (int i = 0; i < fileNumbers.size(); ++i)
    {
        for (int j = 0; j < fileNumbers[0].size(); ++j)
        {   
            
            if (j == 0  && i == 0) // This handles the top left corner
            {
                // Set difference in x and y
                diffX = std::abs(fileNumbers[i][j] - fileNumbers[i][j + 1]);
                diffY = std::abs(fileNumbers[i + 1][j] - fileNumbers[i][j]);

                // Set the energy 
                energyNumbers[i][j] = diffX + diffY; 
            }
            else if ((j == fileNumbers[0].size() - 1) && i == 0) // This handles the top right corner
            {
                diffX = std::abs(fileNumbers[i][j - 1] - fileNumbers[i][j]);
                diffY = std::abs(fileNumbers[i + 1][j] - fileNumbers[i][j]);

                // Set the energy 
                energyNumbers[i][j] = diffX + diffY; 
            }
            else if ((j == 0) && (i == fileNumbers.size() - 1)) // This handles the bottom left corner
            {
                // Set difference in x and y
                diffX = std::abs(fileNumbers[i][j] - fileNumbers[i][j + 1]);
                diffY = std::abs(fileNumbers[i - 1][j] - fileNumbers[i][j]);

                // Set the energy 
                energyNumbers[i][j] = diffX + diffY; 
            }
            else if ((j == fileNumbers[0].size() - 1) && (i == fileNumbers.size() - 1)) // This handles the bottom right corner
            {
                // Set difference in x and y
                diffX = std::abs(fileNumbers[i][j] - fileNumbers[i][j - 1]);
                diffY = std::abs(fileNumbers[i - 1][j] - fileNumbers[i][j]);

                // Set the energy 
                energyNumbers[i][j] = diffX + diffY; 
            }
            else if ((j != 0) && (j != fileNumbers[0].size() - 1) && (i != 0) && (i != fileNumbers.size() - 1)) // This handles the bulk of the numbers (anything not on edges)
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
            else if (j == fileNumbers[0].size() - 1) // Handles the right side (not corner)
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
            else if (i == fileNumbers.size() - 1) // This handles the bottom (not corner)
            {
                // Set difference in x and y
                diffX = std::abs(fileNumbers[i][j - 1] - fileNumbers[i][j]) + std::abs(fileNumbers[i][j] - fileNumbers[i][j + 1]);
                diffY = std::abs(fileNumbers[i - 1][j] - fileNumbers[i][j]);

                // Set the energy 
                energyNumbers[i][j] = diffX + diffY;
            }
        }
    }  
}

// Pre: This function will accept the vector (matrix) of the energy values and vector (matrix) for storing the cumulative energy values.
// Post: This function will fill the cumulative energy matrix
void createCumulativeEnergy(std::vector<std::vector<int>> &energyNumbers, std::vector<std::vector<int>> &cumulativeEnergy)
{

    // This will create the cumulative energy matrix
    for (int i = 0; i < energyNumbers.size(); ++i)
    {
        for (int j = 0; j < energyNumbers[0].size(); ++j)
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
            else if (j == (energyNumbers[0].size() - 1)) // This will handle the right hand side
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

                // For keeping track of the minimum value
                int smallIndexFirst = i - 1;
                int smallIndexSecond = j - 1;

                // This runs through the three options and finds the smallest
                for (int k = 0; k < 3; ++k)
                {   
                    if (cumulativeEnergy[i - 1][j - 1 + k] < cumulativeEnergy[smallIndexFirst][smallIndexSecond])
                    {
                        smallIndexSecond = j - 1 + k;
                    }
                }

                // Add to cumulative energy
                cumulativeEnergy[i][j] += cumulativeEnergy[smallIndexFirst][smallIndexSecond];

            }
        }
    } 
}

// Pre: This function will accpet the horizontal and vertical dimensions as well as the vector (matrix)
// containing the cumulative energy calculations. It will also accept in the vector (matrix) to store the new image data.
// Post: This function will fill create the new image by removing the vertical seam.
void removeVerticalSeam(int &fileHorizontal, int &fileVertical, std::vector<std::vector<int>> &cumulativeEnergy, std::vector<std::vector<int>> &newImage)
{
    // For the starting point
    int startingPoint = cumulativeEnergy[newImage.size() - 1][0];
    std::pair<int,int> startingIndex;

    // Set initial starting point
    startingIndex.first = newImage.size() - 1;
    startingIndex.second = 0;

    // vector for holding the seam
    std::vector<std::pair<int, int>> indexOfSeam;

    // This will find the min on the bottom row (starting point)
    for (int i = 0; i < newImage[0].size(); ++i)
    {
        if (cumulativeEnergy[newImage.size() - 1][i] < startingPoint)
        {
            startingPoint = cumulativeEnergy[newImage.size() - 1][i];
            startingIndex.second = i;
        }
    }

    // Set the index to - 1 to mark it to be removed
    newImage[startingIndex.first][startingIndex.second] = -1;

    // Add starting index to seam
    indexOfSeam.push_back(startingIndex);

    // For getting the next item on the seam
    std::pair<int, int> nextItem;

    // Go through the rest of the image
    for (int i = 0; i < newImage.size() - 1; ++i)
    {

        if ((indexOfSeam.back().second != 0) && (indexOfSeam.back().second != newImage[0].size() - 1)) // If the item is in the middle
        {

            // For keeping track of the minimum
            std::pair<int,int> minumumNum;
            minumumNum.first = indexOfSeam.back().first - 1;
            minumumNum.second = indexOfSeam.back().second - 1;

            // Find the minumum
            for (int j = 0; j < 3; ++j)
            {
                if (cumulativeEnergy[indexOfSeam.back().first - 1][indexOfSeam.back().second - 1 + j] < cumulativeEnergy[minumumNum.first][minumumNum.second])
                {
                    minumumNum.second = indexOfSeam.back().second - 1 + j;
                }
            }
            
            // Set the next item
            nextItem.first = minumumNum.first;
            nextItem.second = minumumNum.second;
            
            // Set the index to -1 to mark it to be removed
            newImage[nextItem.first][nextItem.second] = -1;

            // Add next item to seam vector
            indexOfSeam.push_back(nextItem);

        }
        else if (indexOfSeam.back().second == 0) // Check left side
        {

            if (cumulativeEnergy[indexOfSeam.back().first - 1][indexOfSeam.back().second] < cumulativeEnergy[indexOfSeam.back().first - 1][indexOfSeam.back().second + 1])
            {
                nextItem.first = indexOfSeam.back().first - 1;
                nextItem.second = indexOfSeam.back().second;
            }
            else
            {
                nextItem.first = indexOfSeam.back().first - 1;
                nextItem.second = indexOfSeam.back().second + 1;
            }

            // Set the index to -1 to mark it to be removed
            newImage[nextItem.first][nextItem.second] = -1;

            // Add next item to seam vector
            indexOfSeam.push_back(nextItem);
        }
        else if (indexOfSeam.back().second == newImage[0].size() - 1) // check right side
        {
            if (cumulativeEnergy[indexOfSeam.back().first - 1][indexOfSeam.back().second - 1] < cumulativeEnergy[indexOfSeam.back().first - 1][indexOfSeam.back().second])
            {
                nextItem.first = indexOfSeam.back().first - 1;
                nextItem.second = indexOfSeam.back().second - 1;
            }
            else
            {
                nextItem.first = indexOfSeam.back().first - 1;
                nextItem.second = indexOfSeam.back().second;
            }

            // Set the index to -1 to mark it to be removed
            newImage[nextItem.first][nextItem.second] = -1;

            // Add next item to seam vector
            indexOfSeam.push_back(nextItem);
        }
    }

    // Do the deletions of the seam items
    for (int i = 0; i < newImage.size(); ++i)
    {
        for (int j = 0; j < newImage[i].size(); ++j)
        {
            if (newImage[i][j] == -1)
            {
                newImage[i].erase(newImage[i].begin() + j);
            }
        }
    }

    // Make the size of the horizontal smaller
    fileHorizontal -= 1;
    
}

// Pre: This function will take in the horizontal and vertical dimentions and also the vector (matrix) 
// that contains the data for the image.
// Post: This file will write the data to a file
void writeImageToFile(int &fileHorizontal, int &fileVertical, std::vector<std::vector<int>> &newImage)
{
    std::ofstream outFile("../image_processed.pgm");

    // Write information to file
    outFile << "P2\n";
    outFile << "# Created by IrfanView\n";
    outFile << fileHorizontal << " " << fileVertical << "\n";
    int grayscale = 255;
    outFile << grayscale << "\n";

    // Write image to the fiel
    for (int i = 0; i < fileVertical; ++i)
    {
        for (int j = 0; j < fileHorizontal; ++j)
        {
            outFile << newImage[i][j] << " ";
        }

        outFile << "\n";
    }
}

// Pre: This function will accept the image vector (matrix)
// Post: This function will return the transposed vector (matrix)
std::vector<std::vector<int>> transposeMatrix(std::vector<std::vector<int>> &newImage)
{   
    // This will be the transposed vector
    std::vector<std::vector<int>> transposedMatrix(newImage[0].size(), std::vector<int>(newImage.size(), 0));

    for (int i = 0; i < newImage.size(); ++i)
    {
        for (int j = 0; j < newImage[i].size(); ++j)
        {
            transposedMatrix[j][i] = newImage[i][j];
        }
    }

    return transposedMatrix;
}