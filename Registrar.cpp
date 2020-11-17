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
  oFile << "Processing File: " << fileName << endl << endl;

  ProcessFile(fileName);
  Student temp;
  int currentTime = 0;
  //number of windows in array, numbered 1 to numWindows
  int availableWindows = numWindows;

  while(!studentQueue.IsEmpty())
  {

    while(!studentQueue.IsEmpty() && studentQueue.Peek().GetArrivalTime() <= currentTime /*&$ OPEN Window*/)
    {

      temp = studentQueue.Dequeue();

      studentWaitTimes.InsertBack(temp.GetWaitTime());

      //from 0 to less that number of windows
      int nextWindow = FindNextEmptyWindow();

      windowArray[nextWindow].SetStudent(temp);
    }

    ++currentTime;
  }

  cout << endl;
  FindAndPrintStats(oFile);
}//END void Registrar :: RunSimulation(string fileName, ostream& oFile)




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

      studentQueue.Enqueue(Student(currentTime, studentWindowTime));
    }
  }//END while(!inFile.eof())

}
void Registrar :: SetWindows(int newNumWindows)
{
  if(windowArray != nullptr)
  {
    delete[] windowArray;
  }

  windowArray = new Window[numWindows];

  numWindows = newNumWindows;
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
  int emptyWindow = -1;

  for(int i = 0; i < numWindows; ++i)
  {
    if(windowArray[i].IsIdle())
    {
      emptyWindow = i;
      break;
    }
  }
  return emptyWindow;
}




/******************************
 * Print Statistics Functions *
 ******************************/
void Registrar :: FindAndPrintStats(ostream& oFile)
{
  FindAndPrintStudentStats(oFile);
  //FindAndPrintWindowStats(oFile);
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
  //Does not include 0 wait times
  if(studentWaitTimes.GetSize() == 0)
  {
    return 0;
  }

  int sum = 0;

  for(int i = 0; i < studentWaitTimes.GetSize(); ++i)
  {
    if(studentWaitTimes.GetValueAtIndex(i) != 0)
    {
      sum += studentWaitTimes.GetValueAtIndex(i);
    }
  }

  return (float)sum / studentWaitTimes.GetSize();
}
float Registrar :: CalcMedianStudentWait()
{
  //number is even
  if(studentWaitTimes.GetSize() % 2 == 0)
  {
    int sum = studentWaitTimes.GetValueAtIndex((studentWaitTimes.GetSize() / 2));
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
  if(windowIdleTimes.GetSize() == 0)
  {
    return 0;
  }

  int sum = 0;

  for(int i = 0; i < windowIdleTimes.GetSize(); ++i)
  {
    sum += windowIdleTimes.GetValueAtIndex(i);
  }

  return (float)sum / windowIdleTimes.GetSize();
}
int Registrar :: LongestWindowIdleTime()
{
  if(windowIdleTimes.GetSize() == 0)
  {
    return 0;
  }

  int longestIdle = 0;

  for(int i = 0; i < windowIdleTimes.GetSize(); ++i)
  {
    if(windowIdleTimes.GetValueAtIndex(i) > longestIdle)
    {
      longestIdle = windowIdleTimes.GetValueAtIndex(i);
    }
  }

  return longestIdle;
}
int Registrar :: NumWindowsOver5Minutes()
{
  if(windowIdleTimes.GetSize() == 0)
  {
    return 0;
  }

  int numWindowsOver5 = 0;

  for(int i = 0; i < windowIdleTimes.GetSize(); ++i)
  {
    if(windowIdleTimes.GetValueAtIndex(i) >= 5)
    {
      ++numWindowsOver5;
    }
  }

  return numWindowsOver5;
}


void Registrar :: UpdateWindowIdleTimes()
{
  for(int i = 0; i < numWindows; ++i)
  {
    windowArray[i].UpdateWindowIdleTime();
  }
}
