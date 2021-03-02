#include <string>
#include <iostream>

using namespace std;

class FileProcessor{
  public:
    FileProcessor();
    ~FileProcessor();
    string loadLineFromFile(string inputFile, int lineNumber);
   void printToFile(string outputFile, string line);
   void makeOutFile(string outputFile);
};
