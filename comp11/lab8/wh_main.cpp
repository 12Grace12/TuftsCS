#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
using namespace std;

#include "warehouse.h"

//
// user program to talk to the object
//

void show_all(Warehouse&);
void do_action(int, Warehouse&);

int main()
{
	Warehouse wh;
	int	action;

	while (true) {
		cout << "Inventory management program" << endl;
		cout << "select an operation:" << endl;
		cout << "  0. restock all" << endl;
		cout << "  1. restock one" << endl;
		cout << "  2. have any?" << endl;
		cout << "  3. how many?" << endl;
		cout << "  4. ship out" << endl;
		cout << "  5. running low?" << endl;
		cout << "  6. show inventory" << endl;
		cout << "  7. quit " << endl;
		cout << endl << " choice? ";
		cin >> action;
		if (action == 7) {
			break;
		}
		do_action(action, wh);
	}
}
void do_action(int action, Warehouse &wh)
{
	int	prod, amt;
	bool	restock_list[NUM_PRODUCTS];
	int	num_low, i_res;
	bool	b_res;
	int	max = wh.maxid();

	switch (action) {
		case 0:	cout << "restock all with how many? " ;
			cin  >> amt;
			cout << " restock(" << amt << ")";
			wh.restock(amt);
			break;

		case 1:	cout << "restock which with how many? ";
			cin >> prod >> amt;
			cout << "restock("<<prod<<","<<amt<<")";
			wh.restock(prod,amt);
			break;

		case 2: cout << "product number? ";
			cin  >> prod;
			cout << "is_instock(" << prod << ")";
			b_res = wh.is_instock(prod);
			cout << " returns " << ( b_res ? "T" : "F" );
			break;

		case 3:	cout << "Check quantity of which product? ";
			cin  >> prod;
			cout << "on_hand(" << prod << ")";
			i_res = wh.on_hand(prod);
			cout << " returns " << i_res;
			break;

		case 4:	cout << "Ship how many of what product? ";
			cin  >> amt >> prod;
			cout << "remove("<<prod<<","<<amt<<")";
			b_res = wh.remove(prod, amt);
			cout << " returns " << ( b_res ? "T" : "F" );
			break;

		case 5: cout << "Which products are below what level? ";
			cin  >> amt;
			cout << "running_low("<<amt<<")";
			num_low = wh.need_restock(amt, restock_list);
			cout << " returns " << num_low << endl;
			for (int i = 0; i <= max; i++)
				if (restock_list[i]) {
					cout << "   product " << i ;
					cout <<" : " <<wh.on_hand(i) <<endl;
				}
			break;
		case 6: cout << "Listing All Quantities \n";
			show_all(wh);
			break;
	}
	cout << endl;
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
