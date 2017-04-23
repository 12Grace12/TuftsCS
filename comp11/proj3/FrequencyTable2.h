/* File: FrequencyTable2.h
     By: Ben Tanen (Tufts University // COMP-11)
   Date: 4/21/2014
  About: This file is the interface of the Frequency Table class
	 for phase 2. It declares each function to be used by the class.
	 This is the faster version of FrequencyTable, in comparision to 
	 FrequencyTable1, due to its more efficient data structure.
	 See below for more information. */

#ifndef __FREQUENCYTABLE2_H__
#define __FREQUENCYTABLE2_H__

#include "WordFreqList.h"

const int alpha_letters = 26;

class FrequencyTable {
    public:
	FrequencyTable();
	/* Function:  FrequencyTable() [Constructor]
	   Purpose:   This function creates a frequency table
		      which is ultimatley used to keep track
		      of the words and their frequency in a certain
		      input text.
	   Arguments: None
	   Returns:   None
	   Effects:   This produces a frequency table class
	   Notes:     None */
	bool in(string word);
	/* Function:  in()
	   Purpose:   This function is used to check if a certain word
		      is already present in the frequency table
	   Arguments: A word to check (string)
	   Returns:   True or False (bool)
	   Effects:   None
	   Notes:     None */
	void insert(string word);
	/* Function:  insert()
	   Purpose:   This function is used to insert a word into the
		      frequency table
	   Arguments: A word to add (string)
	   Returns:   Nothing
	   Effects:   Adds the argument word to the frequency table
	   Notes:     Can be used if the word is already in the table
		      or if it is not. If the word is already present in the table,
		      the frequency is increased by one */
	int  frequency(string word);
	/* Function:  frequency()
	   Purpose:   This function returns the frequency of a certain
		      word in the frequency table
	   Arguments: A word to check (string)
	   Returns:   The frequency of said word (int)
	   Effects:   None
	   Notes:     If the word is not present in the frequency table,
		      0 is returned */
	int  size();
	/* Function:  size()
	   Purpose:   This function returns the size of the frequency table
	   Arguments: None
	   Returns:   The size of the table (int)
	   Effects:   None
	   Notes:     None */
	void get(int n, string *p_word, int *p_frequency);
	/* Function:  get()
	   Purpose:   This function is used to get the word/frequency value
		      of a particular word in the frequency table and place it
		      in the locations given by two pointers
	   Arguments: The number of the particular word being asked for (int),
		      A pointer pointing to a location to store the word (*string)
		      A pointer pointing to a location to store the freq (*int)
	   Returns:   Nothing
	   Effects:   Places the word/freq values of a particular word in the
		      locations given by the pointers
	   Notes:     This function is used to print out the contents of the
		      frequency table */
	void destroy();
	/* Function:  destory()
	   Purpose:   This function is used to destroy the frequency table once
		      it is no longer being used
	   Arguments: None
	   Returns:   Nothing
	   Effects:   Erases all of the values of the frequency table and all
		      associated memory
	   Notes:     None */
    private:
	/* This is an array containing 26 different WordFreqLists (one for
	   each letter of the alphabet). This structure is similar to that
	   of a hash table. It is significantly more efficient than the 
	   structure used by FrequencyTable1, outputting the results in a 
	      fraction of the time */
	WordFreqList list[alpha_letters];
	
	int alpha_index(string word);
	/* Function:  alpha_index()
	   Purpose:   This function is used to determine which alphabetic letter
		      list the public functions should go through. It effectively
		      converts character letters ('a', 'd', etc) to their 
		      corresponding index (0, 3, etc).
	   Arguments: The word to be tested/used (string)
	   Returns:   A corresponding index value (int)
	   Effects:   None
	   Notes:     None */
};

#endif