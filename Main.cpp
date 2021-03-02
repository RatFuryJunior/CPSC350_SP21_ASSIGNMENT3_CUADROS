#include <iostream>
#include "Simulation.h"

using namespace std;

int main(int argc, char **argv) {
  cout<<"Welcome to the program... Would you like to create a random grid or import a grid?"<<endl;;
  cout<<"Type 1 for random, type 2 for importing from a file"<<endl;
  int userGenChoice = 0;
  cin >> userGenChoice;
  cout<<"What boundery mode? Classic, Doughnut, or Mirror..."<<endl;
  cout<<"Type 1 for Classic, 2 for Doughnut, 3 for Mirror"<<endl;
  int userModeChoice = 0;
  cin >> userModeChoice;
  cout<<"Do you want the program to briefly pause, wait for enter, or output to file?"<<endl;
  cout<<"Type 1 for brief pause, 2 for using enter, 3 for outputing to a file"<<endl;
  int userOutputChoice = 0;
  cin >> userOutputChoice;

  Simulation sim1 = Simulation(userGenChoice,userModeChoice,userOutputChoice);

  return 0;
}
