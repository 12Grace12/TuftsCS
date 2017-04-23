
/*
 * build the animals game tree
 */

struct Node {
	string	question;
	string	animal;
	Node	*yes;
	Node	*no;
};

Node *make_tree();

