#include <iostream>

using namespace std;

int main()
{
    bool valid_date = true;
    bool leap_year = false;
    int month, day, year;
    const int jan = 1, feb = 2, mar = 3, may = 5, jul = 7, aug = 8, oct = 10, dec = 12;

    cin >> month >> day >> year;
    if ((month < 1) || (month > 12)) {  // Checks if the month is valid 
    	valid_date = false;
    }
    if ((year < 1) || (year > 9999)) { // Checks if the year is within the valid range
    	valid_date = false;
    }
 
    if ((year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0))) {
	leap_year = true;
    } 
    
    if ((month == jan) || (month == mar) || (month == may) || (month == jul) || (month == aug) || (month == oct) || (month == dec)) {
	if ((day < 1) || (day > 31)) {
	    valid_date = false;
    	}
    } else if (month == feb) {
	if ((day < 1) || (day > 28)) {
	    valid_date = false;
	}
	if ((day == 29) && (leap_year)) {
	    valid_date = true;
	}
    } else {
	if ((day < 1) || (day > 30)) {
	    valid_date = false;
	}
    }

    if (valid_date) {
	cout << 'Y' << endl;
    } else {
	cout << 'N' << endl;
    }

}
