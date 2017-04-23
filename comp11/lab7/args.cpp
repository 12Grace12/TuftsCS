//
// args.cpp -- command line arguments passed to main()
// 2012-10-23 - added "I was called with .." line

#include <iostream>
using namespace std;

int main(int numargs, char *args[])
{
        int     pos;
        string  s;

        cout << "I was called with " << numargs << " command line strings\n";
        for (pos = 0; pos < numargs ; pos++) {
                s = args[pos];
                cout << "arg " << pos << "=" << s << endl;
        }
        return 0;
}
