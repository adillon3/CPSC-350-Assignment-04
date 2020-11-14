/*******************************
 * Andrew Dillon
 * 2382400
 * CPSC 350
 * Assignment 04
 *******************************/

 #ifndef WINDOW_H_
 #define WINDOW_H_

 #include "GenQueue.h"
 #include "Student.h"

 class Window
 {
public:
  Window();
  ~Window();

  void SetStudent(Student* newStudent);
  Student* RemoveStudentIfDone();

  void DecrementStudentWindowTime();
  bool IsIdle();
private:
  Student* student;
 };

 #endif // WINDOW_H_
