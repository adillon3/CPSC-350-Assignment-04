/*******************************
 * Andrew Dillon
 * 2382400
 * CPSC 350
 * Assignment 04
 *******************************/

 #ifndef DOUBLYLINKEDLIST_H_
 #define DOUBLYLINKEDLIST_H_

#include "DoublyLinkedListNode.h"

template <class x>
class DoublyLinkedList
{
public:
  //constructors and destructors
  DoublyLinkedList()
  {
    head = nullptr;
    tail = nullptr;
    size = 0;
  }
  ~DoublyLinkedList()
  {
    head = nullptr;
    tail = nullptr;
  }

  void InsertFront(x newValue)
  {
    if(IsEmpty())
    {
      InsertEmptyList(newValue);
    }
    else
    {
      head -> prev = new DoublyLinkedListNode<x>;

      //concting the new node to the list
      head -> prev -> next = head;

      //setting head to new head
      head = head -> prev;

      //adding the value
      head -> data = newValue;
      ++size;
    }
  }
  void InsertBack(x newValue)
  {
    if(IsEmpty())
    {
      InsertEmptyList(newValue);
    }
    else
    {
      tail -> next = new DoublyLinkedListNode<x>;

      //concting the new node to the list
      tail -> next -> prev = tail;

      tail = tail -> next;

      //adding new value
      tail -> data = newValue;
      ++size;
    }
  }
  x DeleteBack()
  {
    if(IsEmpty())
    {
      throw "List Empty";
    }
    else if(size == 1)
    {
      return DeleteOnlyNode();
    }
    else
    {
      x returnVal = tail -> data;
      DoublyLinkedListNode<x>* temp = tail;

      tail -> prev -> next = nullptr;
      tail = tail -> prev;


      temp -> prev = nullptr;
      delete temp;

      //adjusting size
      --size;

      return returnVal;
    }
  }
  x DeleteFront()
  {
    if(IsEmpty())
    {
      throw "List Empty";
    }
    else if(size == 1)
    {
      return DeleteOnlyNode();
    }
    else
    {
      x returnVal = head -> data;
      DoublyLinkedListNode<x>* temp = head;

      head -> next -> prev = nullptr;
      head = head -> next;


      temp -> next = nullptr;
      delete temp;

      //adjusting size
      --size;

      return returnVal;
    }
  }
  x Delete(x key)
  {
    DoublyLinkedListNode<x>* temp = Search(key);

    if(temp == head)
    {
      DeleteFront();
    }
    else if (temp == tail)
    {
      DeleteBack();
    }
    else if(temp == nullptr)
    {
      throw "Not Found";
    }
    else if(size == 1)
    {
      return DeleteOnlyNode();
    }
    else
    {
      temp -> next -> prev = temp -> prev;
      temp -> prev -> next = temp -> next;

      --size;
    }
  }

  DoublyLinkedListNode<x>* Search(x key)
  {
    if(IsEmpty())
    {
      throw "List Empty";
    }

    DoublyLinkedListNode<x>* temp = head;

    while(temp && temp -> data != key)
    {
      temp = temp -> next;
    }

    return temp;
  }
  DoublyLinkedListNode<x>* GetFront()
  {
    return head;
  }
  DoublyLinkedListNode<x>* GetBack()
  {
    return tail;
  }

  void DisplayForwards(ostream& oFile)
  {
    oFile << "Forwards: ";
    if(size <= 0)
    {
      oFile << "List is Empty";
    }
    else
    {
      DoublyLinkedListNode<x>* temp = head;

      while(temp != tail)
      {
        oFile << temp -> data;
        oFile << " : ";
        temp = temp -> next;
      }

      oFile << tail -> data;
    }
  }
  void DisplayBackwards(ostream& oFile)
  {
    oFile << "Backwards: ";

    if(size < 0)
    {
      oFile << "List is Empty";
    }
    else
    {
      DoublyLinkedListNode<x>* temp = tail;

      while(temp -> prev != nullptr)
      {
        oFile << temp -> data;
        oFile << " : ";

        temp = temp -> prev;
      }

      oFile << head -> data;
    }
  }
  bool IsEmpty()
  {
    if(size == 0)
    {
      return true;
    }

    return false;
  }
  bool GetSize()
  {
    return size;
  }
  x GetValueAtIndex(int index)
  {
    if(index >= size)
    {
      throw "Index out of bounds";
    }

    DoublyLinkedListNode<x>* temp = head;

    for(int i = 0; i < index; ++i)
    {
      temp = temp -> next;
    }

    return temp -> data;
  }

private:
  void InsertEmptyList(x newValue)
  {
    head = new DoublyLinkedListNode<x>;
    head -> data = newValue;
    tail = head;
    ++size;
  }
  x DeleteOnlyNode()
  {
    x returnVal = head -> data;

    delete head;
    head = nullptr;
    tail = nullptr;
    --size;

    return returnVal;
  }

  DoublyLinkedListNode<x>* head;
  DoublyLinkedListNode<x>* tail;
  unsigned int size;

};


#endif // DOUBLYLINKEDLIST_H_
