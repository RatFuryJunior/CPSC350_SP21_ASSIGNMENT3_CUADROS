/*
#include <iostream>
#include <stdlib.h>
#include "RandomGen.h"

using namespace std;

RandomGen::RandomGen(){
  mRows = 4;
  mColumns = 4;
  mDensity = .5;
  GenRandomArray();
}

RandomGen::RandomGen(int rows, int col, float den){
  mRows = rows;
  mColumns = col;
  mDensity = den;
  GenRandomArray();
}

RandomGen::~RandomGen(){
  for (int i = 0; i < mRows; ++i){
    cout<<"bruh."<<endl;
    delete randomArray[i];
    cout<<"bruh.."<<endl;
  }
  delete [] randomArray;
  cout<<"bruh..."<<endl;
}

char ** RandomGen::returnArray(){
  return randomArray;
}

void RandomGen::GenRandomArray(){
  totalCells = mRows*mColumns;
  numCellsFromRando = totalCells * mDensity;
  char randomArray[mRows][mColumns];
  for(int i = 0; i < mRows; ++i){
    for(int j = 0; j <mColumns; ++j){
      randomArray[i][j] = '-';
    }
  }
  int i = 0;
  int r, c = 0;
  while (i < totalCells){
    r = GenNumber(mRows);
    c = GenNumber(mColumns);

    randomArray[r][c] = 'x';
    i++;
  }
}

int RandomGen::GenNumber(int max){
  return abs(rand()% max - 1);
}
*/
