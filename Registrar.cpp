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
   ProcessFile(fileName);

   Student temp;

   int currentTime = 0;

   while(!studentQueue.IsEmpty())
   {
     string myString;
     //getline(cin, myString);

     cerr << "while(!studentQueue.IsEmpty())\n";
     cerr << "==========================CURRENT TIME: " << currentTime << endl;
     studentQueue.PrintQueue(oFile);


     RemoveStudentsFromWindows();

     while(!studentQueue.IsEmpty() && studentQueue.Peek().GetArrivalTime()  <= currentTime)
     {
       cerr << " while(!studentQueue.IsEmpty() && studentQueue.Peek().GetArrivalTime()  <= currentTime)\n";
       studentQueue.PrintQueue(oFile);

       int nextWindow = FindNextEmptyWindow();
       cerr << " NEXT WINDOW: " << nextWindow << endl;

       if(nextWindow != -1)
       {
         //Removing student from Queue
         temp = studentQueue.Dequeue();

         //finding student wait time (current time - student arrival time)
         studentWaitTimes.InsertBack(currentTime - temp.GetArrivalTime());

         cerr << "\n + ADDING: " << (currentTime - temp.GetArrivalTime()) << "++++++++++++++++++++++++++++++++++++++++\n";
         cerr << "()()()()()()()()()()()()()()()()()()()()studentWaitTimes.GetSize(): " << studentWaitTimes.GetSize() << endl;
         studentWaitTimes.DisplayForwards(oFile);
         cerr << endl;

         //Adding student to window
         windowArray[nextWindow].SetStudent(temp);
       }
       else
       {
         break;
       }
       studentQueue.PrintQueue(oFile);
     }


     //updating times
     ++currentTime;
     UpdateWindowIdleTimes();
     UpdateStudentWindowTimes();
   }//while(!studentQueue.IsEmpty())


   MakeIdleList();



   FindAndPrintStats(oFile);
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

     studentQueue.Enqueue(Student(arrivalTime, studentWindowTime));
   }//for(int i = 0; i < numStudentsAtTime; ++i)
 }//END while(!inFile.eof())

 inFile.close();
}
int  Registrar :: FindNextEmptyWindow()
{
  cerr << " * Entering FindNextEmptyWindow()\n";

  for(int i = 0; i < numWindows; ++i)
  {
    cerr << "for(int i = 0; i < numWindows; ++i)\n";
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
  oFile << "The Mean Window Idle Time:     " << MeanWindowIdleTime() << endl;
  oFile << "The Longest Window Idle Time:  " << LongestWindowIdleTime() << endl;
  oFile << "The Number of Windows" << endl;
  oFile << "Idle For More Than 5 Minutes:  " << NumWindowsOver5Minutes() << endl;
}

/*****************************
 * Calc Statistics Functions *
 *****************************/
 //student stat fucntions
float Registrar :: CalcMeanStudentWait()
{
  cerr << "CalcMeanStudentWait()\n\n";

  //Does not include 0 wait times
  if(studentWaitTimes.GetSize() == 0)
  {
    cerr << "No Wait Times";
    return 0;
  }

  int sum = 0;

  cerr << "SIZE: " << studentWaitTimes.GetSize();

  for(int i = 0; i < studentWaitTimes.GetSize(); ++i)
  {
    cerr << "for(int i = 0; i < studentWaitTimes.GetSize(); ++i)\n";
    if(studentWaitTimes.GetValueAtIndex(i) != 0)
    {
      sum += studentWaitTimes.GetValueAtIndex(i);
    }
  }

  return (float)sum / studentWaitTimes.GetSize();
}
int Registrar :: CalcMedianStudentWait()
{
  //number is even
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
    if(studentWaitTimes.GetValueAtIndex(i))
    {
      ++numOver10;
    }
  }

  return numOver10;
}
//window stat functions
float Registrar :: MeanWindowIdleTime()
{
  if(windowIdleTimes.GetSize() == 0)
  {
    cerr << "SIZE = 0 \n\n";
    return 0;
  }

  int sum = 0;

  for(int i = 0; i < numWindows; ++i)
  {
    if(windowIdleTimes.GetValueAtIndex(i) >= 0)
    {
      sum += windowIdleTimes.GetValueAtIndex(i);
    }
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
