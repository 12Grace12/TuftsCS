//
//  main3.cpp
//  Sorting using RadixSort
//

#include <iostream>
#include "sort3.h"

using namespace std;

int main()
{
        sort3 sorter;
        
        sorter.readList();
        sorter.sort();
        cout << "Output:\n";
        sorter.printArray();
}