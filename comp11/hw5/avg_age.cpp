// This program takes in years and names, adds them to an array
// and then finds the average of a given name (based on the previous inputs
//
// By: Ben Tanen, COMP11, 2/23/2014
//

#include <iostream>
using namespace std;

// - - - Function Declerations - - - //
double avg_age(string name, string names[], int age[]);

const int CURRENT_YEAR = 2014;       // Define the current year
const int array_space = 50000;       // Define how many names/ages to hold

int main()
{
    int    ages[array_space+1];        // Initialize a space to store all the ages
    string names[array_space+1];       // Initialize a space to store all the names

    for (int i=0;i<((array_space)*2)+1;i++){ 
	int    age_input;
	string name_input;
    
	if (i%2 == 0) {              // Test if it is even (to take in age)
	    cin >> age_input;
	    ages[i/2] = age_input;
	    if (age_input == -1){    // Test if the input was the sentinel
		cin >> name_input;
		names[i/2] = name_input;
		break;
	    }
	} else if (i%2 == 1) {       // Test if it is odd (to take in name)
	    cin >> name_input;
	    names[i/2] = name_input;
	}

	if (i == (array_space*2)){   // Test if the max limit has been reached
	    cerr << "too much data" << endl;
	    return 1;
	}
    }
    string search_name;
    cout << "Enter a name: ";
    do {                                         // Make sure the name taken in is actually a name
	cin >> search_name;
    } while ((search_name == "") || (search_name == " "));
    if (avg_age(search_name,names,ages) == -1 || avg_age(search_name,names,ages) > CURRENT_YEAR)  { // If the name is not found, avg_age returns -1
	cout << "name not found" << endl;        // Thus, main() will print "name not found"
    
    } else {                                     // All other conditions (if the avg_age is not -1)
	cout << "average age = " << avg_age(search_name,names,ages) << endl;
    }
}

double avg_age(string name, string names[], int ages[])
{
    double sum_age = 0;
    double counter = 0;
    for (int i=0;i<array_space;i++){
	if (names[i] == name) {                  // if name from array element is the same as the given name
	    sum_age += (CURRENT_YEAR - ages[i]); // find difference between current year and person's birth year (age)
	    counter++;                           // add to counter
	}
    }
    if (counter > 0){
	return (sum_age/counter);
    } else {
	return -1;
    }
}
