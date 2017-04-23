/***********************************************************************/
/*                          IntList Interface                          */
/***********************************************************************/
/* A minimal implementation of linked lists.                           */
/* Author:  Mark A. Sheldon, Tufts University, Fall 2012               */
/*                                                                     */
/* An IntList is either:                                               */
/*      - An empty list (the empty list)  OR                           */
/*      - A non-empty list node containing:                            */
/*           o an integer-valued first element  AND                    */
/*           o an IntList tail                                         */
/*                                                                     */
/* Operations:                                                         */
/* (see prototypes below for parameter/type information)               */
/*      empty()      : returns an empty list                           */
/*      isEmpty()    : returns true if the given list is empty,        */
/*                     and false otherwise                             */
/*      prepend()    : returns a newly allocated list node with the    */
/*                     given data value in the head and the given list */
/*                     in the tail                                     */
/*      first()      : returns the data value in the head of the       */
/*                     given non-empty list node.                      */
/*                     It is an error to call first() on an empty list.*/
/*      rest()       : returns the IntList in the rest of the given    */
/*                     non-empty list node.                            */
/*                     It is an error to call tail() on an empty list. */
/*      deleteFirst(): returns the IntList in the rest of the given    */
/*                     list.                                           */
/*                     Frees storage associated with a non-empty node. */
/*                     It is an error to call deleteFirst() on an      */
/*                     empty list.                                     */
/***********************************************************************/

#ifndef __INTLIST_H__
#define __INTLIST_H__

struct  IntListNode;
typedef IntListNode *IntList;

IntList empty      (void);
bool    isEmpty    (IntList list);
IntList prepend    (int new_data, IntList list);
int     first      (IntList list);
IntList rest       (IntList list);
IntList deleteFirst(IntList list);

#endif
