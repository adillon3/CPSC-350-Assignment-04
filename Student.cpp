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
   waitTime = 0;
 }

 Student :: Student(int newArrivalTime, int newWindowTime)
 {
   arrivalTime = newArrivalTime;
   windowTime = newWindowTime;
   waitTime = 0;
 }

 Student :: Student(int newArrivalTime, int newWindowTime, int newWaitTime)
 {
   arrivalTime = newArrivalTime;
   windowTime = newWindowTime;
   waitTime = newWaitTime;
 }

 int Student :: GetWindowTime()
 {
   return windowTime;
 }
 int Student :: GetWaitTime()
 {
   return waitTime;
 }
 int Student :: GetArrivalTime()
 {
   return arrivalTime;
 }
 void Student :: SetWindowTime(int newWindowTime)
 {
   windowTime = newWindowTime;
 }
void Student :: SetWaitTime(int newWaitTime)
 {
   waitTime = newWaitTime;
 }
 void Student :: SetArrivalTime(int newArrivalTime)
 {
   arrivalTime = newArrivalTime;
 }


 void Student :: IncrementWaitTime()
 {
   ++waitTime;
 }
 void Student :: DecrementWindowTime()
 {
   --windowTime;
 }



 ostream& operator<<(ostream& oFile, const Student& student)
 {
    oFile << "Student arrived at: " << student.arrivalTime << endl;
    oFile << "Window time is    : " << student.windowTime << endl;
    oFile << endl;
 }
