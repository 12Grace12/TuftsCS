//
//  sort2.h
//  Header File for sort2 class
//  Sorting Algorithm: QuickSort
//

#ifndef __Sorting__sort2__
#define __Sorting__sort2__

#include <iostream>

struct arrayWithLength{
        int length;
        int *arr;
};

class sort2 {
public:
        sort2(); // constructor
        ~sort2();
        
        // read in a list of values from stdin
        void readList();
        
        // sort function
        void sort();

        // recursive quickSort function
        void quickSort(int *arr, int start, int end);
        
        // print the array
        void printArray();
        
private:
        arrayWithLength sortArray;
};

#endif /* defined(__Sorting__sort2__) */

