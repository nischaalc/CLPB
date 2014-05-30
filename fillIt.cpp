//-----------------------------------------------------------
//Program Name: Fill It!
//Author: Nischaal Cooray
//Desciption: Simulates the effect of the "Bucket" tool from Paint by filling a shape defined by the user. 
//-----------------------------------------------------------

#include <iostream>
#include <vector>
#include <fstream>
#include "GridGame.h"

using namespace std;

//----------Prototypes---------------
void floodFill(int row, int col, GridGame& G);
//-----------------------------------

int main(void)
{
	//--------Variables---------------------------
	int rows, columns, startRow, startCol;
	int numberOfPoints = 0;
	string userDecision, temp, fileName;
	string outputName = "filledShape.txt";
	bool keepPlotting = true;
	bool corrPlot;
	ofstream outFile(outputName);
	//--------------------------------------------

	//------Introduction to the program-----------
	cout << "Welcome to Fill It!" << endl;
	cout << "The aim of this program is to simulate the effect of the \"Bucket\" tool from \nPaint." << endl;
	cout << "Using either a file or your own imagination, create a shape and then say where\n you want the filling to start from. Then watch the magic happen!" << endl;
	cout << "Format for entering coordinates is: \"row column\". For example, entering \"3 2\" \nwould correspond to row 3, column 2." << endl;
	cout << "Happy Filling!" << endl << endl;
	//--------------------------------------------

	//Check if user wants to create their own shape or use one from a file
	cout << "Do you want to enter a Grid size yourself or from a File? (G or F): ";
	cin >> userDecision;
	
	//----------Creating users own shape----------
	if (userDecision == "G")
	{
		cout << "Enter the number of rows: ";			//Get the dimensions of the grid to create
		cin >> rows;
		cout << "Enter the number of columns: ";
		cin >> columns;

		GridGame g(rows, columns);						//Initialize the grid

		cout << g << endl << endl;						//Display the grid to the user

		while (numberOfPoints < 10)						//Loop until more than 10 points have been plotted by the user
		{
			while (keepPlotting == true)				//Loop until the user decides to stop plotting points
			{
				cout << "Enter a point to plot: ";		//Get the position that the user wants to plot at
				cin >> rows >> columns;									

				if ((rows == 99) && (columns == 99))	//Check if the user wants to stop plotting
					keepPlotting = false;
				else
				{
					corrPlot = g.isLegalPlot(rows, columns);	//Check if the users plot point is valid

					if (corrPlot == true)				//If valid, then plot the points 
					{
						g.setVal(rows, columns, 1);
						keepPlotting = true;
						numberOfPoints++;
					}
					else								//Else, display an error message and do nothing to the grid
					{
						cout << "Please enter a correct value!" << endl << endl << endl;
					}

					cout << g << endl << endl;			//Display an updated grid

					cout << "Enter \"99 99\" at any time to start filling." << endl;
				}
			}
			if (numberOfPoints < 10)					//Check if the user has plotted at least 10 points 
			{
				cout << "You need at least 10 points to start filling!" << endl;
				keepPlotting = true;
			}
		}

		cout << "Enter your starting position: ";		//Get the position that the user wants to start filling from
		cin >> startRow >> startCol;
		
		g.startPosition(startRow, startCol);			//Update the grid

		floodFill(startRow, startCol, g);				//Call the recursive algorithm

		cout << g << endl << endl;						//Display the final grid
	}
	//--------------------------------------------

	//-------Creating a shape from a file---------
	else if (userDecision == "F")
	{
		cout << "Enter the name of your file (including the extension): ";		//Get the name of the file that's storing the shape
		cin >> fileName;

		GridGame g(fileName);													//Initialize the grid

		cout << endl << endl << g << endl << endl;								//Display the grid

		cout << "Enter your starting position: ";								//Get the position that the user wants to start filling from
		cin >> startRow >> startCol;											
		
		g.startPosition(startRow, startCol);									//Update the grid

		cout << endl << endl << g << endl;										//Display the grid

		floodFill(startRow, startCol, g);										//Call the recursive algorithm

		cout << g << endl << endl;												//Display the final grid and write it to a file
		outFile << g << endl << endl;

		cout << "Done!" << endl;
		cout << "A file has been created with your filled shape." << endl;
	}
	//--------------------------------------------
	
	return 0;

}

/*
Recursive algorithm that fills a shape. Similar to the "Bucket" tool in Paint
@param row, col: the point at which the fill should be carried out
@param G: the shape, passed by reference to allow easy updating
*/
void floodFill(int row, int col, GridGame& G)
{
	//Check if the current position can be filled
	if (G.getVal(row, col) == 0)
	{
		if ((row < G.getRow()) && (col < G.getCol()))
		{
			G.setVal(row, col, 1);
		}
	}

	//Check if it is possible to move down
	if (row + 1 < G.getRow())
	{
		if (G.getVal(row + 1, col) == 0)
		{
			floodFill(row + 1, col, G);
		}
	}

	//Check if it is possible to move right
	if (col + 1 < G.getCol())
	{
		if (G.getVal(row, col + 1) == 0)
		{
			floodFill(row, col + 1, G);
		}
	}

	//Check if it is possible to move up
	if ((G.getVal(row - 1, col) == 0) && (row - 1 >= 0))
	{
		floodFill(row - 1, col, G);
	}

	//Check if it is possible to move left
	if ((G.getVal(row, col - 1) == 0) && (col - 1 >= 0))
	{
		floodFill(row, col - 1, G);
	}
}