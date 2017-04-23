#include "BSTree.h"


BST::BST()
{
	root = NULL;	
}

//
// Insert: public version of Insert takes a value only and
// 	   inserts in the tree at the root
//
void BST::unbalancedInsert(int v)
{
	root = unbalancedInsert(root, v);
}

//
// Insert: private version inserts a value at any subtree
//         given by the 'root' of that tree
//
//   returns: the current tree NOW WITH the value inserted
//   note: ALWAYS adds a leaf
//
BSTNode* BST::unbalancedInsert(BSTNode* r, int v)
{
	//Base Case for recursion:
	//We have reached the end of the
	//tree and we are at NULL. We
	//create a node with the correct
	//information and return a pointer
	//to the new data. This return sets
	//the value for the parent which made
	//the function call

	if(r == NULL)
	{
		r = new BSTNode;
		r->value = v;
		r->left = NULL;
		r->right = NULL;
		return r;
	}

	//notice we asked NULL first so that
	//r->left and r->right will not seg fault

	else if(v < r->value)
	{
		r->left = unbalancedInsert(r->left, v);
		return r;

	}

	else
	{
		r->right = unbalancedInsert(r->right, v);
		return r;


	}
}


//****************** inorder *****************//

void BST::inOrder()
{
	inOrder(root);		// calls the next one
}


void BST::inOrder(BSTNode* root)
{
	if (root->left != NULL) {
	    inOrder(root->left);   
	}
	
	cout << root->value << " ";
	
	if (root->right != NULL) {
	    inOrder(root->right);
	}
}



//****************** postorder *****************//



void BST::postOrder()
{	
	postOrder(root);	// calls the next one
}

void BST::postOrder(BSTNode* root)
{
      stack<BSTNode *> s;
      stack<BSTNode *> s2;
	
      s.push(root);
	
      while (!s.empty()) {
	    BSTNode* node = s.top();
	    s.pop();
	    s2.push(node);
	    
	    if (node->left != NULL)
		s.push(node->left);
	    if (node->right != NULL)
		s.push(node->right);
      }
      
      while (!s2.empty()) {
	  BSTNode* node = s2.top();
	  s2.pop();
	  cout << node->value << " ";
      }

}



//****************** preorder *****************//



// print the tree in preOrder using the next function
// Question to ponder: can we do this without a helper function?
void BST::preOrder()
{
	preOrder(root);		// calls the next one (really needed?)
}

//
// preOrder traversal using a stack of our own, not
// the one from the compiler

void BST::preOrder(BSTNode* root)
{
	//preorder with a stack
	stack<BSTNode *> s;
	//TODO: stack defined here:
	
	s.push(root);
	// print out left, push right, go down left
	
	
	while (!s.empty()) {
	    BSTNode* node = s.top();
	    s.pop();
	    
	    cout << node->value << " ";
	    if (node->right != NULL)
		s.push(node->right);
	    if (node->left != NULL)
		s.push(node->left);
	}
}



//****************** levelorder *****************//



void BST::levelOrder()
{
	levelOrder(root);
}


void BST::levelOrder(BSTNode* root)
{
	// levelOrder with a queue
	queue<BSTNode *> q;
	
	q.push(root);
	
	while (!q.empty()) {
	    BSTNode* node = q.front();
	    q.pop();
	    
	    cout << node->value << " ";
	    if (node->left != NULL)
		q.push(node->left);
	    if (node->right != NULL)
		q.push(node->right);  
	}

}
