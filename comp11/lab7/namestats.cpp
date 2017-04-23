// namestats.cpp -- age stats by names
//   usage: namestats name < datafile-of-year-name
// 
//  result: find avg, then range of ages and frequency by age
//  history: revised 2012-10-23 added 'who' to show_freq

#include <iostream>
#include <cstdlib>

using namespace std;


struct Person {
    string name;
    int    age;
};

const int MAXPEOPLE = 50000;
const int SENTINEL  = -1;
const int NOW       = 2013;

void    read_in_data(Person person[], int sentinel, int array_size);
string  get_name    (int numargs, char *args[]);
void	print_ages  (Person person[], int sentinel, string who);
void    do_stats    (Person person[], int sentinel, string who);
int	find_max    (Person person[], int sentinel, string name);
int	find_min    (Person person[], int sentinel, string name);
double	find_avg    (Person person[], int sentinel, string name);
void	show_freq   (Person person[], int sentinal, string name,
                     int min, int max);

int main(int numargs, char *args[])
{
	Person	people[MAXPEOPLE];
	string	name;
	cout << numargs << endl;

	read_in_data(people, SENTINEL, MAXPEOPLE);
	name = get_name(numargs, args);
	print_ages(people, SENTINEL, name);
	do_stats(people, SENTINEL, name);

	return 0;
}

// --- read_in_data ------------------------------------------------------
//  args: array of Person structs, sentinel, max space in array
//  rets: nothing
//  does: reads from cin a year and name, puts sentinel in array
//  errs: calls exit if out of space
//
void read_in_data(Person person[], int sentinel, int space)
{
	int	yr;
	string	nm;
	int	pos = 0;

	do {
		cin >> yr >> nm ;
		if (pos >= space) {
			cerr << "Out of space\n";
			exit(1);
		}
		person[pos].name = nm;
		person[pos].age  = NOW - yr;
		pos++;
	} while (yr != sentinel);
}

// --- get_name ----------------------------------------------------------
//  purp: read in one name from cin
//  args: none
//  rets: the name
string get_name(int numargs, char *args[])
{
    	string nm;
	if (numargs >= 2){
	    nm = args[1];
	} else {
	    cin >> nm;
	}  	
        return nm;
}

// --- print_ages -------------------------------------------------------
//  purp: print all ages for the specified name
//  args: an array of structs, the sentinel, the name to find
//  rets: nothing
//  does: prints report to cout
//
void print_ages(Person person[], int sentinel, string who)
{
    	int pos = 0;
	do {
	    if (person[pos].name == who){
		cout << person[pos].age << endl;
	    }
	    pos++;
	} while (person[pos].age != (NOW - sentinel));	
}

// --- do_stats ----------------------------------------------------------
//  purp: compute and print avg, range AND freq for each age in range
//  args: an array of structs, the sentinel, the name to find
//  rets: nothing
//  does: prints report to cout
//
void do_stats(Person person[], int sentinel, string who)
{
	int	min, max;	// min and max age for 'who'
	double	avg;

	avg = find_avg(person, sentinel, who);
	min = find_min(person, sentinel, who);
	max = find_max(person, sentinel, who);
	if (min == 1000){
	    min = 0;
	}
	cout << "name: " << who << endl;
	cout << "average: " << avg << endl;
	cout << "range: "   << min << "-" << max << endl;
	show_freq(person, sentinel, who, min, max);
}

double find_avg(Person person[], int sent, string name)
{
    	int pos = 0;
	double sum = 0;
	double counter = 0;
	do {
	    if (person[pos].name == name){
		sum +=  person[pos].age;
		counter++;
	    }
	    pos++;
	} while (person[pos].age != (NOW - sent));	
        return (sum/counter);
}

int find_min(Person person[], int sent, string name)
{
    	int pos = 0;
	int min = 1000;
	do {
	    if (person[pos].name == name){
		if (person[pos].age < min){
		    min = person[pos].age;
		}
	    }
	    pos++;
	} while (person[pos].age != (NOW - sent));
        return min;
}

int find_max(Person person[], int sent, string name)
{
        int pos = 0;
	int max = 0;
	do {
	    if (person[pos].name == name){
		if (person[pos].age > max){
		    max = person[pos].age;
		}
	    }
	    pos++;
	} while (person[pos].age != (NOW - sent));
        return max;
}

void show_freq(Person person[], int sent, string who, int min, int max)
{
    for (int i=min;i<max+1;i++){
    	int count = 0;
	int pos = 0;
	do {
	    if (person[pos].name == who && person[pos].age == i){
		count++;
	    }
	    pos++;
	} while (person[pos].age != (NOW - sent));
	if (count > 0){
		cout << i << " " << count << endl;
	}

    }
}
