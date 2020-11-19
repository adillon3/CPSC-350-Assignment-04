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
  ~Registrar();

  //Core Methods
  void RunSimulation(string fileName, ostream& oFile);
  void ProcessFile(string fileName);
  int  FindNextEmptyWindow();
  void RemoveStudentsFromWindows();
  bool AllWindowsAreIdle();
  void SetWindows(int numWindows);
  void UpdateStudentWindowTimes();
  void UpdateWindowIdleTimes();



  //Stats functions
  //  Print Stats Functions
  void FindAndPrintStats(ostream& oFile, int currentTime);
  void FindAndPrintStudentStats(ostream& oFile);
  void FindAndPrintWindowStats(ostream& oFile);
  //  Calc Stat functions
  //    student stats
  float CalcMeanStudentWait();
  int   CalcMedianStudentWait();
  int   LongestStudentWait();
  int   NumStudentsOver10Minutes();
  //    window stats
  float CalcMeanWindowIdle();
  int   CalcMedianWindowIdle();
  int   LongestWindowIdle();
  int   NumWindowsOver5Minutes();

private:
  void MakeIdleList();

  GenQueue<Student> studentQueue;
  Window* windowArray;
  int numWindows;

  DoublyLinkedList<int> studentWaitTimes;
  DoublyLinkedList<int> windowIdleTimes;
 };

 #endif // REGISTRAR_H_
