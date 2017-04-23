//
//  sort2.cpp
//  Sorts integers using the quickSort algorithm
//  Written by Ben Tanen, 11/13/14
//


#include "sort2.h"
#include <stdlib.h>

using namespace std;

sort2::sort2(){ // constructor
        sortArray.length = 0;
        sortArray.arr = NULL;
}

sort2::~sort2() {
        delete [] sortArray.arr;
}

// reads in a list of integers from stdin and returns an arrayWithLength
void sort2::readList(){
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

// sorts sortArray.arr using QuickSort (helper function)
void sort2::sort(){
        // call quickSort function (recursive)
        quickSort(sortArray.arr,0,sortArray.length - 1);
}

// recursive quickSort function used in sort()
void sort2::quickSort(int *arr, int start, int end) {
        // checks the size of the subLists
        if (start + 1 <= end) {
                // init values for pivot, left, right
                int left = start;
                int right = end;

                // three potential values for pivot
                // int pivot = start;                       // uses first pos
                // int pivot = start + ((end - start) / 2); // uses middle pos
                int pivot = rand() % (end - start) + start; // uses random pos
                
                // swap first pos with pivot
                int pivotNum = arr[pivot];
                arr[pivot] = arr[start];
                arr[start] = pivotNum;
                pivot = start;
                
                // until left / right converge or pass each other
                while (left < right) {
                        // increment down right to value that must be swapped
                        if (arr[right] >= arr[pivot]) {
                                right--;
                        // increment up left to value that must be swapped
                        } else if (arr[left] <= arr[pivot]) {
                                left++;
                        // when values must be swapped
                        } else {
                                int temp = arr[right];
                                arr[right] = arr[left];
                                arr[left] = temp;
                        }
                }

                // swap pivot with "middle" value
                arr[pivot] = arr[right];
                arr[right] = pivotNum;
                pivot = right;

                // quickSort left of pivot
                quickSort(arr, start, pivot - 1);

                // quickSort right of pivot
                quickSort(arr, pivot + 1, end);
        } else {
                return;
        }       
}

// prints each element of array
void sort2::printArray(){
        // prints out the integers in sorted order
        for (int i=0;i<sortArray.length;i++) {
                cout << sortArray.arr[i] << endl;
        }
}


