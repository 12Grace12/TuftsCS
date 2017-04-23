#include <iostream>
#include <cstdlib>
#include <time.h>

#include "hand.h"

using namespace std;

int main(int argc, char **argv)
{
	List_linked_list test_list;

	Card c('2','C');
	Card d('5','S');
	Card e('T','S');
	Card f('8','H');
	Card g('9','D');

	test_list.insert_at_head(c);
	test_list.insert_at_head(d);
	test_list.insert_at_tail(e);
	test_list.insert_at_index(f,2);
	test_list.replace_at_index(g,1);
	test_list.print_list();
	cout << test_list.cards_in_hand() << endl;
	test_list.card_at(3).print_card();
	cout << endl;

	if (test_list.has_card(f)){
		cout << "good!" << endl;
	}

	test_list.remove_from_index(1).print_card();
	cout << endl;
	test_list.print_list();

	return 0;
}