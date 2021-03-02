#include "Cell.h"

using namespace std;
//cell is one sapce on the grid, they have thier status and last 2 status stored
Cell::Cell(){
  mStatus = 0;
  mOnePast = -1;
  mTwoPast = -1;
}
Cell::Cell(bool status){
  mStatus = status;
  mOnePast = -1;
  mTwoPast = -1;
}
 Cell::~Cell(){
}

bool Cell::getStatus(){
  return mStatus;
}
void Cell::setStatus(bool update){
  mStatus = update;
}
bool Cell::getNextStatus(){
  return mNextStatus;
}
void Cell::setNextStatus(bool update){
  mNextStatus = update;
}

void Cell::setOnePast(float thatRound){
  setTwoPast(mOnePast);
  mOnePast = thatRound;
}
float Cell::getOnePast(){
  return mOnePast;
}
void Cell::setTwoPast(float onePastRound){
  mTwoPast = onePastRound;
}
float Cell::getTwoPast(){
  return mTwoPast;
}
