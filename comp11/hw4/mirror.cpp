#include <iostream>

using namespace std;

void mirror(int max_num); // Declare mirror function

int main()
{
    int max_num;

    cout << "Maximum value? ";
    cin >> max_num;
    if (max_num > -1) {
	mirror(max_num);
    }

    return 0;
}

void mirror(int max_num)
{
    for (int n=0;n<4;n++){
	for (int i=0;i<max_num+1;i++){
	    cout << i;
	}

	cout << '|';

	for (int i=max_num;i>-1;i--){
	    cout << i;
	}

	cout << endl;
    }

}
