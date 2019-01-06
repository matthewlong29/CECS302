/*******************************************************************************
Write efficient functions that take only a pointer to the root of a binary tree, T, and compute

(a) the number of nodes in T
(b) the number of leaves in T
(c) the number of full nodes in T

What is the running time of your routines?
*******************************************************************************/

#include <iostream>
#include <chrono>
#include <ratio>
#include <ctime>

using namespace std;
using namespace std::chrono;

#define findNumOfNodes // comment any three of these out to examine runtime independently
#define findNumOfLeaves
#define findNumOfFullNodes

/**
 * Node for a binary tree has a pointer to left right and data
 */
typedef struct Node
{
  int data;
  struct Node *left, *right;
} T; // end Node

/**
 * create new node in binary tree
 */
T *newNode(int data)
{
  T *temp = new T;
  temp->data = data;
  temp->left = temp->right = NULL;
  return temp;
}; // end newNode

/**
 * (a) given pointer to root of binary tree, T, return number of nodes
 * 
 * the time complexity is O(n) because this involves traversing the binary tree linearly
 */
int numOfNodes(T *root)
{
  if (root == NULL) // if tree has no node
    return 0;
  return (numOfNodes(root->left) + 1 + numOfNodes(root->right));
} // end numOfNodes

/**
 * (b) given pointer to root of binary tree, T, return number of leaves
 * 
 * the time complexity is O(n) because this involves traversing the binary tree linearly
 */
int numOfLeaves(T *root)
{
  if (root == NULL) // if tree has no node
    return 0;
  if (root->left == NULL && root->right == NULL) // if trees root node has no left and right node
    return 1;
  return (numOfLeaves(root->left) + numOfLeaves(root->right)); // recursively traverse the tree
} // end numOfLeaves

/**
 * (c) given pointer to root of binary tree, T, return number of full nodes
 * 
 * the time complexity is O(n) because this involves traversing the binary tree linearly
 */
int numOfFullNodes(T *root)
{
  static int count = 0; // static count so that its not reset with recursive calls
  if (root == NULL)     // if tree has no node
    return 0;
  else
  {
    numOfFullNodes(root->left);
    if (root->left != NULL && root->right != NULL) // if examined node has a left AND right node
      count++;
    numOfFullNodes(root->right);
  }
  return count;
} // end numOfFullNodes

/**
 * driver for binary tree examiner functions
 */
int main()
{
  /**
   * create the following binary tree to be used in functions (a), (b), and (c).
   * if a larger tree is created the runtime will be greater than 0 nanoseconds.
   * 
   *                   1
   *                 /   \
   *                2     3
   *               / \   / \
   *              4   5 6   7
   * 
   * Nodes: 1, 2, 3, 4, 5, 6, 7
   * Leaves: 4, 5, 6, 7
   * Full Nodes: 1, 2, 3
   */
  struct Node *root = newNode(1);
  root->left = newNode(2);
  root->right = newNode(3);
  root->left->left = newNode(4);
  root->left->right = newNode(5);
  root->right->left = newNode(6);
  root->right->right = newNode(7);

  high_resolution_clock::time_point t1 = high_resolution_clock::now();

#ifdef findNumOfNodes
  cout << numOfNodes(root) << endl; // 7
#endif

#ifdef findNumOfLeaves
  cout << numOfLeaves(root) << endl; // 4
#endif

#ifdef findNumOfFullNodes
  cout << numOfFullNodes(root) << endl; // 3
#endif

  high_resolution_clock::time_point t2 = high_resolution_clock::now();
  duration<double, nano> time_span = duration_cast<duration<double, nano>>(t2 - t1);
  cout << "It took " << time_span.count() << " nanoseconds to traverse the binary search tree, T."; // likely 0ns because of small tree
  cout << endl;

  return 0;
} // end main