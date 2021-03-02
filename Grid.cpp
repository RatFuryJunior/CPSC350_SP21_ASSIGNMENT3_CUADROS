#include "Grid.h"
#include <stdlib.h>
#include <iostream>

using namespace std;

//A grid is a 2 by 2 array as defined by the user or the file contains cells
Grid::Grid(){
  mRows = 4;
  mColumns = 4;
  theGrid = new Cell *[mRows];
  for (int i = 0; i < mRows; ++i){
    theGrid [i] = new Cell [mColumns];
  }
}

Grid::Grid(int x, int y){
  mRows = x;
  mColumns = y;
  theGrid = new Cell *[mRows];
  for (int i = 0; i < mRows; ++i){
    theGrid [i] = new Cell [mColumns];
  }
}

Grid::~Grid(){
  //deletions
  for (int i = 0; i < mRows; ++i){
    delete theGrid[i];
  }
  delete [] theGrid;
}

Cell Grid::getCellAt(int x, int y){
  Cell toRet = theGrid[x][y];
  return toRet;
}
bool Grid::getCellValueAt(int x, int y){
  bool toRet = theGrid[x][y].getStatus();
  return toRet;
}
void Grid::setCellAt(int x, int y, bool setTo){
  theGrid[x][y].setStatus(setTo);
}

void Grid::setCellAtToNext(int x, int y, bool nextStatus){
  theGrid[x][y].setNextStatus(nextStatus);
}

void Grid::updateCell(int x, int y){
  theGrid[x][y].setStatus(theGrid[x][y].getNextStatus());
}

void Grid::setOnePastCellAt(int x, int y, float onePastFloat){
  theGrid[x][y].setOnePast(onePastFloat);
}

//taken in part from Rene's Lecture
//used for the random decleration option
void Grid::generateRandomGrid(float density){
  srand (time(NULL));
  int totalCells = mRows*mColumns;
  int numCellsFromRando = totalCells * density;
  cout<< numCellsFromRando <<endl;
  for(int i = 0; i < mRows; ++i){
    for(int j = 0; j <mColumns; ++j){
      theGrid[i][j].setStatus(0);
    }
  }
  int i = 0;
  int r, c = 0;
  while (i < numCellsFromRando){
    r = abs((rand()% mRows));
    c = abs((rand()% mColumns));

    if(theGrid[r][c].getStatus()){
      continue;
    }

    theGrid[r][c].setStatus(1);
    i++;
  }
}

string Grid::printGrid(){
  string toRet = "";
  for(int i = 0; i < mRows; ++i){
    for(int j = 0; j <mColumns; ++j){
      if(theGrid[i][j].getStatus()){
        toRet = toRet + "X";
      }else{
        toRet = toRet + "-";
      }
    }toRet = toRet + "\n";
  }
  return toRet;
}

int Grid::getRows(){
  return mRows;
}
int Grid::getColumns(){
  return mColumns;
}
