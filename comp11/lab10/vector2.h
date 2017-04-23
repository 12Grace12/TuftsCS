// A dynamic array that resizes as new elements are added

#ifndef VECTOR_H
#define VECTOR_H

class Vector {
public:

        Vector();                // Constructor:  Initializes Vector with 
                                 //               capacity of 10
        ~Vector();               // Destructor
        int  getSize();          // Returns size of the Vector
        int  getCapacity();      // Returns capacity of the Vector
        int  get(int index);     // Returns element at the given index
        void add(int element);   // Adds given element to end of array
        void add(int element,    // Places given element at given index.
                 int index);     // Index must be less than current vector size
        void ensureCapacity(int newCapacity);  // Makes sure vector has at least
                                               // this capacity, increasing
                                               // current capacity if necessary.
private:
   
        int capacity;            // Current capacity of the Vector
        int n_elements;          // Number of elements stored in the Vector
        int *data;               // Actual data stored in the Vector
};

#endif
