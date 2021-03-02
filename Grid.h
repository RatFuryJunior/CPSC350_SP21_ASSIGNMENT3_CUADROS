#include "Cell.h"
#include <string>

using namespace std;

class Grid{
  public:
    Grid();
    Grid(int x, int y);
    ~Grid();

    Cell getCellAt(int x, int y);
    bool getCellValueAt(int x, int y);
    void setCellAt(int x, int y, bool setTo);
    void setCellAtToNext(int x, int y,bool nextStatus);
    void updateCell(int x, int y);
    void setOnePastCellAt(int x, int y, float onePastFloat);
    void generateRandomGrid(float density);
    string printGrid();
    int getRows();
    int getColumns();
  protected:

    Cell ** theGrid;
    int mRows;
    int mColumns;
};
