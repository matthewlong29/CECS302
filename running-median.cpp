/*******************************************************************************
(5 points) The median of a set of integers is the midpoint value of the data set for which an equal number of integers are less than and greater than the value. To find the median, one way is to sort your set of integers in non-decreasing order, then:

1. If your set contains an odd number of elements, the median is the middle element of the sorted sample.
2. If your set contains an even number of elements, the median is the average of the two middle elements of the sorted sample.

Given an input stream of integers, you must perform the following task for each integer:

1. Add the integer to a running list of integers.
2. Find the median of the updated list.

For example, assume a stream of 1, 4, 6, 3, 2, 8
The median would be 1, 2.5, 4, 3.5, 3, 3.5

(Hint: use heaps)
*******************************************************************************/

#include <iostream>
#include <queue>

using namespace std;

// #define debugDriver
// #define debugFindRunningMedian

/**
 * findRunningMedian
 */
void findRunningMedian(vector<double> streamOfElements, int numberOfElements)
{
  priority_queue<double> smallerElements;                                  // max heap to store the smaller half elements
  priority_queue<double, vector<double>, greater<double>> greaterElements; // min heap to store the greater half elements

  double median = streamOfElements[0];
#ifdef debugFindRunningMedian // define copy of median used for debugging
  double currentMedian;       // used for debugging
#endif
#ifdef debugFindRunningMedian // print reason why median was found
  cout << "The first median \"" << median << "\" is the first element because only one currently exists;" << endl;
#endif
  smallerElements.push(median);

  cout << "Running median: " << median << endl; // print current median.. first value

  for (int i = 1; i < numberOfElements; i++) // loop over all other elements
  {
    double x = streamOfElements[i];

    if (smallerElements.size() > greaterElements.size()) // if left side of heap has more elements
    {
      if (x < median)
      {
        greaterElements.push(smallerElements.top());
        smallerElements.pop();
        smallerElements.push(x);
      }
      else
        greaterElements.push(x);

      median = (smallerElements.top() + greaterElements.top()) / 2.0;
#ifdef debugFindRunningMedian // print reason why median was found
      cout << "The left side of heap is bigger so median is \"" << median << "\";" << endl;
#endif
    }

    else if (smallerElements.size() == greaterElements.size()) // if both heaps are balanced
    {
#ifdef debugFindRunningMedian
      currentMedian = median;
#endif
      if (x < median)
      {
        smallerElements.push(x);
        median = (double)smallerElements.top();
#ifdef debugFindRunningMedian // print reason why median was found
        cout << "The heaps are balanced and the current value in stream of elements \"" << x << "\" is less than previous median \"" << currentMedian << "\" so median is now \"" << median << "\";" << endl;
#endif
      }
      else
      {
        greaterElements.push(x);
        median = (double)greaterElements.top();
#ifdef debugFindRunningMedian // print reason why median was found
        cout << "The heaps are balanced and the current value in stream of elements \"" << x << "\" is greater than or equal to the previous median \"" << currentMedian << "\" so median is now \"" << median << "\";" << endl;
#endif
      }
    }

    else // else right side of heap has more elements
    {
      if (x > median)
      {
        smallerElements.push(greaterElements.top());
        greaterElements.pop();
        greaterElements.push(x);
      }
      else
        smallerElements.push(x);

      median = (smallerElements.top() + greaterElements.top()) / 2.0;
#ifdef debugFindRunningMedian
      cout << "The right side of heap is bigger so median is \"" << median << "\";" << endl;
#endif
    }

    cout << "Running median: " << median << endl;
  }
} // print medians

/**
 * driver function
 */
int main()
{
  cout << "Running Median Calculator;----------------------------------" << endl;
  vector<double> streamOfElements = {1, 4, 6, 3, 2, 8}; // stream of integers
#ifdef debugDriver                                      // print stream of elements
  cout << "Stream of Elements;-----------------------------------------\n";
  for (int i = 0; i < streamOfElements.size(); i++)
    cout << streamOfElements[i] << (i == streamOfElements.size() - 1 ? "" : ", ");
  cout << endl;
#endif
#ifdef debugDriver // print size of stream of elements
  cout << "Number of Elements in Stream;-------------------------------\n"
       << streamOfElements.size() << endl;
#endif
  findRunningMedian(streamOfElements, streamOfElements.size());

  return 0;
} // end main