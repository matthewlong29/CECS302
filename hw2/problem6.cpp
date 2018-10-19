/*******************************************************************************
For each of the following six program fragments (based on Problem 2.7): Give an analysis of the running time (Big-Oh will do), implement the code in the language of your choice, and give the running time for several values of N, compare your analysis with the actual running times.
*******************************************************************************/
#include <iostream>
#include <chrono>
#include <ctime>

using namespace std;
using namespace std::chrono;

// #define a
// #define b
// #define c
// #define d
// #define e
#define f
// #define g

#ifdef a
void A(int n)
{
  int sum = 0;
  for (int i = 0; i < n; ++i)
    ++sum;
}
#endif

#ifdef b
void B(int n)
{
  int sum = 0;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      ++sum;
}
#endif

#ifdef c
int C(int n)
{
  int sum = 0;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n * n; ++j)
      ++sum;
}
#endif

#ifdef d
int D(int n)
{
  int sum = 0;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < i; ++j)
      ++sum;
}
#endif

#ifdef e
int E(int n)
{
  int sum = 0;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < i * i; ++j)
      for (int k = 0; k < j; ++k)
        ++sum;
}
#endif

#ifdef f
int F(int n)
{
  int sum = 0;
  for (int i = 1; i < n; ++i)
    for (int j = 1; j < i * i; ++j)
      if (j % i == 0)
        for (int k = 0; k < j; ++k)
          ++sum;
}
#endif

#ifdef g
int G(int n)
{
  int sum = 0;
  for (int j = 1; j < n; j *= 2)
    ++sum;
}
#endif

/**
 * 
 */
int main()
{
  auto t1 = std::chrono::high_resolution_clock::now();
#ifdef a
  A(2048);
#endif
#ifdef b
  B(2048);
#endif
#ifdef c
  C(2048);
#endif
#ifdef d
  D(2048);
#endif
#ifdef e
  E(256);
#endif
#ifdef f
  F(1024);
#endif
#ifdef g
  G(1);
#endif
  auto t2 = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> fp_ms = t2 - t1;
  auto int_ms = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
  std::cout << "Runtime: " << fp_ms.count() << " ms." << std::endl;
  return 0;
} // end main