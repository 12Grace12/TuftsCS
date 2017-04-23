/* File: WordFreqList.cpp
     By: Ben Tanen (Tufts University // COMP-11)
   Date: 4/21/2014
  About: This file is the implementation of the WordFreqList structure.
	 It outlines how each of the functions used by this list work. */


#include <iostream>

#include "WordFreqList.h"

using namespace std;

// component that makes up WordFreqList
// contains data point and pointer to next node
struct WordFreqListNode {
    WordFreq          data;
    WordFreqListNode *next;   
};

// makes an empty list
WordFreqList empty(void)
{
    return NULL;
}

// checks if a given list is empty
bool isEmpty(WordFreqList list)
{
    return list == NULL;
}

// adds a new data element to front of existing list
WordFreqList prepend(WordFreq new_data, WordFreqList list)
{
    // creates new node (located at p_node)
    WordFreqListNode *p_node = new WordFreqListNode;
    
    // changes data of new node
    p_node->data = new_data;
    p_node->next = list;
    
    return p_node;
}

// returns the first data element of a list
WordFreq first(WordFreqList list)
{
    return list->data;
}

// returns the rest of the list (pointer to next list node)
WordFreqList rest(WordFreqList list)
{
    return list->next;
}

// deletes the first list node (returns pointer to next list node)
WordFreqList deleteFirst(WordFreqList list)
{
    WordFreqList Rest = rest(list);
    list->next = NULL;
    delete list;
    return Rest;
}

// inserts a new data element between the first list node
// and the next list node
void insertAfter(WordFreq new_data, WordFreqList list)
{
    list->next = prepend(new_data, rest(list));
}

// changes the frequency of the first node of a list
void set_freq(int new_freq, WordFreqList list)
{
    (list->data).freq = new_freq;
}



