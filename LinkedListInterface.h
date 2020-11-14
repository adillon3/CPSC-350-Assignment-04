/*******************************
 * Andrew Dillon
 * 2382400
 * CPSC 350
 * Assignment 04
 *******************************/


#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include "DoublyLinkedList.h"

template <class x>
class LinkedListInterface
{
public:
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




private:
  DoublyLinkedList<x> myList;
};

#endif // LINKEDLIST_H_
