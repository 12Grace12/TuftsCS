/* File: WordFreq.cpp
     By: Ben Tanen (Tufts University // COMP-11)
   Date: 4/21/2014
  About: This file is the main file that is used by the client.
	 It outlines the procedure by which each word is read in,
	 manipulated, and entered into the frequency table. Once done
	 reading the file, it then outputs the words alphabetically with
	 their corresponding frequencies throughout the given text. */

#include <iostream>

#include "FrequencyTable.h"

using namespace std;

int main()
{
    // create instance of FrequencyTable class
    FrequencyTable word_list;
    
    do {
	string word;
	cin >> word;
	
	// if word starts with a letter and it is not the blank string
	if (isalpha(word[0]) && word != ""){
	    // convert each letter of word to lower case
	    for (int i=0;i < word.length(); i++){
		char low_letter = tolower(word[i]);
		word[i] = low_letter;
	    }
	    
	    // add newly lower cased word to FrequencyTable
	    word_list.insert(word);
	}
    // until end of file
    } while (!cin.eof());
    
    // for each word in the frequency table
    for (int i=0;i<word_list.size();i++){
	string output_word;
	int    output_freq;
	
	// put values of each WordFreq pair in variables output_word & output_freq
	word_list.get(i,&output_word,&output_freq);
	
	// output said variables
	cout << output_freq << " " << output_word << endl;
    }
    
    // destroy the word_list after it is done being used
    word_list.destroy();
}