#include <string>
#include <iostream>
#include <fstream>
#include "FileProcessor.h"

using namespace std;

//format is row, columns, grid
// 5
// 7
// ---X--X
// -X--X--
// -----XX
// X-X-X--
// -----XX
FileProcessor::FileProcessor(){

}
FileProcessor::~FileProcessor(){

}
//called for input file option in main
string FileProcessor::loadLineFromFile(string inputFile,int lineNumber){
  ifstream inFile;
  inFile.open (inputFile);
  if (!inFile.is_open()) {
    cout<<"Something went wrong, check the name of the file"<<endl;
  }
  string toRet = "";
  for (int i = 0; i < lineNumber;++i){
    getline(inFile, toRet);
  }
  inFile.close();
  return toRet;
}
//called for output file mode chosen in main
void FileProcessor::printToFile(string outputFile, string line){
    ofstream outFile;
    outFile.open (outputFile,std::ios_base::app);
    outFile<<line;
    outFile.close();
}

void FileProcessor::makeOutFile(string outputFile){
  ofstream outFile;
  outFile.open (outputFile);
  outFile.close();
}
