//
//  sort3.cpp
//  Sorts integers using the radixSort algorithm
//  Written by Ben Tanen, 11/13/14
//


#include "sort3.h"
#include "Queue.h"

using namespace std;

sort3::sort3(){ // constructor
        sortArray.length = 0;
        sortArray.arr = NULL;
}

sort3::~sort3() {
        delete [] sortArray.arr;
}

// reads in a list of integers from stdin and returns an arrayWithLength
void sort3::readList(){
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

// sorts sortArray.arr using RadixSort
void sort3::sort(){        
        Queue buckets[10]; 
        int maxDigit = 10; // max number of digits to sort (limits of INT_MAX)

        // find maximum number in array - O(n)
        int maxNum = sortArray.arr[0];
        for (int i=0;i<sortArray.length;i++) {
                if (sortArray.arr[i] > maxNum)
                        maxNum = sortArray.arr[i];
        }
        // find maximum sigDigit of maxNum (limited by digits to sort) - O(10)
        for (int i=10;i>=0;i--) {
                if (sigDigit(maxNum,i) != 0) {
                        maxDigit = i;
                        break;
                }           
        }

        // for each sigDigit between 0 and maxDigit - O(20n)
        for (int i=0;i<=maxDigit;i++) {
                // for each element in array, put it in correct bucket - O(n)
                for (int j=0;j<sortArray.length;j++) {
                        int num = sortArray.arr[j];
                        buckets[sigDigit(num,i)].enqueue(num);
                }

                // replace each element back into array - O(n)
                int bucketNum = 0;
                for (int j=0;j<sortArray.length;j++) {
                        while (buckets[bucketNum].isEmpty()) {
                                bucketNum++;
                        }
                        
                        int test = buckets[bucketNum].dequeue();
                        sortArray.arr[j] = test;
                }
        }
}

// finds the value of the n-th significant digit of a number
int sort3::sigDigit(int num, int digit) {
        int factor = 1;
        for (int i=0;i<digit;i++) {
                factor *= 10;
        }
        return (num / factor) % 10;
}

// prints each element of array
void sort3::printArray(){
        // prints out the integers in sorted order
        for (int i=0;i<sortArray.length;i++) {
                cout << sortArray.arr[i] << endl;
        }
}


