/**
 * Write a recursive function that returns the number of 1 in the binary representation of N. 
 * Use the fact that this is equal to the number of 1 in the representation of N/2, plus 1, if N is odd.
 */

#include <iostream>

using namespace std;

/**
 * number of onces of binary representation of decimal value by recursion
 */
int numOnes(int N)
{
  if (N == 0)
    return 0;
  else if (N == 1)
    return 1;
  else if (N % 2 != 0)
    return 1 + numOnes(N / 2);
  else
    return numOnes(N / 2);
} // end numOnes

int main(void)
{
  cout << numOnes(-78);
  return 0;
} // end main