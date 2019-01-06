/*******************************************************************************
Given two sorted lists, L1 and L2, write a procedure to compute L1 intersect L2 using only the basic list operations.

Example: 
L1 = 1, 3, 4, 5, 6
L2 = 1, 5, 6, 7, 9
L1 intersect L2 = 1, 5, 6
*******************************************************************************/
#include <list>
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

/**
 * printsList prints each integer element in list L
 */
void printList(list<int> L)
{
  for (auto l : L)
    cout << l << " ";
} // end printList

/**
 * calculate intersection of two lists L1 and L2
 */
list<int> intersect(list<int> L1, list<int> L2)
{
  list<int> L3;                   // initialize L3 to temporarily hold L1 intersect L2
  list<int>::iterator itr1, itr2; // initialize iterators
  itr1 = L1.begin();              // returns iterator to first element in L1
  itr2 = L2.begin();              // returns iterator to first element in L2

  // iterate over L1 and L2
  while (itr1 != L1.end() && itr2 != L2.end())
  {
    if (*itr1 < *itr2)
      itr1++;
    else if (*itr1 > *itr2)
      itr2++;
    else
    {
      L3.push_back(*itr1); // if itr1 == itr2 push value to L3
      itr1++;
      itr2++;
    }
  }
  return L3;
} // end intersect

/**
 * main
 */
int main()
{
  srand(time(NULL)); // seed rand
  list<int> L1;
  list<int> L2;
  list<int> L3; // this will be the intersection of L1 and L2

  // add 10 random int elements between 0 and 9 to L1 and L2
  for (int i = 0; i < 10; i++)
  {
    L1.push_back(rand() % 10);
    L2.push_back(rand() % 10);
  }

  L1.sort();   // sort elements in L1
  L2.sort();   // sort elements in L2
  L1.unique(); // remove repeated elements in L1
  L2.unique(); // remove repeated elements in L2

  cout << "\nSorted unique values in L1: "; // print elements in L1
  printList(L1);

  cout << "\nSorted unique values in L2: "; // print elements in L2
  printList(L2);

  L3 = intersect(L1, L2); // calculate the values in L1 itersect L2

  cout << "\n\nValues in both L1 and L2: "; // print elements in L1 intersect L2
  printList(L3);

  return 0;
} // end main