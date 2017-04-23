//
//  SelectionSort.cpp
//  Sorts integers using the SelectionSort algorithm
//  Written by Ben Tanen, 11/13/14
//


#include "SelectionSort.h"

using namespace std;

SelectionSort::SelectionSort() { // constructor
        sortArray.length = 0;
        sortArray.arr = NULL;
}

SelectionSort::~SelectionSort() {
        delete [] sortArray.arr;
}

// reads in a list of integers from stdin and returns an arrayWithLength
void SelectionSort::readList(){
        int currentCapacity = 10;
        sortArray.arr = new int[currentCapacity];
        
        while (cin >> sortArray.arr[sortArray.length]) {
                ++sortArray.length;
                if (sortArray.length==currentCapacity) {
                        int *temp = new int[currentCapacity*2];
                        for (int i=0;i<currentCapacity;i++) {
                                temp[i] = sortArray.arr[i];
                        }
                        delete [] sortArray.arr;
                        sortArray.arr = temp;
                        currentCapacity *= 2;
                }
        }
}

void SelectionSort::sort(){
        // reposition each element of array - O(n^2)
        for (int i=0;i<sortArray.length;i++) {

                // initialize smallInt (and location) to starter elem
                int smallInt = sortArray.arr[i];
                int smallIntIndex = i;

                // compare to all other elem @ greater index (to right) - O(n)
                for (int j=i+1;j<sortArray.length;j++) {

                        // make new smallInt if in fact smaller
                        if (sortArray.arr[j] < smallInt) {
                                smallInt = sortArray.arr[j];
                                smallIntIndex = j;
                        }
                }

                // adjust accordingly
                sortArray.arr[smallIntIndex] = sortArray.arr[i];
                sortArray.arr[i] = smallInt;
        }
}

void SelectionSort::printArray(){
        // prints out the integers in sorted order
        for (int i=0;i<sortArray.length;i++) {
                cout << sortArray.arr[i] << endl;
        }
}


