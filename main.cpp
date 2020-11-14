/*******************************
 * Andrew Dillon
 * 2382400
 * CPSC 350
 * Assignment 04
 *******************************/

#include "GenQueue.h"
#include "Assign4.h"
#include "Registrar.h"

int main(int argc, char* argv[])
{
  string fileName;
  Registrar myRegistrar;

  //Getting input if commandline is blank
  if(argc < 2)
  {
    fileName = GetFileName();
  }
  else
  {
    fileName = argv[1];
  }

  CheckFileNameValid(fileName);


  myRegistrar.ProcessFile(fileName);
  //myRegistrar.RunSimulation(fileName, cout);


  cout << "\n\nEND\n\n";


  return 0;
}
