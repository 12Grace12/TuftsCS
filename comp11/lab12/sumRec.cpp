#include <iostream>
using namespace std;

/*
 * sumRec.cpp - compute the sum of integers from n..0 using recursion
 */

int sum_from_n(int);

int main()
{
	int	n;
	int	sum;

	cin >> n;
	sum = sum_from_n(n);
	cout << sum << endl;
}
//
// purp: add ints from n down to 0
// args: n
// rets: the sum
//
int sum_from_n(int n)
{
        if (n == 0) {
                return 0;
        }
        else {
	    return n + sum_from_n(n-1);
	}

}
