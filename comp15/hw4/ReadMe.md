# ReadMe for COMP 15 HW4
## Binary Search Tree Assignment 
### Written by Ben Tanen, 10/23/14

**Purpose**: The purpose of this project was to implement a Binary Search Tree.
The tree was implemented like most standard trees (linked nodes of varying 
depths) with some more complexity (keeping it a binary search tree). Like 
standard BSTs, the user can add and remove from the tree and get information (
tree height, max value, etc.) from it. For the sake of the assignment, most of 
the work involved is done in the BinarySearchTree.cpp file.

* * *

**Included Files**:

`main.cpp`: The main file that is used to runs the BST(s)

`BinarySearchTree.cpp`: The implementation of the BST class (largely student written).

`BinarySearchTree.h`: The interface of the `BST` class (no real changes).

`pretty_print.cpp`: The included file to print out the BSTs (see for doc)

`ReadMe.md`: The README, which gives a brief description of the program.

`Makefile`: The Makefile used to compile the program using clang++.

* * *

**Compile Instructions**: To compile the program, use the included Makefile.

* * *

**Data Structure(s)**: Binary Search Trees, like standard trees, are interesting
because they are both ADTs as well as data structures (depending on how you look
at it). The BST was implemented using a 'tree' of node structs that would point
to other nodes (or NULL). Implemented similar to a linked list (or tree/BST). 

* * *

**Algorithm(s)**: There were no underlying algorithms used in this assignment.
However, pretty much every function is a least a little recursive, which is a
fairly standard approach to BSTs and trees in general. Only other mentionable
algorithms would be the use of pre-order and post-order tree traversal for the
tree copying (copy constructor & assignment overload) and tree deletion
respectively. 

