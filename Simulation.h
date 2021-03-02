#include "Grid.h"
#include "FileProcessor.h"

using namespace std;

class Simulation{
  public:
    Simulation();
    Simulation(int genType, int mode, int outputMode);
    ~Simulation();
    void loadFromMap();
    void runSimulation(char modeToSim, int outputMode);
    void runSimulationRound(char modeToSim, int outputMode);
    bool checkSurvival(bool currCondition, float currNeigAlive,float onePastNumber,float twoPastNumber,float numberOfRounds);
    int checkNeighborsClassic(int x,int y);
    int checkNeighborsMirror(int x,int y);
    int checkNeighborsDoughnut(int x,int y);
    void setLastGrid();
    void setGridPastLastGrid();
    char mMode;
    bool **lastGrid;
    bool **pastLastGrid;
    bool **pastLastLastGrid;
  protected:
    FileProcessor gridFileProc;
    Grid *simGrid;
    int mRoundCounter;
};
