/*
 * main.cpp
 *
 *  Created on: Oct 13, 2014
 *      Author: chrisgregg
 */

#include <iostream>
#include "BinarySearchTree.h"

using namespace std;

void print_tree_details(BinarySearchTree &bst) {
	bst.print_tree();
	cout << "\n";
	cout << "min: " << bst.find_min() << "\n";
	cout << "max: " << bst.find_max() << "\n";
	cout << "nodes: " << bst.node_count() << "\n";
	cout << "count total: " << bst.count_total() << "\n";
	cout << "tree height: " << bst.tree_height() << "\n";
	cout << "\n";
}

int main() {

	int rand_ints[12]={5,3,6,11,-5,-2,15,4,4,9,14,8};

	BinarySearchTree bst;
	for (int i=0;i<12;i++) {
		cout << "Inserting " << rand_ints[i] << "\n";
		bst.insert(rand_ints[i]);
	}
	bst.print_tree();
	cout << "Removing 5.\n";
	bst.remove(5);
	bst.print_tree();

	return 0;

/*
	BinarySearchTree test;
	int insert_num[10] = {7, 9, 3, 8, 11, 5, 11, 8, 10, 6};

	for (int i=0;i<10;i++) test.insert(insert_num[i]);

	print_tree_details(test);

	cout << test.remove(9);
	cout << endl;

	print_tree_details(test);
	
	return 0;
*/
}
