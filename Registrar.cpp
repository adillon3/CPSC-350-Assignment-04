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
 Registrar :: ~Registrar()
 {
   delete[] windowArray;
 }

 /***************
  * Core Methods*
  ***************/
 void Registrar :: RunSimulation(string fileName, ostream& oFile)
 {
   oFile << "**********************\n";
   oFile << "* Running Simulation *\n";
   oFile << "**********************\n\n";

   oFile << "Processing " << fileName << "...\n\n";

   try
   {
     ProcessFile(fileName);
   }
   catch(char const* myString)
   {
     oFile << myString;
     return;
   }

   oFile << "Simulating Registrar...\n\n";

   Student temp;

   int currentTime = 0;

   //while there are students to process and or there are students at a window
   while(true) //while(!studentQueue.IsEmpty() ||  !AllWindowsAreIdle())
   {
     RemoveStudentsFromWindows();

     while(!studentQueue.IsEmpty() && studentQueue.Peek().GetArrivalTime()  <= currentTime)
     {
       int nextWindow = FindNextEmptyWindow();

       if(nextWindow != -1)
       {
         //Removing student from Queue
         temp = studentQueue.Dequeue();

         //finding student wait time (current time - student arrival time)
         studentWaitTimes.InsertBack(currentTime - temp.GetArrivalTime());

         //Adding student to window
         windowArray[nextWindow].SetStudent(temp);
       }
       else
       {
         break;
       }
     }


     //updating times if not the end of the loop
     if(!studentQueue.IsEmpty() ||  !AllWindowsAreIdle())
     {
       ++currentTime;
       UpdateStudentWindowTimes();
       if(!studentQueue.IsEmpty())
       {
         UpdateWindowIdleTimes();
       }

     }
     else
     {
       break;
     }

   }//END while(true) //while(!studentQueue.IsEmpty() ||  !AllWindowsAreIdle())


   MakeIdleList();

   FindAndPrintStats(oFile, currentTime);
 }
void Registrar :: ProcessFile(string fileName)
{
 int arrivalTime;
 int numStudentsAtTime;
 int studentWindowTime;


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

 while(true)
 {
   //Getting student arrival time
   inFile >> arrivalTime;
   if(inFile.eof())
   {
     break;
   }
   if(inFile.fail())
   {
     inFile.clear();
     inFile.ignore(100000000, '\n');
     throw "Sorry, file not formatted correctly\n";
   }

   //getting number of studnts to arrive
   inFile >> numStudentsAtTime;
   if(inFile.fail())
   {
     inFile.clear();
     inFile.ignore(100000000, '\n');
     throw "Sorry, file not formatted correctly\n";
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
       throw "Sorry, file not formatted correctly\n";
     }

     studentQueue.Enqueue(Student(arrivalTime, studentWindowTime));
   }//for(int i = 0; i < numStudentsAtTime; ++i)
 }//END while(!inFile.eof())

 inFile.close();
}
int  Registrar :: FindNextEmptyWindow()
{
  for(int i = 0; i < numWindows; ++i)
  {
    if(windowArray[i].IsIdle())
    {
      return i;
    }
  }
  return -1;
}
void Registrar :: RemoveStudentsFromWindows()
{
  for(int i = 0; i < numWindows; ++i)
  {
    windowArray[i].RemoveStudentIfDone();
  }
}
bool Registrar :: AllWindowsAreIdle()
{
  for(int i = 0; i < numWindows; ++i)
  {
    if(!windowArray[i].IsIdle())
    {
      return false;
    }
  }

  return true;
}
void Registrar :: SetWindows(int numWindows)
{
  if(windowArray != nullptr)
  {
    delete[] windowArray;
  }

  windowArray = new Window[numWindows];

}
void Registrar :: UpdateStudentWindowTimes()
{
  for(int i = 0; i < numWindows; ++i)
  {
    //If there is student a student at the window
    if(!windowArray[i].IsIdle())
    {
      windowArray[i].DecrementStudentWindowTime();
    }
  }
}
void Registrar :: UpdateWindowIdleTimes()
{
  for(int i = 0; i < numWindows; ++i)
  {
    if(windowArray[i].IsIdle())
    {
      windowArray[i].UpdateWindowIdleTime();
    }
  }
}




/******************************
 * Print Statistics Functions *
 ******************************/
void Registrar :: FindAndPrintStats(ostream& oFile, int currentTime)
{
  oFile << "***********\n";
  oFile << "* Metrics *\n";
  oFile << "***********\n\n";

  oFile << "Time Last Student Finishes:        " <<  currentTime << endl << endl;

  FindAndPrintStudentStats(oFile);
  oFile << endl;
  FindAndPrintWindowStats(oFile);
}
void Registrar :: FindAndPrintStudentStats(ostream& oFile)
{
  oFile << "Student Metrics:\n";

  oFile << " - Number of Students Attended To: " << studentWaitTimes.GetSize() << endl;
  oFile << " - The Mean Student Wait Time:     " << CalcMeanStudentWait() << endl;
  oFile << " - The Median Student Wait Time:   " << CalcMedianStudentWait() << endl;
  oFile << " - The Longest Student Wait Time:  " << LongestStudentWait() << endl;
  oFile << " - The Number of Students  " << endl;
  oFile << "   Waiting More Than 10 Minutes:   " << NumStudentsOver10Minutes() << endl;
}
void Registrar :: FindAndPrintWindowStats(ostream& oFile)
{
  oFile << "Window Metrics:\n";

  oFile << " - Number of Windows Simulated:    " << windowIdleTimes.GetSize() << endl;
  oFile << " - The Mean Window Idle Time:      " << CalcMeanWindowIdle() << endl;
  oFile << " - Median Window Idle Time:        " << CalcMedianWindowIdle() << endl;
  oFile << " - The Longest Window Idle Time:   " << LongestWindowIdle() << endl;
  oFile << " - The Number of Windows" << endl;
  oFile << "   Idle For More Than 5 Minutes:   " << NumWindowsOver5Minutes() << endl;
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
  int numberOfWaits = 0;

  for(int i = 0; i < studentWaitTimes.GetSize(); ++i)
  {
    if(studentWaitTimes.GetValueAtIndex(i) != 0)
    {
      sum += studentWaitTimes.GetValueAtIndex(i);
      ++numberOfWaits;
    }
  }

  if(numberOfWaits == 0)
  {
    return 0;
  }

  return (float)sum / numberOfWaits;
}
int Registrar :: CalcMedianStudentWait()
{
  //empty list
  if(studentWaitTimes.IsEmpty())
  {
    return 0;
  }
  //number is even and non zero
  if(studentWaitTimes.GetSize() % 2 == 0)
  {
    int mid1 = studentWaitTimes.GetValueAtIndex((studentWaitTimes.GetSize() / 2));
    int mid2 = studentWaitTimes.GetValueAtIndex((studentWaitTimes.GetSize() / 2) - 1);

    if(mid1 < mid2)
    {
      return mid1;
    }
    else
    {
      return mid2;
    }
  }//if(studentWaitTimes.GetSize() % 2 == 0)
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
    if(studentWaitTimes.GetValueAtIndex(i) > 10)
    {
      ++numOver10;
    }
  }

  return numOver10;
}
//window stat functions
float Registrar :: CalcMeanWindowIdle()
{
  if(windowIdleTimes.GetSize() == 0)
  {
    return 0;
  }

  int sum = 0;
  int numberOfWaits = 0;

  for(int i = 0; i < numWindows; ++i)
  {
    if(windowIdleTimes.GetValueAtIndex(i) >= 0)
    {
      sum += windowIdleTimes.GetValueAtIndex(i);
      ++numberOfWaits;
    }
  }

  if(numberOfWaits == 0)
  {
    return 0;
  }

  return (float)sum / numberOfWaits;
}
int Registrar :: CalcMedianWindowIdle()
{
  //empty list
  if(windowIdleTimes.IsEmpty())
  {
    return 0;
  }
  //number is even and non zero
  else if(windowIdleTimes.GetSize() % 2 == 0)
  {
    //cerr << "finding
    int mid1 = windowIdleTimes.GetValueAtIndex((windowIdleTimes.GetSize() / 2));
    int mid2 = windowIdleTimes.GetValueAtIndex((windowIdleTimes.GetSize() / 2) - 1);

    if(mid1 < mid2)
    {
      return mid1;
    }
    else
    {
      return mid2;
    }
  }//if(windowIdleTimes.GetSize() % 2 == 0)
  //number is odd
  else
  {
    return windowIdleTimes.GetValueAtIndex((windowIdleTimes.GetSize() / 2));
  }
}
int Registrar :: LongestWindowIdle()
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
    if(windowIdleTimes.GetValueAtIndex(i) > 5)
    {
      ++numWindowsOver5;
    }
  }

  return numWindowsOver5;
}

/**************************
 * Private/Helper Methods *
 **************************/
void Registrar :: MakeIdleList()
{
  for(int i = 0; i < numWindows; ++i)
  {
    windowIdleTimes.InsertBack(windowArray[i].GetIdleTimeCounter());
  }
}
