/*******************************************************************************
Efficiently implement a stack class using a singly linked list, with no header or tail nodes.
*******************************************************************************/
#include <iostream>

using namespace std;

class LinkedList
{
private:
  int val;          // holds value in the list
  LinkedList *next; // stores address to next node

public:
  void displayStack(LinkedList *);
  LinkedList *push(LinkedList *, int);
  LinkedList *pop(LinkedList *);
  void top(LinkedList *);
  int size(LinkedList *);
};

/**
 * display the stack
 */
void LinkedList::displayStack(LinkedList *list)
{
  if (list != NULL)
  {
    // loop over and print all nodes in list
    while (list->next != NULL)
    {
      cout << list->val << ((list->next) ? ", " : "");
      list = list->next;
    }
    cout << list->val << endl;
  }
  else
    cout << "Stack is empty." << endl;
} // end displayStack

/**
 * push node to list at top
 */
LinkedList *LinkedList::push(LinkedList *list, int node)
{
  LinkedList *tempTop, *tempList;
  tempList = list;
  tempTop = new LinkedList;
  tempTop->next = NULL;
  tempTop->val = node;
  if (list == NULL) // if list is empty add node
    list = tempTop;
  else
  {
    while (list->next != NULL) // loop to end of list if not empty
      list = list->next;
    list->next = tempTop;
    list = tempList;
  }
  return list;
} // end push

/**
 * pop node from list
 */
LinkedList *LinkedList::pop(LinkedList *list)
{
  LinkedList *tempTop;
  if (list != NULL)
  {
    tempTop = list;
    if (list->next == NULL) // if only one node in list
    {
      cout << "Popped [" << list->val << "]"
           << " from stack." << endl;
      return NULL;
    }
    while (list->next->next != NULL) // loop to last node in list
      list = list->next;
    cout << "Popped [" << list->next->val << "]"
         << " from stack." << endl;
    list->next = list->next->next;
    list = tempTop;
    return list;
  }
  else
  {
    cout << "Please try again." << endl;
    return list;
  }
} // end pop

/**
 * display top element on list stack
 */
void LinkedList::top(LinkedList *list)
{
  LinkedList *tempTop;
  if (list != NULL)
  {
    tempTop = list;
    if (list->next == NULL) // if only one node in list
    {
      cout << "Top node on the stack is [" << list->val << "]." << endl;
      return;
    }
    while (list->next->next != NULL) // loop to last node in list
      list = list->next;
    cout << "Top node on the stack is [" << list->next->val << "]." << endl;
    return;
  }
  else
  {
    cout << "Please try again." << endl;
    return;
  }
} // end top

/**
 * return and print the size of the list
 */
int LinkedList::size(LinkedList *list)
{
  LinkedList *tempTop;
  int count = 0; // hold count, or number of nodes in list
  if (list != NULL)
  {
    tempTop = list;
    if (list->next == NULL) // if only one node in list
    {
      cout << "There is [" << ++count << "] element on the stack." << endl;
      return count; // next node is null hence only one node in list
    }
    while (list->next != NULL) // loop to last node in list
    {
      list = list->next;
      count++;
    }
    cout << "There are [" << ++count << "] elements on the stack." << endl;
    return count;
  }
  else
  {
    cout << "There are [" << count << "] elements on the stack." << endl;
    return count;
  }
} // end size

/**
 * main acts as a "driver function" for LinkedList
 */
int main(void)
{
  LinkedList *list, cur; // create LinkedLists
  int node, selection;
  cout << "Select stack operation [1] push, [2] pop, [3] top, [4] size, and [5] exit: ";
  cin >> selection;
  list = NULL; // empty stack
  while (1)
  {
    switch (selection)
    {
    case 1: // get node from user to push to stack
      cout << "Enter node: ";
      cin >> node;
      list = cur.push(list, node);
      cout << "Stack: ";
      cur.displayStack(list);
      break;
    case 2: // pop top value from stack
      list = cur.pop(list);
      cout << "Stack: ";
      cur.displayStack(list);
      break;
    case 3:
      cur.top(list);
      cout << "Stack: ";
      cur.displayStack(list);
      break;
    case 4:
      cur.size(list);
      cout << "Stack: ";
      cur.displayStack(list);
      break;
    case 5: // exit
      cout << "Stack: ";
      cur.displayStack(list);
      return 0; // early return from main when selecting 3
    default:
      cout << "Invalid selection." << endl;
      break;
    }
    cout << "Select stack operation [1] push, [2] pop, [3] top, [4] size, and [5] exit: ";
    cin >> selection;
  }
  return 0;
} // end main