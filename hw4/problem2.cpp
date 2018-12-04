/*******************************************************************************
 (5 points) Write a program to implement the following strategy for multiplying two sparse polynomials P1, P2 of size M and N, respectively. Each polynomial is represented as a list of objects consisting of a coefficient and an exponent. We multiply each term in P1 by a term in P2 for a total of MN operations. 
 
 One method is to sort these terms and combine like terms, but this requires sorting MN records, which could be expensive, especially in small-memory environments. 
 
 Alternatively, we could merge terms as they are computed and then sort the result.
 
 1. Write a program to implement the alternative strategy.
 2. If the output polynomial has about O(M+N) terms, what is the running time of both methods?
 
 (Problem 5.13 from the textbook.)
*******************************************************************************/

#include <iostream>
#include <vector>
#include <stdlib.h> // for rand and srand
#include <time.h>   // to seed rand
#include <chrono>   // for runtime
#include <ratio>

/**
 * change this for larger polynomials
 * note that each polynomial will be MAX_SIZE size initially,
 * but may be smaller when combining like terms
 */
#define MAX_SIZE 40

// #define methodOne // sort => combine => multiply each term in P1 by term in P2 => sort => combine
#define methodTwo // sort => multiply and combine => sort

// #define debugCombineLikeTerms
// #define debugSortPolynomial
// #define debugMultPolynomial
// #define debugDisplayPolynomial
// #define debugMultAndCombineLikeTerms>
// #define debugDriver

#define runTime // use chrono to output runtime of the two methods

using namespace std;
using namespace std::chrono;

/**
 * Term such as (8x^2)
 */
typedef struct Term
{
  int coefficient, exponent;
} term;
// end Term

/**
 * create a new term that belongs to a polynomial
 */
term *newTerm(int coefficient, int exponent)
{
  term *temp = new Term;
  temp->coefficient = coefficient;
  temp->exponent = exponent;
  return temp;
} // end newTerm

/**
 * create two unsimplified random polynomials
 */
vector<term *> newPolynomial()
{
  vector<term *> P;
  int randomCoefficient, randomExponent;

  for (int i = 0; i < MAX_SIZE; i++)
  {
    randomCoefficient = rand() % MAX_SIZE - MAX_SIZE / 2;
    randomExponent = rand() % MAX_SIZE - MAX_SIZE / 2;
    if (randomCoefficient == 0)
      continue; // don't push back because term equals 0
    P.push_back(newTerm(randomCoefficient, randomExponent));
  }

  return P; // return random polynomial of max size (also max magnitude coefficient and exponent)
} // end newPolynomial

/**
 * nicely print the polynomial
 * 
 * note that the value of 1 for the coefficient and exponent are not shown
 * also note that if the exponenet is 0 only the coefficient is shown
 * the term was not initially added if it was found that the coefficient is 0
 * however, it is possible that the coefficient becomes 0 when combining terms
 * in this case, it will not be printed
 */
void displayPolynomial(vector<term *> P)
{
  if (P.size() == 0)
    cout << "Polynomial not found.";

#ifdef debugDisplayPolynomial
  cout << "-----------------------------------------------------------\nOriginal Polynomial;---------------------------------------" << endl;
  for (int i = 0; i < P.size(); i++)
    cout << "Term " << i << "; Coefficient: " << P[i]->coefficient << "; Exponent: " << P[i]->exponent << "; (" << P[i]->coefficient << "x^" << P[i]->exponent << ");" << endl;
  cout << "-----------------------------------------------------------" << endl;
#endif

  for (int i = 0; i < P.size(); i++)
  {
    if (P[i]->coefficient == 0)
      continue;
    else if (P[i]->exponent == 0)
      cout << "(" << P[i]->coefficient;
    else if (P[i]->exponent == 1 && P[i]->coefficient == 1)
      cout << "(x";
    else if (P[i]->exponent == 1 && P[i]->coefficient == -1)
      cout << "(-x";
    else if (P[i]->exponent == 1)
      cout << "(" << P[i]->coefficient << "x";
    else if (P[i]->coefficient == 1)
      cout << "(x^" << P[i]->exponent;
    else if (P[i]->coefficient == -1)
      cout << "(-x^" << P[i]->exponent;
    else
      cout << "(" << P[i]->coefficient << "x^" << P[i]->exponent;

#ifdef debugDisplayPolynomial // print check that P[i]->coefficient == 0 continue statement worked as expected
    if (P[i]->coefficient == 0)
      cout << "Reached this line?;";
#endif
    cout << (i != P.size() - 1 ? ") + " : ")");
  }
  cout << endl;
} // end displayPolynomial

/**
 * combineLikeTerms "utility" function used to simplify the randomly generated polynomials
 */
vector<term *> combineLikeTerms(vector<term *> P)
{
  bool isSameExponent = false; // flag to indicate if a duplicate exponent has been found
#ifdef debugCombineLikeTerms   // print size of polynomial p
  cout << "Size of Polynomial: " << P.size() << ";" << endl;
#endif
#ifdef debugCombineLikeTerms // print individual terms separated by coefficient and exponent
  cout << "-----------------------------------------------------------\nOriginal Polynomial;---------------------------------------" << endl;
  for (int i = 0; i < P.size(); i++)
  {
    cout << "Term " << i << "; Coefficient: " << P[i]->coefficient << "; Exponent: " << P[i]->exponent << "; (" << P[i]->coefficient << "x^" << P[i]->exponent << ");" << endl;
  }
  cout << "-----------------------------------------------------------" << endl;
#endif
  int j;
  // simplify polynomials by adding like exponenets (not necessarily sorted yet)
  for (int i = 0; i < P.size(); i++) // gather like exponents and add their coefficients
  {
    isSameExponent = false; // reset isSameExponent to false
    j = i + 1;
    while (j < P.size() && !isSameExponent)
    {
#ifdef debugCombineLikeTerms // print index's j and i used in for loop
      cout << "i: " << i << "; j: " << j << ";" << endl;
#endif
      if (P[i]->exponent == P[j]->exponent)
      {
#ifdef debugCombineLikeTerms // print statement indicating exponents that are equal
        cout << "Exponent for \"Term " << i << "\" (" << P[i]->coefficient << "x^" << P[i]->exponent << ") and \"Term " << j << "\" (" << P[j]->coefficient << "x^" << P[j]->exponent << ") are equal;" << endl;
#endif
        isSameExponent = true;
        P[i]->coefficient += P[j]->coefficient;
        P.erase(P.begin() + j);
#ifdef debugCombineLikeTerms // print individual terms separated by coefficient and exponent
        cout << "-----------------------------------------------------------\nNew Polynomial;--------------------------------------------" << endl;
        for (int i = 0; i < P.size(); i++)
        {
          cout << "Term " << i << "; Coefficient: " << P[i]->coefficient << "; Exponent: " << P[i]->exponent << "; (" << P[i]->coefficient << "x^" << P[i]->exponent << ");" << endl;
        }
        cout << "-----------------------------------------------------------" << endl;
#endif
      }

      if (!isSameExponent)
        j++;
      else
      {
        j = i + 1;
        i--;
      }
    }
  }
#ifdef debugCombineLikeTerms // print simplified polynomial
  cout << "-----------------------------------------------------------\nSimplified Polynomial;-------------------------------------" << endl;
  for (int i = 0; i < P.size(); i++)
  {
    cout << "Term " << i << "; Coefficient: " << P[i]->coefficient << "; Exponent: " << P[i]->exponent << "; (" << P[i]->coefficient << "x^" << P[i]->exponent << ");" << endl;
  }
  cout << "-----------------------------------------------------------" << endl;
#endif

  return P; // return simplified polynomial
} // end combineLikeTerms

/**
 * sort polynomial 
 */
vector<term *> sortPolynomial(vector<term *> P)
{
#ifdef debugSortPolynomial // print unsorted polynomial
  cout << "-----------------------------------------------------------\nUnsorted Polynomial;---------------------------------------" << endl;
  for (int i = 0; i < P.size(); i++)
  {
    cout << "Term " << i << "; Coefficient: " << P[i]->coefficient << "; Exponent: " << P[i]->exponent << "; (" << P[i]->coefficient << "x^" << P[i]->exponent << ");" << endl;
  }
  cout << "-----------------------------------------------------------" << endl;
#endif
  for (int i = 0; i < P.size(); i++)
  {
    for (int j = i; j < P.size(); j++)
    {
      if (P[j]->exponent > P[i]->exponent)
      {
#ifdef debugSortPolynomial // print statement indicating which terms are being swapped
        cout << "Swapping (" << P[i]->coefficient << "x^" << P[i]->exponent << ") and (" << P[j]->coefficient << "x^" << P[j]->exponent << ");" << endl;
#endif
        term *temp = new Term;
        temp->exponent = P[j]->exponent;
        temp->coefficient = P[j]->coefficient;
        P[j]->exponent = P[i]->exponent;
        P[j]->coefficient = P[i]->coefficient;
        P[i]->exponent = temp->exponent;
        P[i]->coefficient = temp->coefficient;
#ifdef debugSortPolynomial // print sorting progress
        cout << "-----------------------------------------------------------\nSorted (Almost..) Polynomial;------------------------------" << endl;
        for (int i = 0; i < P.size(); i++)
        {
          cout << "Term " << i << "; Coefficient: " << P[i]->coefficient << "; Exponent: " << P[i]->exponent << "; (" << P[i]->coefficient << "x^" << P[i]->exponent << ");" << endl;
        }
        cout << "-----------------------------------------------------------" << endl;
#endif
      }
    }
  }

#ifdef debugSortPolynomial // print sorted polynomial
  cout << "-----------------------------------------------------------\nSorted Polynomial;-----------------------------------------" << endl;
  for (int i = 0; i < P.size(); i++)
  {
    cout << "Term " << i << "; Coefficient: " << P[i]->coefficient << "; Exponent: " << P[i]->exponent << "; (" << P[i]->coefficient << "x^" << P[i]->exponent << ");" << endl;
  }
  cout << "-----------------------------------------------------------" << endl;
#endif

  return P;
} // end sortPolynomial

/**
 * multPolynomial
 */
vector<term *> multPolynomial(vector<term *> P1, vector<term *> P2)
{
#ifdef debugMultPolynomial // print sorted and simplified  P1 and P2
  cout << "-----------------------------------------------------------\nPolynomial One;--------------------------------------------" << endl;
  for (int i = 0; i < P1.size(); i++)
  {
    cout << "Term " << i << "; Coefficient: " << P1[i]->coefficient << "; Exponent: " << P1[i]->exponent << "; (" << P1[i]->coefficient << "x^" << P1[i]->exponent << ");" << endl;
  }
  cout << "-----------------------------------------------------------\nPolynomial Two;--------------------------------------------" << endl;
  for (int i = 0; i < P2.size(); i++)
  {
    cout << "Term " << i << "; Coefficient: " << P2[i]->coefficient << "; Exponent: " << P2[i]->exponent << "; (" << P2[i]->coefficient << "x^" << P2[i]->exponent << ");" << endl;
  }
  cout << "-----------------------------------------------------------" << endl;
#endif
  vector<term *> P;

  for (int i = 0; i < P1.size(); i++)
  {
    for (int j = 0; j < P2.size(); j++)
    {
#ifdef debugMultPolynomial // print which terms are being multiplied
      cout << "-----------------------------------------------------------\nMultiplying terms (" << P1[i]->coefficient << "x^" << P1[i]->exponent << ") and (" << P2[j]->coefficient << "x^" << P2[j]->exponent << ");" << endl;
#endif
      term *temp = new Term;
      temp->coefficient = P1[i]->coefficient * P2[j]->coefficient; // multiply coefficients
      temp->exponent = P1[i]->exponent + P2[j]->exponent;          // add exponents
      if (temp->coefficient == 0)
      {
#ifdef debugMultPolynomial // print statement indicating coefficient is 0
        cout << "temp->coefficient == 0; Continueing to next term;" << endl;
#endif
        continue; // continue to next term because this term is 0
      }
      P.push_back(temp);
    }
  }

#ifdef debugMultPolynomial // print product of P1 and P2
  cout << "-----------------------------------------------------------\nPolynomial Product (P1) * (P2);----------------------------" << endl;
  for (int i = 0; i < P.size(); i++)
  {
    cout << "Term " << i << "; Coefficient: " << P[i]->coefficient << "; Exponent: " << P[i]->exponent << "; (" << P[i]->coefficient << "x^" << P[i]->exponent << ");" << endl;
  }
  cout << "-----------------------------------------------------------" << endl;
#endif

  return P;
} // end multPolynomial

/**
 * multAndCombineLikeTerms - multiplies terms one at a time and while multiplying checks if that 
 * exponent is already in the list of exponents (i.e. in the vector), if it is add the coefficients 
 * then continue to next term else push back that term
 */
vector<term *> multAndCombineLIkeTerms(vector<term *> P1, vector<term *> P2)
{
#ifdef debugMultAndCombineLikeTerms // print P1 and P2 separated by term
  cout << "-----------------------------------------------------------\nSorted Polynomial One;-------------------------------------" << endl;
  for (int i = 0; i < P1.size(); i++)
  {
    cout << "Term " << i << "; Coefficient: " << P1[i]->coefficient << "; Exponent: " << P1[i]->exponent << "; (" << P1[i]->coefficient << "x^" << P1[i]->exponent << ");" << endl;
  }
  cout << "-----------------------------------------------------------\nSorted Polynomial Two;-------------------------------------" << endl;
  for (int i = 0; i < P2.size(); i++)
  {
    cout << "Term " << i << "; Coefficient: " << P2[i]->coefficient << "; Exponent: " << P2[i]->exponent << "; (" << P2[i]->coefficient << "x^" << P2[i]->exponent << ");" << endl;
  }
  cout << "-----------------------------------------------------------" << endl;
#endif
  vector<term *> P;

  for (int i = 0; i < P1.size(); i++)
  {
    for (int j = 0; j < P2.size(); j++)
    {
      term *temp = new Term;
      temp->coefficient = P1[i]->coefficient * P2[j]->coefficient; // multiply coefficients
      temp->exponent = P1[i]->exponent + P2[j]->exponent;          // add exponents
#ifdef debugMultAndCombineLikeTerms                                // print which terms are being multiplied
      cout << "-----------------------------------------------------------\nCalculating Product: (" << P1[i]->coefficient << "x^" << P1[i]->exponent << ") * (" << P2[j]->coefficient << "x^" << P2[j]->exponent << ") = (" << temp->coefficient << "x^" << temp->exponent << ");" << endl;
#endif

      if (temp->coefficient == 0)
      {
#ifdef debugMultAndCombineLikeTerms // print statement indicating coefficient is 0
        cout << "temp->coefficient == 0; Continueing to next term;" << endl;
#endif
        continue; // continue to next term because this term is 0
      }

      if (P.size() == 0)
      {
#ifdef debugMultAndCombineLikeTerms // print term that is being pushed_back
        cout << "P.size() == 0; Pushing back term (" << temp->coefficient << "x^" << temp->exponent << ") to P;" << endl;
#endif
        P.push_back(temp);
        continue; // pushed back; now calculate next term
      }
#ifdef debugMultAndCombineLikeTerms // print sizeOf P
      cout << "P is size " << P.size() << ";" << endl;
#endif
#ifdef debugMultAndCombineLikeTerms // print P separated by term which is P1 * P2
      cout
          << "-----------------------------------------------------------\nCurrent (P1) * P(2) Polynomial;----------------------------" << endl;
      for (int i = 0; i < P.size(); i++)
      {
        cout << "Term " << i << "; Coefficient: " << P[i]->coefficient << "; Exponent: " << P[i]->exponent << "; (" << P[i]->coefficient << "x^" << P[i]->exponent << ");" << endl;
      }
      cout << "-----------------------------------------------------------" << endl;
#endif

      // if the exponent is already in the product of P1 and P2 then combine them
      for (int k = 0; k < P.size(); k++)
      {
#ifdef debugMultAndCombineLikeTerms // print check for if exponent product is already in P
        cout << "Do terms (" << temp->coefficient << "x^" << temp->exponent << ") and (" << P[k]->coefficient << "x^" << P[k]->exponent << ") have the same exponent; " << ((temp->exponent == P[k]->exponent) ? "Yes;" : "No;") << endl;
#endif
        if (temp->exponent == P[k]->exponent)
        {
          P[k]->coefficient += temp->coefficient;
#ifdef debugMultAndCombineLikeTerms // print term that is being combined
          cout << "Term " << k << " now equal to (" << P[k]->coefficient << "x^" << P[k]->exponent << ");" << endl;
#endif
          break; // exit loop early if same exponent is found
        }

        if (k == P.size() - 1)
        {
#ifdef debugMultAndCombineLikeTerms // print term being pushed_back
          cout << "End of P; Pushing back term (" << temp->coefficient << "x^" << temp->exponent << ") to P;" << endl;
#endif
          P.push_back(temp);
          break;
        }
      }
    }
  }

  return P; // return simplified polynomial product (P1) * (P2)
} // end multAndCombineLikeTerms

/**
 * driver
 * 
 * using vectors for easy indexing, []
 */
int main()
{
  srand(time(NULL));

  vector<term *> P1, P2, PProduct; // PProduct = (P1) * (P2)

  P1 = newPolynomial(); // create random polynomial P1
  P2 = newPolynomial(); // create random polynomial P2

#ifdef runTime // start runtime calc
  high_resolution_clock::time_point t1 = high_resolution_clock::now();
#endif

  // print unsimplified polynomials P1 and P2
  cout << "Unsimplified Polynomial One (P1);--------------------------" << endl;
  displayPolynomial(P1);
  cout << "Unsimplified Polynomial Two (P2);--------------------------" << endl;
  displayPolynomial(P2);

  P1 = sortPolynomial(P1);
  P2 = sortPolynomial(P2);

#ifdef debugDriver // print sorted polynomials P1 and P2
  cout << "Sorted Polynomial One (P1);--------------------------------" << endl;
  displayPolynomial(P1);
  cout << "Sorted Polynomial Two (P2);--------------------------------" << endl;
  displayPolynomial(P2);
#endif

#ifdef methodOne // start method one driver
  cout << "Method One;------------------------------------------------" << endl;
  P1 = combineLikeTerms(P1);
  P2 = combineLikeTerms(P2);

#ifdef debugDriver // print simplified polynomials P1 and P2
  cout << "Simplified Polynomial One (P1);----------------------------" << endl;
  displayPolynomial(P1);
  cout << "Simplified Polynomial Two (P2);----------------------------" << endl;
  displayPolynomial(P2);
#endif

  PProduct = multPolynomial(P1, P2);

#ifdef debugDriver // print unsorted and unsimplified polynomial product (P1) * (P2)
  cout << "Polynomial Product (P1) * (P2);----------------------------" << endl;
  displayPolynomial(PProduct);
#endif

  PProduct = combineLikeTerms(PProduct);
  PProduct = sortPolynomial(PProduct);

#endif // end method one driver

#ifdef methodTwo // start method two driver
  cout << "Method Two;------------------------------------------------" << endl;
  PProduct = multAndCombineLIkeTerms(P1, P2);
#endif // end method two driver

#ifdef debugDriver // print sorted and simplified polynomial product (P1) * (P2) if found
  cout << "Simplified Polynomial Product (P1) * (P2);-----------------" << endl;
  displayPolynomial(PProduct);
#endif

  PProduct = sortPolynomial(PProduct);

  cout << "Simplified and Sorted Polynomial Product (P1) * (P2);------" << endl;
  displayPolynomial(PProduct);

#ifdef runTime // end runtime calc
  high_resolution_clock::time_point t2 = high_resolution_clock::now();
  duration<double, nano> time_span = duration_cast<duration<double, nano>>(t2 - t1);
  cout << "-----------------------------------------------------------\nIt took " << time_span.count() << " nanoseconds to multiply two polynomials\nresulting in a sorted and simplified product; when\nstarting with " << MAX_SIZE << " terms;\n-----------------------------------------------------------" << endl;
#endif

  return 0;
} // end main