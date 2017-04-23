/* File: FrequencyTable1.cpp
     By: Ben Tanen (Tufts University // COMP-11)
   Date: 4/21/2014
  About: This file is the implementation of the Frequency Table class
	 for phase 1. It outlines each function that is used by the class. 
	 This is the slower version, in comparision to FrequencyTable2, which
	 utilizes a more efficient data structure. See FrequencyTable2.h for
	 more information. */

#include <iostream>

#include "FrequencyTable1.h"
#include "WordFreqList.h"

using namespace std;

// used to construct/initalize a FrequencyTable instance
FrequencyTable::FrequencyTable()
{
    // make list empty
    list = empty();
}

// used to check if a certain word is in list
bool FrequencyTable::in(string word)
{
    // create new temp list
    WordFreqList temp;
    temp = list;
    // go through list until temp is empty (end of list)
    while (!isEmpty(temp)) {
	// if word found
	if (first(temp).word == word) {
	    return true;
	} else {
	    temp = rest(temp);
	}
    }
    
    // if end of list is reached but word not found
    return false;
}

// used to insert a word into the FrequencyTable (or increase
// the frequency by one (if word already in list)
void FrequencyTable::insert(string word)
{
    // if word is in list
    if (in(word)) {
	WordFreqList temp = list;
	// find word
	while (first(temp).word != word)
	    temp = rest(temp);
	// increase frequency by one
	set_freq(first(temp).freq + 1, temp);
    // otherwise
    } else {
	// make new data point (where word is given word and freq is 1)
	WordFreq new_data;
	new_data.word = word;
	new_data.freq = 1;
	// if list is empty (no words yet)
	if (isEmpty(list)) {
	    // add data point to front
	    list = prepend(new_data, list);
	// if first word of list comes after given word alphabetically
	} else if (first(list).word > word) {
	    // add data point to front
	    list = prepend(new_data, list);
	} else {
	    WordFreqList temp = list;
	    // go through list until list is emppty or next word comes after given word
	    while (rest(temp) != NULL && first(rest(temp)).word < word) {
		temp = rest(temp);
	    }
	    // insert given word after this point
	    insertAfter(new_data, temp);
	}
    }
}

// used to return the frequency of a certain word in the list
int FrequencyTable::frequency(string word)
{
    // if word is in list
    if (in(word)){
	WordFreqList temp = list;
	// search through list until word found
	while (first(temp).word != word)
	    temp = rest(temp);
	// return its frequency
	return first(temp).freq;
    // otherwise
    } else {
	return 0;
    }
}

// used to return the size of the FrequencyTable instance
int FrequencyTable::size()
{
    WordFreqList temp = list;
    int list_length = 0;
    // add one to list_length until reach end of list
    while (!isEmpty(temp)){
	  temp = rest(temp);
	  list_length++;
    }
    return list_length;
}

// used to pass values of FrequencyTable by reference (used for printing
// purposes)
void FrequencyTable::get(int n, string *p_word, int *p_frequency)
{
    WordFreqList temp = list;
    // go from word to word until nth word
    for (int i=0;i<n;i++)
	temp = rest(temp);
    
    // store the values for this WordFreq pair in the given locations
    *p_word = first(temp).word;
    *p_frequency = first(temp).freq;
}

// used to destroy the FrequencyTable instance once it is done.
void FrequencyTable::destroy()
{
    // delete each WordFreq pair until end
    while (!isEmpty(list)) {
	list = deleteFirst(list);
    }
	
}

