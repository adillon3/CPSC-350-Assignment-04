/*******************************
 * Andrew Dillon
 * 2382400
 * CPSC 350
 * Assignment 04
 *******************************/


#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include "DoublyLinkedListNode.h"

//#include "DoublyLinkedList.h"

template <class x>
class LinkedListInterface
{
public:
  virtual void InsertFront(x newValue) = 0;
  virtual void InsertBack(x newValue) = 0;
  virtual x DeleteBack() = 0;
  virtual x DeleteFront() = 0;
  virtual x Delete(x key) = 0;
  virtual DoublyLinkedListNode<x>* Search(x key) = 0;
  virtual DoublyLinkedListNode<x>* GetFront() = 0;
  virtual DoublyLinkedListNode<x>* GetBack() = 0;
  virtual void DisplayForwards(ostream& oFile) = 0;
  virtual void DisplayBackwards(ostream& oFile) = 0;
  virtual bool IsEmpty() = 0;
  virtual bool GetSize() = 0;
  virtual x GetValueAtIndex(int index) = 0;


  /*
  LinkedListInterface()
  {}
  ~LinkedListInterface()
  {}

  void InsertFront(x newValue)
  {
    myList.InsertFront(newValue);
  }
  void InsertBack(x newValue)
  {
    myList.InsertBack(newValue);
  }
  x DeleteBack()
  {
    return myList.DeleteBack();
  }
  x DeleteFront()
  {
    return myList.DeleteFront();
  }
  x Delete(x key)
  {
    return myList.Delete(key);
  }
  DoublyLinkedListNode<x>* Search(x key)
  {
    return myList.Search(key);
  }
  DoublyLinkedListNode<x>* GetFront()
  {
    return myList.GetFront();
  }
  DoublyLinkedListNode<x>* GetBack()
  {
    return myList.GetBack();
  }
  void DisplayForwards(ostream& oFile)
  {
    myList.DisplayForwards(oFile);
  }
  void DisplayBackwards(ostream& oFile)
  {
    myList.DisplayBackwards(oFile);
  }
  bool IsEmpty()
  {
    myList.IsEmpty();
  }
  bool GetSize()
  {
    return myList.GetSize();
  }
  x GetValueAtIndex(int index)
  {
    return myList.GetValueAtIndex(index);
  }


*/

};

#endif // LINKEDLIST_H_
