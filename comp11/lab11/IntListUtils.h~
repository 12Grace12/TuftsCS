#ifndef __INTLISTUTILS_H__
#define __INTLISTUTILS_H__

#include "IntList.h"

// Print list in square brackets
void    print            (IntList list);

// Print list in interpretive fashion:  4 ~> 3 ~> ()
void    printArtistically(IntList list);

// Add up the elements of list
int sumList(IntList list);

// Return number of elements in list
int length(IntList list);

// Return sum of elements of list
int sumList(IntList list);

// Return a new list whose elements are the same as list
IntList copy(IntList list);

// Return a NEW list whose elements are each one greater than the 
// elements of list
IntList mapIncrement(IntList list);

// Return a NEW list whose elements are each increment greater than 
// the elements of list
IntList mapIncrementBy(IntList list, int increment);

// Return a NEW list each of whose elements are the sum of 
// the corresponding elements of list1 and list2
IntList sum(IntList list1, IntList list2);

// Return a NEW list consisting of copies of only the 
// positive elements of list.
IntList filterPositive(IntList list);

// Return a list of integers in range [lo, hi)
// E.g., range(2, 6) => [2, 3, 4, 5]
IntList range(int lo, int hi);

// Delete all the elements of list and set caller's variable
// to contain the empty list.
void deleteList(IntList *p_list);

#endif
