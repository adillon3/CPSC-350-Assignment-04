/*******************************
 * Andrew Dillon
 * 2382400
 * CPSC 350
 * Assignment 04
 *******************************/

 #ifndef DOUBLYLINKEDLISTNODE_H_
 #define DOUBLYLINKEDLISTNODE_H_

#include "Student.h"

#include <iostream>
using namespace std;

template <class x>
class DoublyLinkedListNode
{
public:
  //constructors and destructors
  DoublyLinkedListNode()
  {
    next = nullptr;
    prev = nullptr;
  }

  DoublyLinkedListNode(x newData)
  {
    next = nullptr;
    prev = nullptr;
    data = newData;
  }

  ~DoublyLinkedListNode()
  {
    delete next;
    delete prev;
  }


  DoublyLinkedListNode* next;
  DoublyLinkedListNode* prev;
  x data;
};

#endif // DOUBLYLINKEDLISTNODE_H_
