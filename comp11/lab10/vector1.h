// A dynamic array with fixed size

#ifndef VECTOR_H
#define VECTOR_H

class Vector {
public:
        Vector(int capacity);           // Constructor
                                        //      args: capacity of the Vector

        ~Vector();                      // Destructor

        int  getSize();                 // Returns size of the Vector object
        int  get(int index);            // Returns element at the given index
        bool add(int element);          // Adds given element to end of array
        bool add(int element, int index);    // Places the given element at 
                                             // given index.  Index must be less
                                             // than current size of the 
                                             // Vector object

private:

        int capacity;        // Current capacity of the Vector
        int n_elements;      // Number of elements stored in the Vector object
        int *data;           // Actual data stored in the Vector
};

#endif

