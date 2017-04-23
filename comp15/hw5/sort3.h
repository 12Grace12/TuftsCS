//
//  sort3.h
//  Header File for sort3 class
//  Sorting Algorithm: RadixSort
//

#ifndef __Sorting__sort3__
#define __Sorting__sort3__

#include <iostream>

struct arrayWithLength{
        int length;
        int *arr;
};

class sort3 {
public:
        sort3(); // constructor
        ~sort3();
        
        // read in a list of values from stdin
        void readList();
        
        // sort function
        void sort();

        // returns value of sigDigit for n-th place
        int sigDigit(int num, int digit);
        
        // print the array
        void printArray();
        
private:
        arrayWithLength sortArray;
};

#endif /* defined(__Sorting__sort3__) */

