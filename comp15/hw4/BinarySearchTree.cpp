/*
 * BinarySearchTree.cpp
 * The implementation of the BinarySearchTree class
 */

#include <iostream>
#include "BinarySearchTree.h"

/* 
 * Constructor for BinarySearchTree class
 * Note: Student Written
 */
BinarySearchTree::BinarySearchTree() {
	// start with empty (NULL) tree
	root = NULL;
}

/* 
 * Destructor for BinarySearchTree class
 */
BinarySearchTree::~BinarySearchTree() {
	// walk tree in post-order traversal and delete
	post_order_delete(root);
}

/* 
 * Sudo-destructor for BST class (makes passed tree/node empty)
 * Paremeters:
 *      Node *node: pointer to a tree node (which will become empty)
 * Note: Student Written
 */
void BinarySearchTree::post_order_delete(Node *node) {
	if (node != NULL) {
		// go left
		if (node->left != NULL) {
			post_order_delete(node->left);
		}
		// go right
		if (node->right != NULL) {
			post_order_delete(node->right);
		}
		// delete self
		delete node;
		node = NULL;
	}
	
}

/* 
 * Copy constructor
 * Paremeters:
 *      source: a source BST (passed by ref) to copy
 */
BinarySearchTree::BinarySearchTree(const BinarySearchTree &source) {
	// use pre-order traversal to copy the tree
	root = pre_order_copy(source.root);
}

/* 
 * Assignment overload
 * Paremeters:
 *      source: a source BST (passed by ref) to copy
 * Note: Student Written
 */
BinarySearchTree& BinarySearchTree::operator=
		(const BinarySearchTree &source) {
	// check for self-assignment
	if (this != &source) {
		// delete current tree if it exists
		if (this->root != NULL) post_order_delete(this->root);

		// use pre-order traversal to copy the tree
		this->root = pre_order_copy(source.root);
	}

	// don't forget to "return *this"
	return *this;
}

/* 
 * Copy function (using pre-order) for BSTs
 * Paremeters:
 *      Node *node: pointer to a tree node (which will be copied)
 * Returns:
 *      Node *: pointer node to the newly copied tree
 * Note: Student Written
 */
Node * BinarySearchTree::pre_order_copy(Node *node) {
	// if passed node is NULL, return NULL
	if (node == NULL) return NULL;

	// create new_node with same data as node
	Node *new_node = new Node();
	new_node->data = node->data;
	new_node->count = node->count;

	// copy trees from left & right
	new_node->left = pre_order_copy(node->left);
	new_node->right = pre_order_copy(node->right);

	// return this new_node
	return new_node;
}

/* 
 * Function to find min of a BST
 * Note: uses helper function find_min(Node *node)
 */
int BinarySearchTree::find_min() {
	if (root == NULL) return INT_MIN;
	return find_min(root)->data;
}

/* 
 * Helper function for find_min() to find tree minimum value
 * Paremeters:
 *      Node *node: pointer to a tree node to search for min
 * Note: Student Written
 */
Node *BinarySearchTree::find_min(Node *node) {
	// if end of left branch found
	if (node->left == NULL) return node;

	// keep looking
	else return find_min(node->left);
}

/* 
 * Function to find max of a BST
 * Note: uses helper function find_max(Node *node)
 * Note: Student written
 */
int BinarySearchTree::find_max() {
	if (root == NULL) return INT_MAX;
	return find_max(root)->data;
}

/* 
 * Helper function for find_max() to find tree maximum value
 * Paremeters:
 *      Node *node: pointer to a tree node to search for max
 * Note: Student Written
 */
Node *BinarySearchTree::find_max(Node *node) {
	// if end of right branch found
	if (node->right == NULL) return node;

	// keep looking
	else return find_max(node->right);
}

/*
 * Function to find if a value is within a BST
 * Parameters:
 *      int value: value to search for in BST
 * Note: Uses helper function contains (see below)
 * Note: Student written
 */
bool BinarySearchTree::contains(int value) {
	return contains(root, value);
}

/*
 * Helper function to find if a value is within a BST
 * Parameters:
 *      Node node: pointer to tree to search through
 *      int value: value to search for in BST
 * Note: Student written
 */
bool BinarySearchTree::contains(Node *node, int value) {
	// end of branch found
	if (node == NULL) return false;

	// keep searching right
	else if (value > node->data) return contains(node->right, value);

	// keep searching left
	else if (value < node->data) return contains(node->left, value);

	// node found
	else return true;
}

/*
 * Function to insert a value into the BST
 * Parameters:
 *      int value: value to insert in BST
 * Note: Uses helper function insert (see below)
 * Note: Student written
 */
void BinarySearchTree::insert(int value) {
	insert(root,NULL,value);
}

/*
 * Helper function to insert a value within a BST
 * Parameters:
 *      Node node: pointer to tree to insert in
 *      Node parent: a pointer to the parent of given tree
 *      int value: value to insert in BST
 * Note: Student written
 */
void BinarySearchTree::insert(Node *node,Node *parent, int value) {
	// if node is NULL (either given root or inserting location)
	if (node == NULL) {
		// create new node
		node = new Node;
		node->data = value;
		node->count = 1;
		node->right = NULL;
		node->left = NULL;

		// point parent or root to node
		if (parent != NULL && value > parent->data)
			parent->right = node;
		else if (parent != NULL && value < parent->data)
			parent->left = node;
		else
			root = node;

	// search recursively
	} else if (value > node->data) {
		insert(node->right, node, value);
	} else if (value < node->data) {
		insert(node->left, node, value);

	// increment
	} else if (value == node->data) {
		(node->count)++;
	}
 }

/*
 * Function to remove a value from the BST
 * Parameters:
 *      int value: value to remove from BST
 * Note: Uses helper function remove (see below)
 */
bool BinarySearchTree::remove(int value) {
	return remove(root,NULL,value);
}

/*
 * Helper function to remove a value from a BST
 * Parameters:
 *      Node node: pointer to tree to remove from
 *      Node parent: a pointer to the parent of given tree
 *      int value: value to remove from BST
 * Note: Student written
 */
bool BinarySearchTree::remove(Node *node, Node *parent, int value) {
	// reached end of tree with no success
	if (node == NULL) return false;

	// go to the left or right to find node to delete
	else if (value > node->data) return remove(node->right, node, value);
	else if (value < node->data) return remove(node->left, node, value);
	
	// node found
	else {
		// count > 1
		if (node->count > 1) {
			(node->count)--;

		// no children
		} else if (node->right == NULL && node->left == NULL) {
			// coming from parent->right
			if (parent != NULL && node == parent->right) {
				parent->right = NULL;

			// coming from parent->left
			} else if (parent != NULL && node == parent->left) {
				parent->left = NULL;

			// parent == NULL
			} else {
				root = NULL;
			}

			delete node;
		
		// both children
		} else if (node->right != NULL && node->left != NULL) {
			Node *temp = node->right;
			while (temp->left != NULL) temp = temp->left;

			node->data = temp->data;
			node->count = temp->count;
			temp->count = 1;
			
			remove(node->right,node,temp->data);

		// left child
		} else if (node->left != NULL) {
			// coming from parent->right
			if (parent != NULL && node == parent->right) {
				parent->right = node->left;

			// coming from parent->left
			} else if (parent != NULL && node == parent->left) {
				parent->left = node->left;

			// parent == NULL
			} else {
				root = node->left;
			}

			delete node;
		
		// right child
		} else if (node->right != NULL) {
			// coming from parent->right
			if (parent != NULL && node == parent->right) {
				parent->right = node->right;

			// coming from parent->left
			} else if (parent != NULL && node == parent->left) {
				parent->left = node->right;

			// parent == NULL
			} else {
				root = node->right;
			}
			
			delete node;
		}
		return true;
	}
}

/*
 * Function to calculate height of BST
 * Note: Uses helper function tree_height (see below)
 */
int BinarySearchTree::tree_height() {
	return tree_height(root);
}

/*
 * Helper function calculate height of BST
 * Parameters:
 *      Node node: pointer to tree to calculate height of
 * Note: Student written
 */
int BinarySearchTree::tree_height(Node *node) {
	// if bottom of branch found
	if (node == NULL) return -1;

	// compare heights, return larger (plus one for current node)
	if (tree_height(node->left) > tree_height(node->right)){
		return 1 + tree_height(node->left);
	} else {
		return 1 + tree_height(node->right);
	}
}

/*
 * Function to calculate the total nodes of BST (not including duplicates)
 * Note: Uses helper function node_count (see below)
 */
int BinarySearchTree::node_count() {
	return node_count(root);
}

/*
 * Helper function for node_count()
 * Parameters:
 *      Node node: pointer to tree to calculate for
 * Note: Student written
 */
int BinarySearchTree::node_count(Node *node) {
	// if bottom of branch found
	if (node == NULL) return 0;

	// add 1 (current node) + count of left and right
	return 1 + node_count(node->left) + node_count(node->right);
}

/*
 * Function to return the sum of all the node values (including duplicates)
 * Note: Uses helper function count_total (see below)
 */
int BinarySearchTree::count_total() {
	return count_total(root);
}

/*
 * Helper function for count_total()
 * Parameters:
 *      Node node: pointer to tree to calculate for
 * Note: Student written
 */
int BinarySearchTree::count_total(Node *node) {
	// if bottom of branch found
	if (node == NULL) return 0;

	// add current count + count of left and right (totals)
	return (node->count*node->data)
		+ count_total(node->left) + count_total(node->right);
}

// use the printPretty helper to make the tree look nice
void BinarySearchTree::print_tree() {
	printPretty(root, 1, 0, std::cout);
}

Node *BinarySearchTree::find_parent(Node *node,Node *child) {
	if (node==NULL) return NULL;

	// if either the left or right is equal to the child,
	// we have found the parent
	if (node->left==child || node->right == child) {
		return node;
	}

	// Use the binary search tree invariant to walk the tree
	if (child->data > node->data) {
		return find_parent(node->right,child);
	}
	else {
		return find_parent(node->left,child);
	}
}
