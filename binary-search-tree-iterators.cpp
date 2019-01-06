/*******************************************************************************
Write an implementation of iterators (const_iterator, and iterator) in the set class implemented as a binary search tree. Add to each Node a link to the parent Node.
*******************************************************************************/

#include <vector>
#include <iostream>

using namespace std;

template <class T>
class nodeIterator;
template <class T>
class Set;

template <class T>
struct Node
{
  T value;
  Node *left, *right, *nodeFriend;
  Node(const T &data) : value{data}, left{nullptr}, right{nullptr}, nodeFriend{nullptr} {}
};

template <class T>
class Set
{
public:
  Set() : _size{0}, root{nullptr} {}

  using iterator = nodeIterator<T>;

  Set(const Set &set) : _size{0}, root{nullptr}
  {
    for (iterator itr = set.begin(); itr != set.end(); itr++)
      insert(*itr);
  }

  Set &operator=(const Set &set)
  {
    if (&set == this)
      return *this;
    if (root)
    {
      root = nullptr;
      _size = 0;
    }
    for (iterator itr = set.begin(); itr != set.end(); itr++)
      insert(*itr);
    return *this;
  }

  size_t size() const { return _size; }
  size_t _size;
  Node<T> *root;
  mutable Node<T> *startIterator;

  T &insert(const T &t) { return insert(t, root, _size); }

  iterator begin() const
  {
    buildIterator(root);
    return iterator(startIterator);
  } // end begin

  iterator end() const { return iterator(0); } // end end

private:
  void buildIterator(const Node<T> *root) const
  {
    size_t i;
    vector<Node<T> *> iterators;
    buildIterator(iterators, root);

    if (_size == 0)
    {
      startIterator = nullptr;
      return;
    }

    startIterator = iterators[0];
    for (i = 0; i < iterators.size() - 1; i++)
      iterators[i]->nodeFriend = iterators[i + 1];
    iterators[i]->nodeFriend = nullptr;
  } // end buildIterator

  static void buildIterator(vector<Node<T> *> &iterators, const Node<T> *root)
  {
    if (root == nullptr)
      return;
    buildIterator(iterators, root->left);
    iterators.push_back((Node<T> *)root);
    buildIterator(iterators, root->right);
  } // end buildIterator

  static T &insert(const T &t, Node<T> *&root, size_t &_size)
  {
    if (!root)
    {
      _size++;
      root = new Node<T>(t);
      return root->value;
    }
    if (t == root->value)
      return root->value;
    else if (t < root->value)
      return insert(t, root->left, _size);
    else
      return insert(t, root->right, _size);
  } // end insert
};

template <class T>
class nodeIterator
{
  Node<T> *node;

public:
  nodeIterator() : node{0} {}
  nodeIterator(Node<T> *newNode) : node{newNode} {}
  bool operator==(nodeIterator itr) const { return node == itr.node; }
  bool operator!=(nodeIterator itr) const { return node != itr.node; }
  nodeIterator &operator++();
  nodeIterator operator++(int);
  T &operator*() { return node->value; }
  T *operator->() { return &node->value; }
  nodeIterator &operator=(nodeIterator<T> itr)
  {
    node = itr.node;
    return *this;
  }

  friend class Set<T>;
};

template <class T>
nodeIterator<T> &nodeIterator<T>::operator++()
{
  node = node->nodeFriend;
  return *this;
}

template <class T>
nodeIterator<T> nodeIterator<T>::operator++(int)
{
  nodeIterator<T> itr(*this);
  ++(*this);
  return itr;
}

int main()
{
  Set<int> set;
  set.insert(6);
  set.insert(9);
  set.insert(4);
  set.insert(5);
  set.insert(12);
  set.insert(1);
  set.insert(5);
  set.insert(10);
  set.insert(0);
  set.insert(1);
  set.insert(11);
  set.insert(3);
  set.insert(4);
  set.insert(13);
  set.insert(9);
  set.insert(11);
  set.insert(9);
  set.insert(2);
  set.insert(3);
  set.insert(10);
  set.insert(2);

  cout << "The binary search tree implemented as a set with iterators: ";
  for (Set<int>::iterator itr = set.begin(); itr != set.end(); itr++)
    cout << *itr << " ";
  cout << endl;
}