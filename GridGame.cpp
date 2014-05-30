//-----------------------------------------------------------
//Program Name: Fill It!
//Author: Nischaal Cooray
//Desciption: Simulates the effect of the "Bucket" tool from Paint by filling a shape defined by the user. 
//-----------------------------------------------------------

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "GridGame.h"

using namespace std;

//----------------Default Constructor------------
GridGame::GridGame()
{
	for (int i = 0; i < 4; i++)
	{
		vector<int> gridRow;
		for (int j = 0; j < 4; j++)
		{
			gridRow.push_back(1);
		}
		grid_.push_back(gridRow);
	}
}
//-----------------------------------------------

//--------------Alternate Constructor------------
GridGame::GridGame(int maxRow, int maxCol)
{
	maxrow_ = maxRow;
	maxcol_ = maxCol;

	for (int i = 0; i < maxrow_; i++)
	{
		vector<int> gridRow;
		for (int j = 0; j < maxcol_; j++)
		{
			gridRow.push_back(0);
		}
		grid_.push_back(gridRow);
	}
}
//-----------------------------------------------

//--------------Alternate Constructor------------
GridGame::GridGame(string fileName)
{
	ifstream inFile;

	inFile.open(fileName);

	string lineRead;
	int rows = 0, columns = 0;

	while (!inFile.eof())
	{
		inFile >> lineRead;

		vector<int> gridRow;

		for (int j = 0; j < lineRead.length(); j++)
		{
			if ((lineRead.substr(j, 1)) == "1")
			{
				gridRow.push_back(1);
			}
			else if ((lineRead.substr(j, 1)) == "0")
			{
				gridRow.push_back(0);
			}
			else
			{
				cout << "Error encountered in File!";
			}
			columns = j + 1;
		}
		rows++;

		grid_.push_back(gridRow);
	}

	maxrow_ = rows;
	maxcol_ = columns;

}
//-----------------------------------------------

//----------------Destructor---------------------
GridGame::~GridGame()
{

}
//-----------------------------------------------

//---------Method to check if a plot is legal----
bool GridGame::isLegalPlot(int startPosRow, int startPosColumn)
{
	if ((getVal(startPosRow, startPosColumn) == 0) && (startPosRow < maxrow_) && (startPosColumn < maxcol_))
		return true;
	else
		return false;
}
//-----------------------------------------------

//---------Method to return the value stored at an index----
int GridGame::getVal(int row, int col)
{
	return grid_[row][col];
}
//----------------------------------------------------------

//---------Method to check the max number of rows-----------
int GridGame::getRow()
{
	return maxrow_;
}
//----------------------------------------------------------

//---------Method to check the max numbers of columns-------
int GridGame::getCol()
{
	return maxcol_;
}
//----------------------------------------------------------

//---------Method to update the value at an index-----------
void GridGame::setVal(int row, int col, int value)
{
	grid_[row][col] = value;
}
//----------------------------------------------------------

//---Set the start position defined by the user----
void GridGame::startPosition(int startPosRow, int startPosColumn)
{
	if (grid_[startPosRow][startPosColumn] != 1)
	{
		grid_[startPosRow][startPosColumn] = 1;
	}
}
//--------------------------------------------------

//----Facilitator to output shape-------------------
void GridGame::output(ostream& out)
{
	out << "	";
	for (int k = 0; k < maxcol_; k++)
	{
		if (k > 10)
			out << " " << k;
		else
			out << "  " << k;
	}

	out << endl << "	 ";
	for (int k = 0; k < maxcol_; k++)
	{
		out << "---";
	}

	out << endl;

	for (int i = 0; i < maxrow_; i++)
	{
		out << i << "|	";
		for (int j = 0; j < maxcol_; j++)
		{
			if (grid_[i][j] == 1)
				out << "  1";
			else
				out << "  0";
		}

		out << endl;
	}
}
//-----------------------------------------------

//--Method for overloading output operator-------
ostream& operator<<(ostream& out, GridGame& displayGrid)
{
	displayGrid.output(out);
	return out;
}
//-----------------------------------------------
