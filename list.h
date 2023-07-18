// Fig. 21.4: list.h
// Template List class definition.
#ifndef LIST_H
#define LIST_H

#include <iostream>

using std::cout;

#include <new>
#include "listnode.h" // ListNode class definition

template <class NODETYPE>
class List
{

public:
   List();              // constructor
   List(const List &t); // copy constructor
   ~List();             // destructor
   void insertAtFront(const NODETYPE &);
   void insertMiddle(const NODETYPE &, int x);
   bool removeMiddle(const NODETYPE &, int x);
   void insertAtBack(const NODETYPE &);
   bool removeFromFront(NODETYPE &);
   bool removeFromBack(NODETYPE &);
   bool isEmpty() const;
   void print() const;
   void operator=(const List<NODETYPE> &s);

private:
   ListNode<NODETYPE> *firstPtr; // pointer to first node
   ListNode<NODETYPE> *lastPtr;  // pointer to last node

   // utility function to allocate new node
   ListNode<NODETYPE> *getNewNode(const NODETYPE &);

}; // end class List

// default constructor
template <class NODETYPE>
List<NODETYPE>::List()
    : firstPtr(0),
      lastPtr(0)
{
   // empty body

} // end List constructor

template <class NODETYPE>
List<NODETYPE>::List(const List &t)
{
   *this = t;
}

// destructor
template <class NODETYPE>
List<NODETYPE>::~List()
{
   if (!isEmpty())
   { // List is not empty
      //      cout << "Destroying nodes ...\n";

      ListNode<NODETYPE> *currentPtr = firstPtr;
      ListNode<NODETYPE> *tempPtr;

      while (currentPtr != 0) // delete remaining nodes
      {
         tempPtr = currentPtr;

         // commented out the output -- no need to print what we are deallocating
         //         cout << tempPtr->data << '\n';

         currentPtr = currentPtr->nextPtr;
         delete tempPtr;
      }
   }

   //   cout << "All nodes destroyed\n\n";

} // end List destructor

// insert node at front of list
template <class NODETYPE>
void List<NODETYPE>::insertAtFront(const NODETYPE &value)
{
   ListNode<NODETYPE> *newPtr = getNewNode(value);

   if (isEmpty()) // List is empty
      firstPtr = lastPtr = newPtr;

   else
   { // List is not empty
      newPtr->nextPtr = firstPtr;
      firstPtr = newPtr;

   } // end else

} // end function insertAtFront

// insert node at back of list
template <class NODETYPE>
void List<NODETYPE>::insertAtBack(const NODETYPE &value)
{
   ListNode<NODETYPE> *newPtr = getNewNode(value);

   if (isEmpty()) // List is empty
      firstPtr = lastPtr = newPtr;

   else
   { // List is not empty
      lastPtr->nextPtr = newPtr;
      lastPtr = newPtr;

   } // end else

} // end function insertAtBack

// delete node from front of list
template <class NODETYPE>
bool List<NODETYPE>::removeFromFront(NODETYPE &value)
{
   if (isEmpty())   // List is empty
      return false; // delete unsuccessful

   else
   {
      ListNode<NODETYPE> *tempPtr = firstPtr;

      if (firstPtr == lastPtr)
         firstPtr = lastPtr = 0;
      else
         firstPtr = firstPtr->nextPtr;

      value = tempPtr->data; // data being removed
      delete tempPtr;

      return true; // delete successful

   } // end else

} // end function removeFromFront

// delete node from back of list
template <class NODETYPE>
bool List<NODETYPE>::removeFromBack(NODETYPE &value)
{
   if (isEmpty())
      return false; // delete unsuccessful

   else
   {
      ListNode<NODETYPE> *tempPtr = lastPtr;

      if (firstPtr == lastPtr)
         firstPtr = lastPtr = 0;
      else
      {
         ListNode<NODETYPE> *currentPtr = firstPtr;

         // locate second-to-last element
         while (currentPtr->nextPtr != lastPtr)
            currentPtr = currentPtr->nextPtr;

         lastPtr = currentPtr;
         currentPtr->nextPtr = 0;

      } // end else

      value = tempPtr->data;
      delete tempPtr;

      return true; // delete successful

   } // end else

} // end function removeFromBack

// is List empty?
template <class NODETYPE>
bool List<NODETYPE>::isEmpty() const
{
   return firstPtr == 0;

} // end function isEmpty

// return pointer to newly allocated node
template <class NODETYPE>
ListNode<NODETYPE> *List<NODETYPE>::getNewNode(
    const NODETYPE &value)
{
   return new ListNode<NODETYPE>(value);

} // end function getNewNode

// display contents of List
template <class NODETYPE>
void List<NODETYPE>::print() const
{
   if (isEmpty())
   {
      cout << "The list is empty\n\n";
      return;

   } // end if

   ListNode<NODETYPE> *currentPtr = firstPtr;

   cout << "The list is: ";

   while (currentPtr != 0)
   {
      cout << currentPtr->data << ' ';
      currentPtr = currentPtr->nextPtr;

   } // end while

   cout << "\n\n";

} // end function print

template <class NODETYPE>
void List<NODETYPE>::insertMiddle(const NODETYPE &value, int x)
{
   int count = 0;
   int position = x;
   ListNode<NODETYPE> *newPtr = getNewNode(value);
   ListNode<NODETYPE> *currentPtr = firstPtr;
   ListNode<NODETYPE> *prevPtr = nullptr;

   // Determins Size of the List
   while (currentPtr != nullptr)
   {
      ++count;
      currentPtr = currentPtr->nextPtr;
   }

   // If position is too large, insert at the back
   if (position > count)
   {
      insertAtBack(value);
      return;
   }

   // If position is too small, insert at the front
   if (position <= 0)
   {
      insertAtFront(value);
      return;
   }

   // Resets where ptr is looking
   currentPtr = firstPtr;

   for (int i = 0; i < (position - 1); i++)
   { // This is used to travel to the position mentioned in the function call, and then place the new node into that position
      prevPtr = currentPtr;
      currentPtr = currentPtr->nextPtr;
   }
   if (prevPtr == nullptr)
   {
      newPtr->nextPtr = firstPtr;
      firstPtr = newPtr;
      if (lastPtr == nullptr)
      {
         lastPtr = newPtr;
      }
   }
   else
   {
      newPtr->nextPtr = currentPtr;
      prevPtr->nextPtr = newPtr;
   }
}

template <class NODETYPE>
bool List<NODETYPE>::removeMiddle(const NODETYPE &value, int x)
{
   int count = 0;
   int position = x;
   // Establishing nodes to cycle through the list
   ListNode<NODETYPE> *currentPtr = firstPtr;
   ListNode<NODETYPE> *prevPtr = nullptr;

   // Size of List
   while (currentPtr != nullptr)
   {
      ++count;
      currentPtr = currentPtr->nextPtr;
   }

   // If position is too large or too small, return false without removing anything
   if (position > count || position <= 0)
   {
      return false;
   }

   // Need to compose a function that cycles through the List until the position mentioned in the function call is reached
   currentPtr = firstPtr;
   for (int i = 1; i < position; ++i)
   {
      prevPtr = currentPtr;
      currentPtr = currentPtr->nextPtr;
   }

   // Remove the node at the specified position
   if (prevPtr == nullptr)
   {
      firstPtr = currentPtr->nextPtr;
   }
   else
   {
      prevPtr->nextPtr = currentPtr->nextPtr;
   }

   // If the last node is removed, update lastPtr
   if (currentPtr == lastPtr)
   {
      lastPtr = prevPtr;
   }

   delete currentPtr;
   return true;
}

template <class NODETYPE>
void List<NODETYPE>::operator=(const List<NODETYPE> &s)
{
//Sets current pointer equal to the first pointer of the RHS.
ListNode<NODETYPE> *currentPtr = s.firstPtr;
// Runs through the nodes until it reaches nullptr, and inserting the data into the LHS list.

if (this == &s) {
      return; // No need to perform assignment
   }

while(!isEmpty()){
   NODETYPE value;
   removeFromFront(value);
}

  while (currentPtr != nullptr)
   {
      insertAtBack(currentPtr->data);
      currentPtr = currentPtr->nextPtr;
   }
}


 // l = s;
#endif

/**************************************************************************
 * (C) Copyright 1992-2003 by Deitel & Associates, Inc. and Prentice      *
 * Hall. All Rights Reserved.                                             *
 *                                                                        *
 * DISCLAIMER: The authors and publisher of this book have used their     *
 * best efforts in preparing the book. These efforts include the          *
 * development, research, and testing of the theories and programs        *
 * to determine their effectiveness. The authors and publisher make       *
 * no warranty of any kind, expressed or implied, with regard to these    *
 * programs or to the documentation contained in these books. The authors *
 * and publisher shall not be liable in any event for incidental or       *
 * consequential damages in connection with, or arising out of, the       *
 * furnishing, performance, or use of these programs.                     *
 *************************************************************************/