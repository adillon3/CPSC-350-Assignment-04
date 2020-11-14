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
}

Window :: ~Window()
{
  student = nullptr;
}

void Window :: SetStudent(Student* newStudent)
{
  student = newStudent;
}
Student* Window :: RemoveStudentIfDone()
{
  if(student != nullptr)
  {
    if(student -> GetWindowTime() <= 0)
    {
      Student* temp = student;
      student = nullptr;
      return temp;
    }
  }

  return nullptr;
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
