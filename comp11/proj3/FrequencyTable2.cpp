/* File: FrequencyTable2.cpp
     By: Ben Tanen (Tufts University // COMP-11)
   Date: 4/21/2014
  About: This file is the implementation of the Frequency Table class
	 for phase 2. It outlines each function that is used by the class.
	 This is the faster version of FrequencyTable, in comparision to 
	 FrequencyTable1, due to its more efficient data structure.
	 See FrequencyTable2.h for more information. */

#include <iostream>

#include "FrequencyTable2.h"
#include "WordFreqList.h"

using namespace std;

// used to construct/initalize a FrequencyTable instance
FrequencyTable::FrequencyTable()
{
    // makes each letter list empty
    for (int i=0; i < alpha_letters; i++) {
	list[i] = empty();
    }
}

// used to check if a certain word is in list
bool FrequencyTable::in(string word)
{
    WordFreqList temp;
    // alpha_index() goes to the list for the first letter of the 
    // entered word int(word[0]) returns the ASCII value for the 
    // given letter ASCII value of 'a' is 97. Thus, 97-97=0, which 
    // return the first list of the list[] array. See below for more
    int index = alpha_index(word);
    temp = list[index];
    
    // goes through list until temp is empty (end of list)
    while (!isEmpty(temp)) {
	if (first(temp).word == word) {
	    return true;
	} else {
	    temp = rest(temp);
	}
    }
    
    // if end of list is reached before finding word, word not in list
    return false;
}

// used to insert a word into the FrequencyTable (or increase
// the frequency by one (if word already in list)
void FrequencyTable::insert(string word)
{
    // see below function alpha_index() for explanation of below
    int index = alpha_index(word);
    
    // if the word is in the list
    if (in(word)) {
	WordFreqList temp = list[index];
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
	// if particular letter list is empty (no words yet)
	if (isEmpty(list[index])) {
	    // add data point to front
	    list[index] = prepend(new_data, list[index]);
	// if first word of list comes after given word alphabetically
	} else if (first(list[index]).word > word) {
	    // add data point to front
	    list[index] = prepend(new_data, list[index]);
	// otherwise
	} else {
	    WordFreqList temp = list[index];
	    // go through list until list is empty or next word comes after given word
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
    // see below function alpha_index() for explanation of below
    int index = alpha_index(word);
    
    // if word is in list
    if (in(word)){
	WordFreqList temp = list[index];
	// search through list for word
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
    int list_length = 0;
    // for each of the 26 letters
    for (int i=0; i < alpha_letters; i++){
	WordFreqList temp = list[i];
	// add one to list_length until reach end
	while (!isEmpty(temp)){
	      temp = rest(temp);
	      list_length++;
	}
    }
    return list_length;
}

// used to pass values of FrequencyTable by reference (used for printing
// purposes)
void FrequencyTable::get(int n, string *p_word, int *p_frequency)
{
    // start at 'a' list
    int list_index = 0;
    
    // go until first list is non-empty
    while (isEmpty(list[list_index]))
	list_index++;  
    WordFreqList temp = list[list_index];
    
    // go from word to word until nth word
    for (int i=0;i<n;i++) {
	// if list is empty (reached end)
	if (isEmpty(rest(temp))){
	    // search until next non-empty list
	    do {
		list_index++;
	    } while (isEmpty(list[list_index]));
	    temp = list[list_index];
	} else {
	    temp = rest(temp);
	}
    }
    
    // store the values for this WordFreq pair in the given locations
    *p_word = first(temp).word;
    *p_frequency = first(temp).freq;
}

// used to destroy the FrequencyTable instance once it is done.
void FrequencyTable::destroy()
{
    // go through each of the 26 letters
    for (int i=0; i < alpha_letters; i++){
	// delete each WordFreq pair until end
	while (!isEmpty(list[i])) {
	    list[i] = deleteFirst(list[i]);
	}
    }	
}

// used to return the corresponding array index for each alphabetic
// letter ('a' to 0, 'b' to 1, etc)
int FrequencyTable::alpha_index(string word)
{
    // word[0] returns the character of the first letter of string word
    // int(x) returns the ASCII value of variable x (in this case, the first letter)
    // -97 is because the first letter 'a' has an ASCII value of 97 (thus, 'a' -> 0)
    return int(word[0]) - 97;
}

