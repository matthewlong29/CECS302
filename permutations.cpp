/**
 * Write the routines with the following declarations:
 * void permute(const string & str);
 * void permute(const string & str, int low, int high);
 * The first routine is a driver that calls the second and prints all the permutations of the characters in string str. 
 * If str is "abc", then the strings that are output are abc, acb, bac, bca, cab, and cba. 
 * How many permutations for a string of length l?
 */

#include <string>
#include <iostream>

using namespace std;

/**
 * function signatures
 */
void permute(const string &str);
void permute(const string &str, int low, int high);

/**
 * permutation driver
 */
void permute(const string &str)
{
  permute(str, 0, str.size() - 1);
} // end permute

/**
 * permutation calculations and output
 */
void permute(const string &str, int low, int high)
{
  char temp; // hold letter temporarily
  string s = str;
  if (low == high)
    cout << str << endl; // check for trivial case
  else
  {
    for (int i = low; i <= high; i++)
    {
      temp = s[i];
      s[i] = s[low];
      s[low] = temp;
      permute(s, low + 1, high);
      temp = s[i];
      s[i] = s[low];
      s[low] = temp;
    }
  }
} // end permute

int main(void)
{
  permute("abc");
  return 0;
} // end main