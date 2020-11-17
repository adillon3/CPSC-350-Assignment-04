/*******************************
 * Andrew Dillon
 * 2382400
 * CPSC 350
 * Assignment 04
 *******************************/

 #ifndef STUDENT_H_
 #define STUDENT_H_

 #include "GenQueue.h"

 #include <iostream>
 using namespace std;
 #include <string>
 #include <fstream>

 class Student
 {
public:

  //constructors
  Student();
  Student(int newArrivalTime, int newWindowTime);
  Student(int newArrivalTime, int newWindowTime, int newWaitTime);

  int GetWindowTime();
  int GetWaitTime();
  int GetArrivalTime();
  void SetWindowTime(int newWindowTime);
  void SetWaitTime( int newWaitTime);
  void SetArrivalTime(int arrivalTime);
  void IncrementWaitTime();
  void DecrementWindowTime();

  //overloaded operators
  friend ostream& operator<<(ostream& oFile, const Student& object);

private:
  int arrivalTime;
  int windowTime;
  int waitTime;
 };

 #endif // STUDENT_H_
