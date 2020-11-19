  /*******************************
 * Andrew Dillon
 * 2382400
 * CPSC 350
 * Assignment 04
 *******************************/

//#include "GenQueue.h"
#include "Assign4.h"
#include "Registrar.h"

int main(int argc, char* argv[])
{
  const string YES_NO_MESSAGE = "Would you like to check another file?";

  string fileName;


  cout << "\nWelcome to the...\n\n";
  cout << "************************\n";
  cout << "* REGISTRAR SIMULATION *\n";
  cout << "************************\n\n";

  //Getting input if commandline is blank
  if(argc < 2)
  {
    fileName = GetFileName();
  }
  else
  {
    fileName = argv[1];
  }



  do
  {
    CheckFileNameValid(fileName);


    //MOVE THIS TO TOP???
    Registrar myRegistrar;
    myRegistrar.RunSimulation(fileName, cout);


    cout << endl << endl;
    if(GetYesOrNoInput(YES_NO_MESSAGE))
    {
      fileName = GetFileName();
    }
    else
    {
      break;
    }

  } while(true);



  cout << "\n\nThank you for using my program!\n\n";


  return 0;
}
