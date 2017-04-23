#include <iostream>

using namespace std;

void draw_picture(string st1, string str2, int height); // Declare diag function
int get_int(string prompt);
string get_string(string prompt);

int main()
{
    string str1 = get_string("First string? ");
    string str2 = get_string("Second string? ");
    int height = get_int("Height? ");
    draw_picture(str1,str2,height);
    return 0;
}

int get_int(string prompt)
{
    int output;
    cout << prompt;
    cin >> output;
    return output;
}

string get_string(string prompt)
{
    string output;
    cout << prompt;
    cin >> output;
    return output;
}

void draw_picture(string str1, string str2, int height)
{
    for (int i=0;i<height;i++){
	for (int n=0;n<i;n++){
	    cout << str2;
	}
	for (int n=0;n<(height-i-1);n++){
	    cout << str1;
	}
	cout << endl;
    }
}
