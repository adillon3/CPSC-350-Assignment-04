/*******************************
 * Andrew Dillon
 * 2382400
 * CPSC 350
 * Assignment 04
 *******************************/


 #ifndef REGISTRAR_H_
 #define REGISTRAR_H_

 #include "GenQueue.h"
 #include "Student.h"
 #include "Window.h"

 #include <string>
 #include <fstream>

 class Registrar
 {
public:
  //Constructors
  Registrar();
  Registrar(int numWindows);
  ~Registrar();


  void RunSimulation(string fileName, ostream& oFile);
  void ProcessFile(string fileName);
  void SetWindows(int numWindows);
  void DecrementAllStudentWindowTimes();
  int  FindNextEmptyWindow();

  //Stats functions
  //  Print Stats Functions
  void FindAndPrintStats(ostream& oFile);
  void FindAndPrintStudentStats(ostream& oFile);
  void FindAndPrintWindowStats(ostream& oFile);
  //  Calc Stat functions
  //    student stats
  float CalcMeanStudentWait();
  float CalcMedianStudentWait();
  int   LongestStudentWait();
  int   NumStudentsOver10Minutes();
  //    window stats
  int   MeanWindowIdleTime();
  int   LongestWindowIdleTime();
  int   NumWindowsOver5Minutes();


private:
  void UpdateWindowIdleTimes();

  GenQueue<Student> studentQueue;
  Window* windowArray;
  int numWindows;

  LinkedListInterface<int> studentWaitTimes;
  LinkedListInterface<int> windowIdleTimes;
 };

 #endif // REGISTRAR_H_
