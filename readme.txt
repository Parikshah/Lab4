How to Compile

bash
  g++ -o string_binary_tree string_binary_tree.cpp

This will compile the string_binary_tree.cpp file and generate an executable named string_binary_tree.

How to Run:

After successfully compiling the project, you can run the executable with an input file containing the binary tree in level order, followed by the desired output type (LEVELPRINT, PREPRINT, INPRINT, POSTEVAL, or POSTCOUNTCHARS). For example:

bash

  ./string_binary_tree input.txt PREPRINT

The program will process the tree and output the result based on the specified option. If an error occurs (e.g., invalid operation in POSTEVAL), the program will output ERROR.


Input Format:

The input file should contain space-separated strings representing a binary tree in level order. Use _ to represent null nodes.


Output Options:

LEVELPRINT: Prints the tree nodes in level order (including _ for nulls).
PREPRINT: Prints the tree nodes in pre-order traversal.
INPRINT: Prints the tree nodes in in-order traversal.
POSTEVAL: Evaluates the expression represented by the tree and prints the result. Supports +, -, *, / binary operators, and fact, abs unary operators.
POSTCOUNTCHARS: Counts the total number of characters in all non-null nodes and prints the sum.

                                                  
Notes:
                                                  
The program handles division by zero by printing ERROR and terminating.
The fact operator computes the factorial of a number.
Only the first line of the input file is evaluated; anything after that is ignored.
