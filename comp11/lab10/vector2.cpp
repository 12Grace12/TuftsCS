// A dynamic array that resizes as new elements are added


// including to get NULL
#include <iostream>

#include "vector2.h"

//  Initialize a vector with capacity of 10 elements
//  args: capacity of the Vector
Vector::Vector()
{
        capacity   = 10;
        data       = new int[capacity];
        n_elements = 0;
}

//  Destroys a vector
Vector::~Vector()
{
        delete [] data;
        data     = NULL;
        capacity = n_elements = 0;
}

//  Returns size of the Vector
//  rets: number of elements in the Vector
int Vector::getSize()
{
        return n_elements;
}

//  Returns capacity of the Vector
//  rets: maximum number of elements that can be stored in the Vector
int Vector::getCapacity()
{
        return capacity;
}

//  Returns element at the given index
//  args: index of the element
//  rets: element at the given index
int Vector::get(int index)
{
        // STUB
}

//  Adds the given element to end of the array.
//  args: element to be added
void Vector::add(int element)
{
        // STUB
}

//  Places the given element at the given index
//  args: element and index
void Vector::add(int element, int index)
{
        // STUB
}

//  Makes sure the vector can hold the given number of elements.
//  If it's big enough do nothing.  Otherwise, increase the size to
//  the maximum of the given newCapacity and (2 * current capacity) + 2
//   args: new capacity of the Vector
void Vector::ensureCapacity(int newCapacity)
{
        // STUB
}
