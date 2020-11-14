/*******************************
 * Andrew Dillon
 * 2382400
 * CPSC 350
 * Assignment 04
 *******************************/

#include "Registrar.h"

/*****************************
 * Constructors & Destructors*
 *****************************/
Registrar :: Registrar()
{
  windowArray = nullptr;
  numWindows = 0;
}
Registrar :: Registrar(int newNumWindows)
{
  SetWindows(numWindows);
  numWindows = newNumWindows;
}
Registrar :: ~Registrar()
{
  delete[] windowArray;
}

/*********************
 * Primary Functions *
 *********************/
void Registrar :: RunSimulation(string fileName, ostream& oFile)
{
  ProcessFile(fileName);
  Student* temp;
  int longestWait = 0;
  int numStudentsOver10Minutes = 0;

  int currentTime = 0;
  int availableWindows = numWindows;

  //attend to students when there are still students waiting
  //quit loop when queue empty and display stats
  while(!studentQueue.IsEmpty())
  {
    //Check if any students are done at thir window
    //    if so remove them from the window
    //        incrememnt availableWindows

    for(int i = 0; i < numWindows; ++i)
    {
      temp = windowArray[i].RemoveStudentIfDone();

      if(temp != nullptr)
      {
        ++availableWindows;
      }
    }

    //if there is an open window, check the queue
    //    if next student "has arrived" by this time,  put them in the next available window
    //
    while((studentQueue.Peek()->GetArrivalTime() >= currentTime) && (availableWindows > 0))
    {
      //decrement availableWindows
      int nextWindow = FindNextEmptyWindow();

      if(nextWindow >= 0)
      {
        windowArray[nextWindow].SetStudent(studentQueue.Dequeue());

        --availableWindows;
      }
      else
      {
        throw "Error finding next window";
      }
    }


    ++currentTime;
    DecrementAllStudentWindowTimes();
  }


  temp = studentQueue.Dequeue();

  studentWaitTimes.InsertBack(temp -> GetWaitTime());


  FindAndPrintStats(oFile);


}
void Registrar :: ProcessFile(string fileName)
{
  int numWindows;
  ifstream inFile;
  inFile.open(fileName.c_str());

  inFile >> numWindows;
  if(inFile.fail())
  {
    inFile.clear();
    inFile.ignore(100000000, '\n');
    cout << "Sorry, file contains non numeric input.\n";
  }

  SetWindows(numWindows);

  int currentTime;
  int numStudentsAtTime;
  int studentWindowTime;


  while(true)
  {
    //Getting student arrival time
    inFile >> currentTime;
    if(inFile.eof())
    {
      break;
    }
    if(inFile.fail())
    {
      inFile.clear();
      inFile.ignore(100000000, '\n');
      cout << "Sorry, file contains non numeric input.\n";
    }

    //getting number of studnts to arrive
    inFile >> numStudentsAtTime;
    if(inFile.fail())
    {
      inFile.clear();
      inFile.ignore(100000000, '\n');
      cout << "Sorry, file contains non numeric input.\n";
    }

    //getting amount of time each student will spend at the window
    //  and adding them to the queue
    for(int i = 0; i < numStudentsAtTime; ++i)
    {
      inFile >> studentWindowTime;
      if(inFile.fail())
      {
        inFile.clear();
        inFile.ignore(100000000, '\n');
        cout << "Sorry, file contains non numeric input.\n";
      }

      studentQueue.Enqueue(new Student(currentTime, studentWindowTime));
    }
  }//END while(!inFile.eof())


  studentQueue.PrintQueue(cout);
}
void Registrar :: SetWindows(int numWindows)
{
  if(windowArray != nullptr)
  {
    delete[] windowArray;
  }

  windowArray = new Window[numWindows];
}
void Registrar :: DecrementAllStudentWindowTimes()
{
  for(int i = 0; i < numWindows; ++i)
  {
    windowArray[i].DecrementStudentWindowTime();
  }
}
int Registrar :: FindNextEmptyWindow()
{
  int emptyWindow;

  for(int i = 0; i < numWindows; ++i)
  {
    if(windowArray[i].IsIdle())
    {
      emptyWindow = i;
      break;
    }
  }

  if(emptyWindow >= numWindows)
  {
    emptyWindow = -1;
  }

  return emptyWindow;
}




/******************************
 * Print Statistics Functions *
 ******************************/
void Registrar :: FindAndPrintStats(ostream& oFile)
{
  FindAndPrintStudentStats(oFile);
  FindAndPrintWindowStats(oFile);
}
void Registrar :: FindAndPrintStudentStats(ostream& oFile)
{
  oFile << "The Mean Student Wait Time:    " << CalcMeanStudentWait() << endl;
  oFile << "The Median Student Wait Time:  " << CalcMedianStudentWait() << endl;
  oFile << "The Longest Student Wait Time: " << LongestStudentWait() << endl;
  oFile << "The Number of Students  " << endl;
  oFile << "Waiting More Than 10 Minutes:  " << NumStudentsOver10Minutes() << endl;
}
void Registrar :: FindAndPrintWindowStats(ostream& oFile)
{
  oFile << "The Mean Window Idle Time:    " << MeanWindowIdleTime() << endl;
  oFile << "The Longest Window Idle Time: " << LongestWindowIdleTime() << endl;
  oFile << "The Number of Windows" << endl;
  oFile << "Idle For More Than 5 Minutes: " << NumWindowsOver5Minutes() << endl;
}

/*****************************
 * Calc Statistics Functions *
 *****************************/
 //student stat fucntions
float Registrar :: CalcMeanStudentWait()
{
  int sum = 0;

  for(int i = 0; i < studentWaitTimes.GetSize(); ++i)
  {
    sum += studentWaitTimes.GetValueAtIndex(i);
  }

  return (float)sum / studentWaitTimes.GetSize();
}
float Registrar :: CalcMedianStudentWait()
{
  //number is even
  if(studentWaitTimes.GetSize() % 2 == 0)
  {
    unsigned int sum = studentWaitTimes.GetValueAtIndex((studentWaitTimes.GetSize() / 2));
    sum += studentWaitTimes.GetValueAtIndex((studentWaitTimes.GetSize() / 2) -1 );

    return sum / 2.0;
  }
  //number is odd
  else
  {
    return studentWaitTimes.GetValueAtIndex((studentWaitTimes.GetSize() / 2));
  }
}
int Registrar :: LongestStudentWait()
{
  unsigned int longestWait = 0;

  for(int i = 0; i < studentWaitTimes.GetSize(); ++i)
  {
    if(studentWaitTimes.GetValueAtIndex(i) > longestWait)
    {
      longestWait = studentWaitTimes.GetValueAtIndex(i);
    }
  }

  return longestWait;
}
int Registrar :: NumStudentsOver10Minutes()
{
  unsigned int numOver10 = 0;

  for(int i = 0; i < studentWaitTimes.GetSize(); ++i)
  {
    if(studentWaitTimes.GetValueAtIndex(i))
    {
      ++numOver10;
    }
  }

  return numOver10;
}
//window stat functions
int Registrar :: MeanWindowIdleTime()
{
  return 0;
}
int Registrar :: LongestWindowIdleTime()
{
  return 0;
}
int Registrar :: NumWindowsOver5Minutes()
{
  return 0;
}
