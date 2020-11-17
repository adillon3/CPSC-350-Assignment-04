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
}
Window :: ~Window()
{
  delete student;
}

void Window :: SetStudent(Student newStudent)
{
  student = new Student(newStudent.GetArrivalTime(), newStudent.GetWindowTime());
}

bool Window :: IsIdle()
{
  if(student == nullptr)
  {
    return true;
  }
  else
  {
    return false;
  }
}

int Window:: UpdateWindowIdleTime()
{
  if(IsIdle())
  {
    ++idleTimeCounter;
  }
}
int Window:: GetIdleTimeCounter()
{
  return idleTimeCounter;
}
void Window:: RemoveStudentIfDone()
{
  if(student == nullptr)
  {
    return;
  }
  else
  {
    if(student -> GetWindowTime() == 0)
    {
      delete student;
      student = nullptr;
    }
  }
}

void Window :: DecrementStudentWindowTime()
{
  if(student == nullptr)
  {
    return;
  }
  else
  {
    student -> DecrementWindowTime();
  }
}
/*int  GetIdleTimeCounter();



bool IsIdle();

*/
