#include <iostream>
#include "BinarySearchTree.h"

using namespace std;

int main() {
  BinarySearchTree bst;

  bst.insert(12);
  bst.insert(20);
  bst.insert(15);
  bst.insert(23);
  bst.insert(5);
  bst.insert(6);
  bst.insert(3);
  bst.print_tree();
  cout << "Removing 12.\n";
  bst.remove(12);
  bst.print_tree();

  return 0;
}