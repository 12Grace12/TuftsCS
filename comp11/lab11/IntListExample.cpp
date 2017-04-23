#include <iostream>

#include "IntList.h"
#include "IntListUtils.h"

using namespace std;


void   command_loop      (void);
string get_command       (void);
void   prompt_for_command(void);
IntList prepend_cmd      (IntList list);

int main()
{
	command_loop();
	return 0;
}

void command_loop(void)
{
	string  cmd;
	IntList numbers = empty();

	while ((cmd = get_command()) != "quit") {
		if (cmd == "print") {
			print(numbers);
			cout << endl;
		} else if (cmd == "printArtistically") {
			printArtistically(numbers);
			cout << endl;
		} else if (cmd == "sumList") {
			cout << sumList(numbers);
			cout << endl;
		} else if (cmd == "length") {
			cout << length(numbers);
			cout << endl;
		} else if (cmd == "prepend") {
			numbers = prepend_cmd(numbers);
		} else if (cmd == "isEmpty") {
			if (isEmpty(numbers))
				cout << "yes" << endl;
			else
				cout << "no" << endl;
		}
	}
}

string get_command(void)
{
	string cmd;

	prompt_for_command();
	cin >> cmd;

	return cmd;
}

void prompt_for_command(void)
{
	cout << "  prepend   to list"       << endl
	     << "  delete    first element" << endl
	     << "  length"                  << endl
	     << "  sumList"                 << endl
	     << "  isEmpty"                 << endl
	     << "  print     the list"      << endl
	     << "  printArtistically"       << endl
	     << "  quit"                    << endl
	     << ":  ";
}

IntList prepend_cmd(IntList list)
{
	int num;

	cout << "Enter an integer to prepend:  ";
	cin  >> num;

	return prepend(num, list);

}
