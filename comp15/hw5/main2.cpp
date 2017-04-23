//
//  main2.cpp
//  Sorting using QuickSort
//

#include <iostream>
#include "sort2.h"

using namespace std;

int main()
{
        sort2 sorter;
        
        sorter.readList();
        sorter.sort();
        cout << "Output:\n";
        sorter.printArray();
}
