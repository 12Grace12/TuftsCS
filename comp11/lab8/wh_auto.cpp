#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>

using namespace std;

#include "warehouse.h"

//
// driver for Warehouse class
// uses rand to create a set of transactions
// and tests all functions reporting progress
// argv0 is seed to srand
//

void show_all(Warehouse&);

int main(int ac, char *av[])
{
	int	  seed;
	Warehouse wh;
	int	  max = wh.maxid();
	bool	  restock_list[max];
	int	  num_low;

	if ( ac == 1 || ( seed = atoi(av[1]) ) == 0 ) {
		seed = 1971;
	}
	srand(seed);

	int init = 5 + (rand() % 5);
	cout <<"Setting quantity of all " <<max + 1
             <<" items to " << init << endl;
	wh.restock(init);

	// now loop running transactions
	int transactions = 10 + (rand() % 35);

	for (int i = 0; i < transactions; i++) {
		int action, prod, amt;
		bool b_res;			  // boolean result
		int  i_res;			  // integer result

		action = (rand() % 6);
		prod   = rand() % (max + 4) - 2;  // sometimes bogus values
		amt    = (rand() % 4);

		// do remove most often
		if ((rand() % 10) < 8) {
			action = 4;
		}

		// every five loops, print list of low ones

		if (i > 0 && (i % 5) == 0) {
			action = 5;
		}

		cout << "Transaction " << i << ": ";
		switch (action) {
			case 0:	cout << " restock(" << amt << ")";
				wh.restock(amt);
				break;

			case 1:	cout << "restock("<<prod<<","<<amt<<")";
				wh.restock(prod,amt);
				break;

			case 2: cout << "is_instock(" << prod << ")";
				b_res = wh.is_instock(prod);
				cout << " returns " << ( b_res ? "T" : "F" );
				break;

			case 3:	cout << "on_hand(" << prod << ")";
				i_res = wh.on_hand(prod);
				cout << " returns " << i_res;
				break;

			case 4:	cout << "remove("<<prod<<","<<amt<<")";
				b_res = wh.remove(prod, amt);
				cout << " returns " << ( b_res ? "T" : "F" );
				break;

			case 5: amt += 3;
				cout << "running_low("<<amt<<")";
				num_low = wh.need_restock(amt, restock_list);
				cout << " returns " << num_low << endl;
				for (int i = 0; i < max; i++)
					if (restock_list[i] == true) {
						cout << "   product " << i;
						cout <<" : "
                                                     << wh.on_hand(i)
                                                     << endl;
					}
				break;
			case 6: cout << "Listing All Quantities \n";
				show_all(wh);
				break;
		}
		cout << endl;
		show_all(wh);
	}
}

//
// show all data in Warehouse
//
void show_all(Warehouse& W)
{
	int	l = W.maxid();

	cout << "  Current Warehouse Inventory\n";
	cout << "  PROD: ";
	for (int i = 0; i <= l ; i++) {
		cout << setw(4) << i ;
	}
	cout << endl;

	cout << "   QTY: ";
	for (int i = 0; i <= l ; i++) {
		cout << setw(4) <<  W.on_hand(i);
	}
	cout << endl;
	cout << endl;
	cout << endl;
}
