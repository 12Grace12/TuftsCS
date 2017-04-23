/*
 * printsequence.cpp  -- shows how to read a list of numbers into an array
 *
 *	1. First asks for the number of items in the list
 *	2. then uses a loop to read in that many values
 *	3. then prints out the list with line numbers using another loop
 */
#include <iostream>

using namespace std;

const int ARRAY_SPACE = 2000;

int main() 
{
        int bdays[ARRAY_SPACE];   // where data are stored
        int numItems;             // number of spaces used
        int pos;                  // position variable

        cout << "How many birthdays will you enter? ";
        cin  >> numItems;

        if (numItems > ARRAY_SPACE) {
                cout << "I only have space for " << ARRAY_SPACE << endl;
                return 1;
        }

        // this loop is much shorter than
        //   cin >> bdays[0]
        //   cin >> bdays[1]
        //   cin >> bdays[2]
        //   ...
        for (pos = 0; pos < numItems; pos = pos + 1) {
                cin >> bdays[pos];
        }

        // now we can print out the list with numbers
        int counter = 0;
	for (pos = 0; pos < numItems; pos = pos + 1) {
	    if ((bdays[pos] >= 1000)&&(bdays[pos] <= 1031)){
		cout << pos << ". " << bdays[pos] << endl;
		counter++;
	    }
        }
	cout << "There are " << counter << " birthdays in October." << endl;
        return 0;
}
