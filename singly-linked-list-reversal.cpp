/*******************************************************************************
Write an algorithm for printing a singly linked list in reverse, using only constant extra space. This instruction implies that you cannot use recursion, but you may assume that your algorithm is a list member function. Can such an algorithm be written if the routine is a constant member function.
*******************************************************************************/

#include <list>

/**
 * 
 */
struct Node
{
  int data;
  struct Node *next;
}; // end Node struct

/**
 * 
 */
void printReversedList(struct Node *head)
{
  Node currentPosition, nextPosition, previousPosition;
  previousPosition = NULL;             // assign null
  currentPosition = head.next;         // the current pointer points the the beginning of the list
  nextPosition = currentPosition.next; // the next pointer points to the second element

  // while all elements in the list have not been considered
  while (nextPosition != NULL)
  {
    currentPosition.next = previousPosition;
    previousPosition = currentPosition;
    currentPosition = nextPosition;
    nextPosition = nextPosition.next;
  }

  currentPosition.next = previousPosition; // the first pointer points to the list
  head.next = currentPosition;
} // end printReversedList

/**
 * 
 */
int main()
{
  return 0;
} // end