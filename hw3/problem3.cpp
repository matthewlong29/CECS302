/*******************************************************************************
Suppose we want to add the operation findKth to our repertoire. The operation findKth(k) returns the kth smallest value in the tree. Assume all items are distinct. Explain how to modify the binary search tree to support this operation in O(logN) average time, without sacrificing the time bounds of any other operation.
*******************************************************************************/

#include <iostream>
#include <vector>

using namespace std;

/**
 * Node for a binary tree has a pointer to left right and data as well as 
 * size that is used to indicate the weight of a node 
 */
typedef struct Node
{
  int data, size;
  Node *left, *right;
} Node; // endif

/** 
 * insertion by recursion  
 */
Node *insert(Node *root, Node *node)
{
  Node *mov = root; // pointer used for iteration
  Node *currentParent = root;

  while (mov) // traverse to desired node
  {
    currentParent = mov;

    if (node->data < mov->data)
    {
      mov->size++; // we are branching to left subtree increment node count
      mov = mov->left;
    }
    else
      mov = mov->right;
  }

  if (!root) // if tree is empty it is a node
    root = node;
  else if (node->data < currentParent->data)
    currentParent->left = node;
  else
    currentParent->right = node;

  return root;
} // endif

/**
 * elements are in an array. the function builds binary tree 
 */
Node *BST(Node *root, const vector<int> &keys, int const size)
{
  Node *tempNode = NULL;

  for (int i = 0; i < size; i++)
  {
    tempNode = new Node;
    tempNode->data = keys[i]; // initialize
    tempNode->size = 0;
    tempNode->left = NULL;
    tempNode->right = NULL;
    root = insert(root, tempNode); // insert into BST
  }

  return root;
} // end BST

/**
 * findKth
 */
int findKth(Node *root, int k)
{
  int result = -1; // indicates out of bounds

  if (root)
  {
    Node *mov = root;

    while (mov)
    {
      if ((mov->size + 1) == k)
      {
        result = mov->data;
        break;
      }
      else if (k > mov->size)
      {
        k = k - (mov->size + 1);
        mov = mov->right;
      }
      else
        mov = mov->left;
    }
  }

  return result;
}
// end findKth

/**
 * driver program to test above functions 
 */
int main(void)
{
  vector<int> testTree = {8, 6, 15, 13, 2, 1, 19};
  Node *root = NULL;
  int k;
  root = BST(root, testTree, testTree.size()); // creating the testTree given in the above "tree"
  cout << "Enter the value for k: ";
  cin >> k;
  cout << "\"kth\" smallest, when value of k equals " << k << " is " << findKth(root, k) << "!" << endl; // print the sorted array

  return 0;
} // end main