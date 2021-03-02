#include "Simulation.h"
#include <unistd.h>
#include <iostream>

using namespace std;

Simulation::Simulation(){
  simGrid = new Grid(5,5);
  simGrid->generateRandomGrid(.5);
  //This shouldnt every really be called but it can be
  runSimulation('c',1);
}

//Called by main, asks for the creation of the grid for random and loads for file
Simulation::Simulation(int genType, int mode, int outputMode){
  if(genType == 1){//random mode grid creation
    cout<<"How many Rows?"<<endl;
    int userRows = 0;
    cin >> userRows;
    cout<<"How many Columns?"<<endl;
    int userColumns = 0;
    cin >> userColumns;
    cout<<"What Density (must be a decimal less than one)?"<<endl;
    float userDensity = 0;
    cin >> userDensity;
    simGrid = new Grid(userRows,userColumns);
    simGrid->generateRandomGrid(userDensity);
  }else if(genType == 2){//file grid creation
    gridFileProc = FileProcessor();
    loadFromMap();
  }

  if(mode == 1){
    runSimulation('c',outputMode);
  }else if(mode == 2){
    runSimulation('d',outputMode);
  }else if(mode == 3){
    runSimulation('m',outputMode);
  }
}

Simulation::~Simulation(){
}

void Simulation::loadFromMap(){//file grid creation
  cout<<"What is the file name of the file you wish to open? ex: input.txt"<<endl;
  string userFileInput;
  cin >> userFileInput;
  int fileRows = 0;
  fileRows = stoi(gridFileProc.loadLineFromFile(userFileInput, 1));//loads rows
  int fileColumns = 0;
  fileColumns = stoi(gridFileProc.loadLineFromFile(userFileInput, 2));//loads columns
  cout<<"There are " <<fileRows<<" rows and There are " <<fileColumns <<" columns"<<endl;
  simGrid = new Grid(fileRows,fileColumns);//loads grid
  int currentLineNumber = 3;
  for(int i = 0; i < simGrid->getRows(); ++i){
    string fullLine = gridFileProc.loadLineFromFile(userFileInput,currentLineNumber);
    for(int j = 0; j <simGrid->getColumns(); ++j){
      char fileCellStatus = fullLine.at(j);
      if(fileCellStatus == 'X'){
        simGrid->setCellAt(i,j,1);//transaltes the X's and -'s from the file to 0s and 1s
      }
    }
    currentLineNumber = currentLineNumber + 1;
  }
}

void Simulation::runSimulation(char modeToSim, int outputMode){//contians loop that runs each sim.
  string outputFileName = "";
  if(outputMode == 3){//for detemrining file output for ouput option 3
    cout<<"What output file name for the output? ex: output.txt" <<endl;
    cin >>outputFileName;
  }
  if(outputMode == 3){
    gridFileProc.makeOutFile(outputFileName);
    gridFileProc.printToFile(outputFileName,"0\n");
    gridFileProc.printToFile(outputFileName,simGrid->printGrid());
  }else{
    cout<< simGrid->printGrid();
  }

  bool lastGrid [simGrid->getRows()][simGrid->getColumns()];//creats the grids for checking ending
  bool pastLastGrid [simGrid->getRows()][simGrid->getColumns()];
  bool pastLastLastGrid [simGrid->getRows()][simGrid->getColumns()];

  for (mRoundCounter = 0; mRoundCounter < 500; ++mRoundCounter){// loops max of 500 times
    if (outputMode == 1){
      sleep(1);//sleep timer of 1 second between each sim
      runSimulationRound(modeToSim,outputMode);
    }
    if(outputMode == 2){
      string choice = "";// waits for input between each sim
      cout<<"Hit any letter other then q and enter to contiune... or the letter q to quit" <<endl;
      cin >> choice;
      if (choice.at(0)=='q'){
        break;
      }else{
        runSimulationRound(modeToSim,outputMode);//runs the round
      }
    }
    if(outputMode == 3){
      runSimulationRound(modeToSim,outputMode);//runs the round
      gridFileProc.printToFile(outputFileName,to_string(mRoundCounter+1)+"\n");
      gridFileProc.printToFile(outputFileName,simGrid->printGrid());// prints out to the file
    }else{
      cout<<mRoundCounter+1<<endl;
      cout<< simGrid->printGrid();
    }

    for(int i = 0; i < simGrid->getRows(); ++i){// updates the past grids
      for(int j = 0; j <simGrid->getColumns(); ++j){
        pastLastLastGrid[i][j] = pastLastGrid[i][j];
      }
    }
    for(int i = 0; i < simGrid->getRows(); ++i){
      for(int j = 0; j <simGrid->getColumns(); ++j){
        pastLastGrid[i][j] = lastGrid[i][j];
      }
    }
    for(int i = 0; i < simGrid->getRows(); ++i){
      for(int j = 0; j <simGrid->getColumns(); ++j){
        lastGrid[i][j] = simGrid->getCellValueAt(i,j);
      }
    }
    int counter = 0;
    for(int i = 0; i < simGrid->getRows(); ++i){//check for all of them being equal to the last last grid
      for(int j = 0; j <simGrid->getColumns(); ++j){
        if((pastLastLastGrid[i][j] == simGrid->getCellValueAt(i,j))&& (mRoundCounter>2)){
          counter = counter + 1;
        }
      }
    }
    if (counter >= simGrid->getRows() *simGrid->getColumns() ){ // if they are all the same break;
      cout<<"Oscilation occured, simulation halted after "<<mRoundCounter<<" rounds"<<endl;
      break;
    }
    counter = 0;
    for(int i = 0; i < simGrid->getRows(); ++i){//check for all of them being equal to the last grid and if they were both 0
      for(int j = 0; j <simGrid->getColumns(); ++j){
        if((lastGrid[i][j] == simGrid->getCellValueAt(i,j))&& (lastGrid[i][j] == 0)&&(mRoundCounter>2)){
          counter = counter + 1;
        }
      }
    }
    if (counter >= simGrid->getRows() *simGrid->getColumns() ){ // if they are all the same break;
      cout<<"Dead grid, simulation halted after "<<mRoundCounter<<" rounds" <<endl;
      break;
    }
  }
  if(mRoundCounter >499){//if the simulation reaches 500 it also stops
    cout<<"Simulation halted after "<<mRoundCounter<<" rounds"<<endl;
  }
  cout<<"Thanks for stoping by!"<<endl;
}
//this runs one round of the simulation
void Simulation::runSimulationRound(char modeToSim, int outputMode){
  for(int i = 0; i < simGrid->getRows(); ++i){
    for(int j = 0; j <simGrid->getColumns(); ++j){
      Cell calculatedCell = simGrid->getCellAt(i,j);
      float neighborsAlive = 0;
      if(modeToSim == 'c'){
        neighborsAlive = checkNeighborsClassic(i,j);//counts based off of classic rules
      }
      else if(modeToSim == 'm'){
        neighborsAlive = checkNeighborsMirror(i,j);//counts based off of mirror rules
      }
      else if(modeToSim == 'd'){
        neighborsAlive = checkNeighborsDoughnut(i,j);//counts based off of Doughnut rules
      }
      float oneLastNumber = calculatedCell.getOnePast(); //stores these variables in the cells for later use for seeing calculated state
      float twoLastNumber = calculatedCell.getTwoPast();
      //this function sees if the cell survives given the round number, state, and the past states
      bool futureCondition = checkSurvival(calculatedCell.getStatus(),neighborsAlive,oneLastNumber,twoLastNumber,mRoundCounter);
      calculatedCell.setNextStatus(futureCondition);//sets the cells future condition
      simGrid->setCellAtToNext(i,j,futureCondition);
      simGrid->setOnePastCellAt(i,j,neighborsAlive);
    }
  }
  for(int i = 0; i < simGrid->getRows(); ++i){
    for(int j = 0; j <simGrid->getColumns(); ++j){
      Cell cellToSwap = simGrid->getCellAt(i,j);
      simGrid->updateCell(i,j);// this acutally updates the cells after all of the states are calculated
    }
  }
}

//This function checks for the survival of a cell based off of its current value and the past values
bool Simulation::checkSurvival(bool currCondition, float currNeigAlive,float onePastNumber,float twoPastNumber,float numberOfRounds){
  bool toRet = false; // false is dead true is alive
  float averageAliveOverLastRounds = 0;
  if(numberOfRounds == 0){
    averageAliveOverLastRounds = currNeigAlive;
  }else if(numberOfRounds == 1){
    averageAliveOverLastRounds = (currNeigAlive + onePastNumber)/2;
  }else if(numberOfRounds > 1){
    averageAliveOverLastRounds = (currNeigAlive+onePastNumber+twoPastNumber)/3;
  }

  if(averageAliveOverLastRounds<1.5){
    toRet = false;
  }else if(averageAliveOverLastRounds < 2.5){
    if(currCondition){
      toRet = true;
    }else{
      toRet = false;
    }
  }else if(averageAliveOverLastRounds < 3.5){
    toRet = true;
  }else if(averageAliveOverLastRounds >3.5){
    toRet = false;
  }
  return toRet;
}

//classic mode checking for neighbors, does nothing with edges, they are empty
int Simulation::checkNeighborsClassic(int x,int y){
  int numberOfAliveNeigh=0;
  for(int i = -1; i < 2; i++){
    for(int j = -1; j < 2; j++){
      if(simGrid->getRows() > x + i && x + i >= 0){
        if(simGrid->getColumns() > y + j && y + j >= 0){
          if(simGrid->getCellValueAt(x+i,y+j)){
            numberOfAliveNeigh = numberOfAliveNeigh + 1;
          }
        }
      }
    }
  }
  if(simGrid->getCellValueAt(x,y)){
    numberOfAliveNeigh = numberOfAliveNeigh-1;
  }
  return numberOfAliveNeigh;
}

//Mirror mode checking for neighbors, if there is an edge its reflective so that it sees the cells in the map
int Simulation::checkNeighborsMirror(int x,int y){
  int numberOfAliveNeigh=0;
  for(int i = -1; i < 2; i++){
    for(int j = -1; j < 2; j++){
      if(simGrid->getRows() > x + i && x + i >= 0){
        if(simGrid->getColumns() > y + j && y + j >= 0){
          if(simGrid->getCellValueAt(x+i,y+j)){
            numberOfAliveNeigh = numberOfAliveNeigh + 1;
          }
        }else{
          int newY = y;
          if(simGrid->getCellValueAt(x+i,newY)){
            numberOfAliveNeigh = numberOfAliveNeigh + 1;
          }
        }
      }else{
        int newX = x;
        if(simGrid->getColumns() > y + j && y + j >= 0){
          if(simGrid->getCellValueAt(newX,y+j)){
            numberOfAliveNeigh = numberOfAliveNeigh + 1;
          }
        }else{
          int newY = y;
          if(simGrid->getCellValueAt(newX,newY)){
            numberOfAliveNeigh = numberOfAliveNeigh + 1;
          }
        }
      }
    }
  }
  if(simGrid->getCellValueAt(x,y)){
    numberOfAliveNeigh = numberOfAliveNeigh-1;
  }
  return numberOfAliveNeigh;
}

//Doughnut mode checking for neighbors, if ther is a edge it loops around to the other side and looks at that one
int Simulation::checkNeighborsDoughnut(int x,int y){
  int numberOfAliveNeigh=0;
  for(int i = -1; i < 2; i++){
    for(int j = -1; j < 2; j++){
      if(simGrid->getRows() > x + i && x + i >= 0){
        if(simGrid->getColumns() > y + j && y + j >= 0){
          if(simGrid->getCellValueAt(x+i,y+j)){
            numberOfAliveNeigh = numberOfAliveNeigh + 1;
          }
        }else{
          int newY;
          if(y+j>simGrid->getColumns()-1){
             newY = 0;
          }else{
            newY = simGrid->getColumns()-1;
          }
          if(simGrid->getCellValueAt(x+i,newY)){
            numberOfAliveNeigh = numberOfAliveNeigh + 1;
          }
        }
      }else{
        int newX;
        if(x+i>simGrid->getRows()-1){
           newX = 0;
        }else{
          newX = simGrid->getRows()-1;
        }
        if(simGrid->getColumns() > y + j && y + j >= 0){
          if(simGrid->getCellValueAt(newX,y+j)){
            numberOfAliveNeigh = numberOfAliveNeigh + 1;
          }
        }else{
          int newY;
          if(y+j>simGrid->getColumns()-1){
             newY = 0;
          }else{
            newY = simGrid->getColumns()-1;
          }
          if(simGrid->getCellValueAt(newX,newY)){
            numberOfAliveNeigh = numberOfAliveNeigh + 1;
          }
        }
      }
    }
  }
  if(simGrid->getCellValueAt(x,y)){
    numberOfAliveNeigh = numberOfAliveNeigh-1;
  }
  return numberOfAliveNeigh;
}
