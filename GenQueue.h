/*******************************
 * Andrew Dillon
 * 2382400
 * CPSC 350
 * Assignment 04
 *******************************/

 #ifndef GENQUEUE_H_
 #define GENQUEUE_H_

 #include "LinkedListInterface.h"

 template <class x>
 class GenQueue
 {
 public:
   //constructors and destructors
   GenQueue()
   {}
   ~GenQueue()
   {}

   //core functions
   void Enqueue(x newValue)
   {
      queue.InsertBack(newValue);
   }
   x Dequeue()
   {
     return queue.DeleteFront();
   }

   //aux functions
   x Peek()
   {
     return queue.GetFront() -> data;
   }
   bool IsFull()
   {
     return false;
   }
   bool IsEmpty()
   {
     return queue.IsEmpty();
   }
   unsigned int GetSize()
   {
     return queue.GetSize();
   }
   void PrintQueue(ostream& oFile)
   {
     queue.DisplayForwards(oFile);
   }

 private:
   LinkedListInterface<x> queue;
 };

 #endif // GENQUEUE_H_
