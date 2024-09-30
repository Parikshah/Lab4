//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
// CISC220-080 Lab #4 starter code
// September, 2023 -- Prof. Christopher Rasmussen
//----------------------------------------------------------------------------

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

//----------------------------------------------------------------------------

#define ROOT_INDEX  1
#define NULL_TOKEN  "_"  // node value indicating empty

//----------------------------------------------------------------------------

// This class implements a binary tree of strings (therefore not templatized) with an STL vector

class StringBinaryTree
{
public:

  // these functions are already defined
  
  StringBinaryTree() { V.resize(1); V[0] = string(NULL_TOKEN); numNodes = 0; }  // V[0] will represent nullptr
  string & elementAt(int);
  string & root() { return elementAt(ROOT_INDEX); }
  bool isRoot(string & s) { return indexOf(s) == ROOT_INDEX; }
  void levelInsert(string &);
  int size() { return numNodes; }
  int indexOf(string &);
  string & leftChild(string &);
  string & rightChild(string &);

  bool isNull(string & s) { return s == NULL_TOKEN; }
  bool isLeaf(string & s) { return !isNull(s) && isNull(leftChild(s)) && isNull(rightChild(s)); }
  bool isInternal(string & s) { return !isLeaf(s); }
  
  void levelPrint();
  void preOrderPrint();
  void inOrderPrint();
  int postOrderEvaluate();
  int postOrderCountChars();
  
  // these functions must be written
  
  void preOrderPrint(string &);
  void inOrderPrint(string &);
  int postOrderEvaluate(string &);
  int postOrderCountChars(string &);
  
private:
  vector<string> V;    // all nodes, including empty 
  int numNodes;        // number of non-empty nodes
  
};

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

// return reference to node at given index.
// root is at index 1

string & StringBinaryTree::elementAt(int index)
{
  if (index < ROOT_INDEX || index >= V.size())
    throw out_of_range{"Index not in vector"};
  else
    return V[index];
}

//----------------------------------------------------------------------------

// put a new node at the "end" of the tree according to level order

void StringBinaryTree::levelInsert(string & s)
{
  V.push_back(s);
  if (!isNull(s))
    numNodes++;
}

//----------------------------------------------------------------------------

// given a reference to a node, figure out its index with pointer arithmetic.

int StringBinaryTree::indexOf(string & s)
{
  string const *data = V.data();
  
  if (less<string const *>{}(&s, data) || greater_equal<string const *>{}(&s, data + V.size()))
    throw out_of_range{"Item not part of vector"};
  
  return static_cast<size_t>(&s - V.data());
}

//----------------------------------------------------------------------------

// return a reference to this node's left child if it exists

string & StringBinaryTree::leftChild(string & s)
{
  int leftChildIndex = 2 * indexOf(s);

  // in bounds?
  
  if (leftChildIndex < V.size())
    return elementAt(leftChildIndex);

  // out of bounds (this is our way of saying "null" with a string)
  
  else
    return V[0];
}

//----------------------------------------------------------------------------

// return a reference to this node's right child if it exists

string & StringBinaryTree::rightChild(string & s)
{
  int rightChildIndex = 1 + 2 * indexOf(s);

  // in bounds?
  
  if (rightChildIndex < V.size())
    return elementAt(rightChildIndex);

  // out of bounds (this is our way of saying "null" with a string)

  else
    return V[0];
}

//----------------------------------------------------------------------------

// iterate through every element in level order.
// print even NULL elements for debugging purposes

void StringBinaryTree::levelPrint()
{
  for (int i = ROOT_INDEX; i < V.size(); i++) 
    cout << V[i] << " ";
  cout << endl;
}

//----------------------------------------------------------------------------

// print every non-NULL element in the tree according to PRE-ORDER traversal

void StringBinaryTree::preOrderPrint()
{
  preOrderPrint(root());
  cout << endl;
}

//----------------------------------------------------------------------------

// print every non-NULL element in the tree according to IN-ORDER traversal,
// starting with root

void StringBinaryTree::inOrderPrint()
{
  inOrderPrint(root());
  cout << endl;
}

//----------------------------------------------------------------------------

// treat tree like an expression tree and evaluate it to a single number

int StringBinaryTree::postOrderEvaluate()
{
  return postOrderEvaluate(root());
}

//----------------------------------------------------------------------------

// sum up lengths of every string in tree (except NULL elements) 

int StringBinaryTree::postOrderCountChars()
{
  return postOrderCountChars(root());
}

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

// FILL IN THIS FUNCTION

// recursively print every string in subtree with root node, followed by a space,
// according to PRE-ORDER traversal 

void StringBinaryTree::preOrderPrint(string & node)
{
  if (isNull(node)) return;  // Base case: if the node is null, stop recursion

  // Print the current node
  cout << node << " ";

  // Recursively print the left and right children
  preOrderPrint(leftChild(node));
  preOrderPrint(rightChild(node));
}

//----------------------------------------------------------------------------

// FILL IN THIS FUNCTION

// recursively print every string in subtree with root node, followed by a space,
// according to IN-ORDER traversal 

void StringBinaryTree::inOrderPrint(string & node)
{
  if (isNull(node)) return;  // Base case: if the node is null, stop recursion

  // Recursively print the left child
  inOrderPrint(leftChild(node));

  // Print the current node
  cout << node << " ";

  // Recursively print the right child
  inOrderPrint(rightChild(node));
}

//----------------------------------------------------------------------------

// FILL IN THIS FUNCTION

// recursively evaluate expression subtree with root node according to POST-ORDER traversal.
// see lab description for details

int StringBinaryTree::postOrderEvaluate(string & node)
{
  if (isNull(node)) return 0;  // Base case: if the node is null, stop recursion

  // If the node is a leaf, it's a number (operand), so convert it to an integer
  if (isLeaf(node)) return stoi(node);

  // Recursively evaluate the left and right children
  int leftValue = postOrderEvaluate(leftChild(node));
  int rightValue = postOrderEvaluate(rightChild(node));

  // Handle binary operators
  if (node == "+") return leftValue + rightValue;
  else if (node == "-") return leftValue - rightValue;
  else if (node == "*") return leftValue * rightValue;
  else if (node == "/") {
      if (rightValue == 0) {
          cout << "ERROR\n";  // Handle division by zero
          exit(1);
      }
      return leftValue / rightValue;
  }

  // Handle unary operators
  else if (node == "fact") return tgamma(leftValue + 1);  // Factorial: use gamma function
  else if (node == "abs") return abs(leftValue);  // Absolute value

  // If we encounter an invalid operator, print an error and exit
  cout << "ERROR\n";
  exit(1);
}

//----------------------------------------------------------------------------

// FILL IN THIS FUNCTION

// sum up lengths of every string in subtree with root node (except NULL elements) 

int StringBinaryTree::postOrderCountChars(string & node)
{
  if (isNull(node)) return 0;  // Base case: if the node is null, stop recursion

  // Recursively count characters in the left and right children
  int leftCount = postOrderCountChars(leftChild(node));
  int rightCount = postOrderCountChars(rightChild(node));

  // Count the characters in the current node (not including null nodes)
  return leftCount + rightCount + node.length();
}

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

int main(int argc, char** argv)
{
  StringBinaryTree SBT;
  
  // try to open input file
  
  ifstream inStream;
  string word;
  
  if (argc < 3) {
    cout << "Please specify filename AND output type (PREPRINT, INPRINT, or POSTEVAL) on command line\n";
    exit(1);
  }
  
  inStream.open(argv[1]);

  if (inStream.fail()) {
    cout << "Failed to open file " << argv[1] << endl;
    exit(1);
  }

  // read tree word by word in level order
  
  while (inStream >> word) {    
    if (!inStream.eof()) 
      SBT.levelInsert(word);
  }

  inStream.close();

  // output in desired format

  string output_type(argv[2]);
  
  if (output_type == "LEVELPRINT")
    SBT.levelPrint();
  else if (output_type == "PREPRINT")
    SBT.preOrderPrint();
  else if (output_type == "INPRINT")
    SBT.inOrderPrint();
  else if (output_type == "POSTEVAL") {
    cout << fixed;
    cout << SBT.postOrderEvaluate() << endl;
  }
  else if (output_type == "POSTCOUNTCHARS") {
    cout << fixed;
    cout << SBT.postOrderCountChars() << endl;
  }
  
  return 1;
}

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
