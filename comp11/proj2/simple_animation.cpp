#include <iostream>
#include <unistd.h>

using namespace std;

void clear_screen()
{
	cout << "\033[2J";
}

void home_cursor()
{
	cout << "\33[H";
}

int main()
{
	int	pos = 0;

	clear_screen();
	for (pos = 0; pos < 30; pos++) {
		home_cursor();
		for (int i = 0; i < pos; i++)
			cout << " ";
		cout << "><>";
		home_cursor();
		cout.flush();
		usleep(250000);
	}
        return 0;
}
