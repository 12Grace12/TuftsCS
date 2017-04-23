/***********************************************************************/
/*                  Another IntList Implementation                     */
/***********************************************************************/

#include <iostream>

using namespace std;

#include "IntList.h"


/*
 * Representation of an IntList:  
 * A pointer to a struct with isEmpty, data, and next fields.
 *
 */
struct IntListNode {
	bool         isEmpty;
	int          data;
	IntListNode *next;
};

static IntListNode EMPTY_NODE = {true, 0, NULL};
static IntList     THE_EMPTY_LIST = &EMPTY_NODE;

/*
 * Operations on IntLists:
 *
 */

IntList empty(void)
{
	return THE_EMPTY_LIST;
}

bool isEmpty(IntList list)
{
	return list->isEmpty;
}

IntList prepend(int new_data, IntList list)
{
	IntListNode *p_node = new IntListNode;

	p_node->isEmpty = false;
	p_node->data    = new_data;
	p_node->next    = list;

	return p_node;
}

int first(IntList list)
{
	return list->data;
}

IntList rest(IntList list)
{
	return list->next;
}

/* 
 * Intended use:  my_list = deleteFirst(my_list);
 * Could pass in pointer to IntList and side-effect caller's
 * variable.
 */
// STUB:  Left as an exercise
IntList deleteFirst(IntList list)
{
	return list;  // STUB
}
