//-----------------------------------------------------------
//Program Name: Fill It!
//Author: Nischaal Cooray
//Desciption: Simulates the effect of the "Bucket" tool from Paint by filling a shape defined by the user. 
//-----------------------------------------------------------

#ifndef __GRID__
#define __GRID__

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class GridGame
{

public:
	//-----------Constructors--------
	GridGame();
	GridGame(int maxRow, int maxCol);
	GridGame(string fileName);
	//-------------------------------

	//-----------Destructor----------
	~GridGame();
	//-------------------------------
	
	//-----------Inspectors----------
	bool isLegalPlot(int startPosRow, int startPosColumn);
	int getVal(int row, int col);
	int getRow();
	int getCol();
	//-------------------------------

	//-----------Mutators------------
	void startPosition(int startPosRow, int startPosColumn);
	void setVal(int row, int col, int value);
	//-------------------------------

	//-----------Facilitators--------
	void output(ostream& out);
	//-------------------------------


private:
	vector<vector<int> > grid_;
	int maxrow_;
	int maxcol_;
};

//-------Operator Overloading--------
ostream& operator<<(ostream& out, GridGame& displayGrid);
//-----------------------------------

#endif 