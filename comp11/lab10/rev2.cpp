// rev2.cpp
// Read in words, reverse, print
//  Shows: dynamically allocated variable size array

#include <iostream>
#include "vector2.h"
using namespace std;

void readin_data(Vector *data);
void rev_list   (Vector *data);
void print_list (Vector *data);

int main()
{
        Vector data;

        readin_data(&data);
        rev_list(&data);
        print_list(&data);

        return 0;
}


// -- read in a list of integers ---
//   args: data
//   rets: nothing
//   errs: quits on too many words

void readin_data(Vector *data)
{
        int n;

        cin >> n;
        while (!cin.eof()) {
                data->add(n);
                cin >> n;
        }
}


// -- reverse an array ---
//  args: Vector of int
//  rets: nothing
//  mods: reverses array

void rev_list(Vector *data)
{
        // STUB
}

// -- print out a list of strings
//  args: Vector of int
//  rets: nothing
//  mods: modifies cout, not data

void print_list(Vector *data)
{
        for (int i = 0; i < data->getSize(); i++) {
                cout << data->get(i) << endl;
        }
}
