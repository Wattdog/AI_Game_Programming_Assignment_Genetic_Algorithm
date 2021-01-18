#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <random>
#include "Nodes.h";

std::ifstream fileOpen(std::string _fileName);
void drawMaze(std::vector<int> _grid, int _border);
void runAI(std::vector<int> _grid, int _start, int _finish, int _currentPos, int _border);

int main()
{
	std::ifstream file;
	std::string fileName;
	
	// Asks user to enter file name
	std::cout << "Please enter the file name (file_name.txt): ";
	std::cin >> fileName;

	file = fileOpen(fileName);

	// Creates a temp input which will be pushed into
	// the mazeNumbers vector
	char tempInput;
	std::vector<char> mazeNumbers;
	
	// Pushes values into mazeNumbers vector
	while (file >> tempInput)
		mazeNumbers.push_back(tempInput - 48);

	// Defines the X and Y size of the maze
	int sizeX = mazeNumbers[2];
	int sizeY = mazeNumbers[5];

	// Represents the size of the maze
	std::cout << "Size X: " << sizeX << " " << "Size Y: "
		<< sizeY << std::endl;
	
	std::vector<int> grid;
	// The border is the size of the maze + 2;
	int border = sizeX + 2;

	for (int i = 0; i < border + 1; i++)
		// Adds border to the top
		grid.push_back(5);

	int temp = 0;
	for (int i = 0; i < mazeNumbers.size(); i++)
	{
		if (mazeNumbers[i] == 0)
		{
			// 0 represents an walkable space
			grid.push_back(0);
			temp++;
		}

		if (mazeNumbers[i] == 1)
		{
			// 1 represents an obstacle
			grid.push_back(1);
			temp++;
		}

		if (mazeNumbers[i] == 2)
		{
			// 2 represents the start and AI
			grid.push_back(2);
			temp++;
		}

		if (mazeNumbers[i] == 3)
		{
			// 3 represents the finish
			grid.push_back(3);
			temp++;
		}

		if (temp == sizeX)
		{
			// Adds a border to the end of the row
			grid.push_back(5);
			// Adds a border to the start of the row
			grid.push_back(5);
			temp = 0;
		}
	}

	for (int i = 0; i < sizeX + 1; i++)
	{
		// adds border at bottom
		grid.push_back(5);
	}

	// Gets the start, finish and first avaiable positions
	int start = getStartPosition(grid);
	int finish = getFinishPosition(grid);
	// Sets the AIs position to the start
	int currentPosition = start;

	runAI(grid, start, finish, currentPosition, border);
}

std::ifstream fileOpen(std::string _fileName)
{
	std::ifstream mazeFile;
	// Opens file
	mazeFile.open(_fileName);

	// Checks to see if file doesn't exist/open
	if (!mazeFile.is_open())
	{
		std::cout << "Couldn't Open File" << std::endl;
	}

	return mazeFile;
}

void drawMaze(std::vector<int> _grid, int _border)
{
	int j = 0;
	for (int i = 0; i < _grid.size(); i++)
	{
		if (_grid[i] == 5) // Draws border
		{
			std::cout << _grid[i] << "   ";

			j++;
			if (j == _border)
			{
				std::cout << std::endl;
				std::cout << std::endl;
				j = 0;
			}
		}
		if (_grid[i] != 5) // Will draw the values in the maze
		{
			std::cout << _grid[i] << "   ";
			j++;
			if (j == _border)
			{
				std::cout << std::endl;
				std::cout << std::endl;
				j = 0;
			}
		}
	}
}

void runAI(std::vector<int> _grid, int _start, int _finish, int _currentPos, int _border)
{
	// Creates random number generator
	std::default_random_engine generator;
	std::uniform_real_distribution<double> distribution(0.0, 1.0);

	int n = 8; // Number of chromosomes in the population
	int cN = 8; // length of each chromosome

	int chromosome[8][8] = {};

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < cN; j++)
		{
			double r = distribution(generator); // Generates a number between 0 and 1
			if (r <= 0.5)
			{
				chromosome[i][j] = 0;
			}
			else
			{
				chromosome[i][j] = 1;
			}
		}
	}

	// Creates values for all available moves
	moves availableMoves;
	int up = availableMoves.up = -_border;
	int down = availableMoves.down = _border;
	int left = availableMoves.left = -1;
	int right = availableMoves.right = 1;

	int cPosition = 0;
	float finalPosition[8] = {};

	while (_currentPos != _finish)
	{
		while (cPosition <= cN)
		{
			for (int i = 0; i < 8; i++)
			{
				if (chromosome[i][cPosition] == 0 && chromosome[i][cPosition + 1] == 0)
				{
					// Move up
					if (_grid[_currentPos + up] == 0)
					{
						// Sets Previous Position to 8 to show path
						_grid[_currentPos] = 8;
						_currentPos += up;
						// Shows current position
						_grid[_currentPos] = 2;
						cPosition++;
						finalPosition[i] = _currentPos;
					}
				}
				if (chromosome[i][cPosition] == 0 && chromosome[i][cPosition + 1] == 1)
				{
					// Move right
					if (_grid[_currentPos + right] == 0)
					{
						// Sets Previous Position to 8 to show path
						_grid[_currentPos] = 8;
						_currentPos += right;
						// Shows current position
						_grid[_currentPos] = 2;
						cPosition++;
						finalPosition[i] = _currentPos;
					}
				}
				if (chromosome[i][cPosition] == 1 && chromosome[i][cPosition + 1] == 0)
				{
					// Move down
					if (_grid[_currentPos + down] == 0)
					{
						// Sets Previous Position to 8 to show path
						_grid[_currentPos] = 8;
						_currentPos += down;
						// Shows current position
						_grid[_currentPos] = 2;
						cPosition++;
						finalPosition[i] = _currentPos;
					}
				}
				if (chromosome[i][cPosition] == 1 && chromosome[i][cPosition + 1] == 1)
				{
					// Move left
					if (_grid[_currentPos + left] == 0)
					{
						// Sets Previous Position to 8 to show path
						_grid[_currentPos] = 8;
						_currentPos += left;
						// Shows current position
						_grid[_currentPos] = 2;
						cPosition++;
						finalPosition[i] = _currentPos;
					}
				}
			}

			drawMaze(_grid, _border); // Draws maze
			float fitness[8] = {};

			for (int i = 0; i < 8; i++)
			{
				fitness[i] = 1 / (finalPosition[i] + 1); // Calculates the fitness for each chromosome 
			}

			float overallFitness = 0;
			for (int i = 0; i < 8; i++)
			{
				overallFitness += fitness[i]; // Calculates the overall fitness 
			}

			float individualFitnessPercentage[8] = {};
			for (int i = 0; i < 8; i++)
			{
				// Currently doesn't give correct outputs
				individualFitnessPercentage[i] = (fitness[i] / overallFitness) * 100; // Calculates the individual fitness percentage
				std::cout << individualFitnessPercentage[i] << std::endl;
			}

			/*int temp = 0;
			while (temp != 8)
			{
				int x = distribution(generator); // generates random number between 0 and 1
				x = x * 100; // range from 0% to 100%

				// Goes through each chromosome to see which chromosome it will breed
				// with to create a new offspring
				if (x >= 0 && x < 32)
				{
					temp++;
				}
			}*/

			int crossOverRate = 0.7; // Chance of a cross over to occur

			int crossOver = distribution(generator); // Generates a number between 0 and 1;

			if (crossOver <= crossOverRate)
			{
				// Takes the middle point of each chromosome
				// Will Switch the second half from the first chromosome
				// with the second half of the from the second chromosome
			}
			else
			{
				// If crossover doesn't occur then we will just copy
				// the orginal chromsomes over to the offspring
			}

			int mutationRate = 0.001; // Chance of a mutation to occur

			int mutation = distribution(generator); // generates a number between 0 and 1

			// Goes through each value in the chromosome
			for (int i = 0; i < 8; i++)
			{
				if (mutation <= mutationRate)
				{
					// If mutation occurs and point in chromosome equals 0
					// change value to 1
					// If mutation occurs and point in chromosome equals 1
					// change value to 0
				}
				else
				{
					// If mutation doesn't occur continue
				}
			}
		}

	}
}