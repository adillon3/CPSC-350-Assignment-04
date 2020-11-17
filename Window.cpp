/*******************************
 * Andrew Dillon
 * 2382400
 * CPSC 350
 * Assignment 04
 *******************************/

#include "Window.h"

Window :: Window()
{
  student = nullptr;
  idleTimeCounter = 0;
  longestIdleTime = 0;
}

Window :: ~Window()
{
  student = nullptr;
}

void Window :: SetStudent(Student newStudent)
{
  //delete student;
  student = new Student(newStudent.GetArrivalTime(), newStudent.GetWindowTime(), newStudent.GetWaitTime());
}
bool Window :: RemoveStudentIfDone()
{
  if(student != nullptr)
  {
    if(student -> GetWindowTime() <= 0)
    {
      student = nullptr;
      return true;
    }
  }

  return false;
}



void Window :: DecrementStudentWindowTime()
{
  student -> DecrementWindowTime();
}

bool Window :: IsIdle()
{
  if(student == nullptr)
  {
    return true;
  }

  return false;
}

int Window :: UpdateWindowIdleTime()
{
  if(IsIdle())
  {
    ++idleTimeCounter;
  }
  else
  {
    idleTimeCounter = 0;
  }
}
