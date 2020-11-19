/*******************************
 * Andrew Dillon
 * 2382400
 * CPSC 350
 * Assignment 04
 *******************************/

 #include "Student.h"


 Student :: Student()
 {
   arrivalTime = 0;
   windowTime = 0;
 }
 Student :: Student(int newArrivalTime, int newWindowTime)
 {
   arrivalTime = newArrivalTime;
   windowTime = newWindowTime;
 }
 Student :: Student(int newArrivalTime, int newWindowTime, int newWaitTime)
 {
   arrivalTime = newArrivalTime;
   windowTime = newWindowTime;
 }


 int Student :: GetWindowTime()
 {
   return windowTime;
 }
 int Student :: GetArrivalTime()
 {
   return arrivalTime;
 }

  void Student :: DecrementWindowTime()
  {
    --windowTime;
  }

 /*
 void SetWindowTime(int newWindowTime);
 void SetArrivalTime(int arrivalTime);
 void IncrementWaitTime();


 //overloaded operators
 friend ostream& operator<<(ostream& oFile, const Student& object);

 */



 ostream& operator<<(ostream& oFile, const Student& student)
 {
    oFile << "Student arrived at: " << student.arrivalTime << endl;
    oFile << "Window time is    : " << student.windowTime << endl;
    oFile << endl;
 }

 bool operator==(const Student& student1, const Student& student2)
 {
   return (student1.arrivalTime == student2.arrivalTime && student1.windowTime == student2.windowTime);
 }
 bool operator!=(const Student& student1, const Student& student2)
 {
   return (student1.arrivalTime != student2.arrivalTime || student1.windowTime != student2.windowTime);
 }
