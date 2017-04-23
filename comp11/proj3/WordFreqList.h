/* File: WordFreqList.h
     By: Ben Tanen (Tufts University // COMP-11)
   Date: 4/21/2014
  About: This file is the interface of the WordFreqList structure.
	 It declares each of the functions used by this list. */

#ifndef __WORDFREQLIST_H__
#define __WORDFREQLIST_H__

using std::string;

// this struct is how the word/frequency of each particular word is stored
struct WordFreq {
    string word;
    int    freq;
};

// these are the individual components that make up the WordFreqLists
struct  WordFreqListNode;
typedef WordFreqListNode *WordFreqList;
// whenever WordFreqList is mentioned, it refers to pointer to WordFreqListNode

WordFreqList empty      (void);
/* Function:  empty()
   Purpose:   This function returns an empty WordFreqList to be used
   Arguments: None
   Returns:   An empty list (WordFreqList)
   Effects:   None
   Notes:     None */
bool         isEmpty    (WordFreqList list);
/* Function:  isEmpty()
   Purpose:   This function checks if a certain list is empty
   Arguments: A list to check (WordFreqList)
   Returns:   True or False (bool)
   Effects:   None
   Notes:     None */
WordFreqList prepend    (WordFreq new_data, WordFreqList list);
/* Function:  prepend()
   Purpose:   This function puts a given WordFreq struct in the front of
	      a particular list
   Arguments: A new data point (WordFreq), 
	      A list that the data point is added to the front of (WordFreqList)
   Returns:   The list with the new front data point (WordFreqList)
   Effects:   None
   Notes:     None */
WordFreq     first      (WordFreqList list);
/* Function:  first()
   Purpose:   This function returns the WordFreq pair at the beginning of a
	      particular list
   Arguments: A list to use (WordFreqList)
   Returns:   The front WordFreq pair (WordFreq)
   Effects:   None
   Notes:     None */
WordFreqList rest       (WordFreqList list);
/* Function:  rest()
   Purpose:   This function returns the rest of a list (everything past
	      the first WordFreq pair)
   Arguments: A list to use (WordFreqList)
   Returns:   The rest of the list (WordFreqList)
   Effects:   None
   Notes:     None */
WordFreqList deleteFirst(WordFreqList list);
/* Function:  deleteFirst()
   Purpose:   This function returns a list without the front element
   Arguments: A list to use (WordFreqList)
   Returns:   The rest of the list (sans first element) (WordFreqList)
   Effects:   Clears the space in memory that was used by the front
	      WordFreq pair
   Notes:     None */
void         insertAfter(WordFreq new_data, WordFreqList list);
/* Function:  insertAfter()
   Purpose:   This function returns a list with a new data point added
	      after the front element
   Arguments: A new data point (WordFreq), 
	      A list that the data point is added to (WordFreqList)
   Returns:   Nothing
   Effects:   This adds the new data point between the first element of
	      the given point and the rest of the list
   Notes:     None */
void         set_freq   (int new_freq, WordFreqList list);
/* Function:  set_freq()
   Purpose:   This function sets the frequency of the first element
	      of a list to a new value
   Arguments: A new frequency value (int), 
	      A list with the element who's frequency is being changed (WordFreqList)
   Returns:   Nothing
   Effects:   This changes the frequency of the front element of a particular list
   Notes:     None */


#endif