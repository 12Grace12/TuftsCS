//
//  pat.cpp  -- draw a checkerboard pattern
//  version1: draws 8 rows of 8 chars alternating X and -
//  Goal: allow user to enter two strings and 
//		the number of pairs per line
//		the number lines per set
//		the number sets per image
//
//  tools: loops and functions(with arguments)
//

#include <iostream>

using namespace std;

void twolines(string s1, string s2, int per_line, int lines);
string get_string(string prompt);
int get_int(string prompt);

int main()
{
    cout << "Please enter the following to create a pattern..." << endl;
    string str1 = get_string("First string: ");
    string str2 = get_string("Second string: ");
    int per_lines = get_int("Number of string pairs per line: ");
    int lines = get_int("Number of line pairs: ");
    twolines(str1, str2, per_lines, lines);

    return 0;
}

string get_string(string prompt){
    string output;
    cout << prompt;
    cin >> output;
    return output;
}

int get_int(string prompt){
    int output;
    cout << prompt;
    cin >> output;
    return output;
}

void twolines(string s1, string s2, int per_line, int lines)
{
    string output1 = "";
    string output2 = "";
    
    for (int i=0;i<per_line;i++) {
    	output1 = output1 + s1 + s2;
	output2 = output2 + s2 + s1;
    }
    for (int i=0;i<lines;i++){
	cout << output1 << endl;
    	cout << output2 << endl;
    }
}

