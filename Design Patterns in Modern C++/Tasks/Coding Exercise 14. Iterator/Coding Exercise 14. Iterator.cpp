//Iterator Coding Exercise
//Given the following definition of a Node<T>, please implement preorder traversal that returns a sequence of Ts.
// I have greatly simplified the problem by adding an accumulator argument into the preorder_traversal()  function.
//

#include <iostream>
#include <vector>
using namespace std;

template <typename T>
struct Node
{
  T value;
  Node* left{ nullptr }, * right{ nullptr }, * parent{ nullptr };

  Node(T value) : value(value) {}

  Node(T value, Node<T>* left, Node<T>* right) : value(value), left(left), right(right) {
    left->parent = right->parent = this;
  }

  // traverse the node and its children preorder
  // and put all the results into `result`
  void preorder_traversal(vector<Node<T>*>& result)
  {
    result.push_back(this); // Add the current node to the result

    if (left != nullptr)
      left->preorder_traversal(result); // Recursively traverse the left subtree

    if (right != nullptr)
      right->preorder_traversal(result); // Recursively traverse the right subtree
  }
};