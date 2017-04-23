// - - - Implementation of LIST_DYNAMIC_ARRAY Class - - -
// Written Partially by Ben Tanen, 9/12/14
// Purpose: Defines how each of the class's functions work.
// Note: A large portion of the following functions were by Ben Tanen for hw1 of COMP-15 (Tufts University, Fall 2014)

#include "List_dynamic_array.h"

#include <iostream>
#include <cassert>

using namespace std;

List_dynamic_array::List_dynamic_array()
{
	// STUDENT WRITTEN
	// create list
	cards_held = 0;
	hand_capacity = 10; // initialize with capacity of 10
	cards = new Card[hand_capacity];
}

List_dynamic_array::~List_dynamic_array()
{
    // STUDENT WRITTEN
	// delete list
	delete[] cards;

	// need to delete anything else?
}

// copy constructor
List_dynamic_array::List_dynamic_array(const List_dynamic_array& source) {
	// explicit copy constructor necessary because of cards array
	cards_held = source.cards_held;
	hand_capacity = source.hand_capacity;

	cards = new Card[hand_capacity];
	for (int i=0;i<cards_held;i++) {
		cards[i] = source.cards[i];
	}
}

// operator= overload
List_dynamic_array List_dynamic_array::operator =(const List_dynamic_array&
		source) {
	// explicit operator= overload necessary because of cards array
	Card *new_cards;

	// check for self-assignment -- return without doing anything
	if (this == &source) {
		return *this;
	}

	hand_capacity = source.hand_capacity;
	cards_held = source.cards_held;
	new_cards = new Card[hand_capacity];
	for (int i=0;i<hand_capacity;i++) {
		new_cards[i]=source.cards[i];
	}
	delete [ ] cards;
	cards = new_cards;
	return *this;
}

void List_dynamic_array::print_list()
{
	for(int i=0; i<cards_held; i++) {
		cards[i].print_card();
		if (i != cards_held-1) {
			cout << ",";
		} else {
			cout << "\n";
		}
	}
}

void List_dynamic_array::print_list_int()
{
	for(int i=0; i<cards_held; i++) {
		cards[i].print_card_int();
		if (i != cards_held-1) {
			cout << ", ";
		} else {
			cout << "\n";
		}
	}
}

void List_dynamic_array::insert_at_head(Card c)
{
    // STUDENT WRITTEN
	// check if we need to expand, and expand if necessary
	if (cards_held == hand_capacity){
		expand();
	}

	// move all items over one, starting from the last one
	for (int i=cards_held-1; i >= 0; i--) {
		cards[i+1] = cards[i];
	}

	// insert the new card
	cards[0] = c;

	// update cards_held
	cards_held = cards_held + 1;
}

void List_dynamic_array::insert_at_tail(Card c)
{
    // STUDENT WRITTEN
	// check if we need to expand, and expand if necessary
	if (cards_held == hand_capacity){
		expand();
	}

	// insert the new card at the end
	cards[cards_held] = c;

	// update cards_held
	cards_held = cards_held + 1;
}

void List_dynamic_array::insert_at_index(Card c,int index)
{
	// if index is greater than cards_held, then fail
	assert(index <= cards_held);
	
	// STUDENT WRITTEN
	// check if we need to expand, and expand if necessary
	if (cards_held == hand_capacity){
		expand();
	}

	// move all elements past the insertion point up one
	for (int i=cards_held-1; i>=index; i--){
		cards[i+1] = cards[i];
	}

	// insert the card
	cards[index] = c;

	// update cards_held
	cards_held = cards_held + 1;
}

void List_dynamic_array::replace_at_index(Card c, int index) {
	// if index is greater than cards_held-1, then fail
	assert(index < cards_held);

	// STUDENT WRITTEN
	// replace the card at index with c
	cards[index] = c;
}

Card List_dynamic_array::card_at(int index)
{
	// if index is out of bounds, fail
	assert (index >= 0 && index < cards_held);
	
	// STUDENT WRITTEN
	// return the card at index
	return cards[index];
}

bool List_dynamic_array::has_card(Card c) 
{    
    // STUDENT WRITTEN
    // loop through the cards and use the same_card()
    for (int i=0; i<cards_held; i++){
    	if (cards[i].same_card(c)){
    		return true;
    	}
    }

    // Returns true if the card is in the hand, false otherwise
    return false;
}

bool List_dynamic_array::remove(Card c)
{
    // STUDENT WRITTEN
	// if list empty, fail
	if (cards_held == 0){
		return false;
	}

	// find the card
	int card_index = -1;
	for (int i=0; i<cards_held; i++){
		if (cards[i].same_card(c)) {
			card_index = i;
			break;
		} else if (i+1 == cards_held) {
			return false;
		}
	}

	// move all cards (after card) forward 1 space
	for (int i=card_index; i<cards_held; i++){
		cards[i] = cards[i+1];
	}

	// cards_held updated
	cards_held = cards_held - 1;
	return true;
}

Card List_dynamic_array::remove_from_head()
{
	// if the list is empty, fail
	assert(cards_held > 0);

    // STUDENT WRITTEN
	// copy head card
	Card head_card = cards[0];

    // move all cards forward 1 space
	for (int i=0; i<cards_held; i++){
		cards[i] = cards[i+1];
	}

	// cards_held updated
	cards_held = cards_held - 1;

    // Returns the card that was removed
    return head_card;

}

Card List_dynamic_array::remove_from_tail()
{
	// if the list is empty, fail
	assert(cards_held > 0);

    // STUDENT WRITTEN
	// copy tail card
	Card tail_card = cards[cards_held-1];

	// cards_held updated
	cards_held = cards_held - 1;

    // Returns the card that was removed
    return tail_card;
}

Card List_dynamic_array::remove_from_index(int index)
{
	// if the list is empty, fail
	assert(cards_held > 0);
	
	// if loc is outside of bounds, fail
	assert(index >= 0 && index < cards_held);

    // STUDENT WRITTEN
	// copy index card
	Card index_card = cards[index];

    // move all cards forward 1 space
	for (int i=index; i<cards_held; i++){
		cards[i] = cards[i+1];
	}

	// cards_held updated
	cards_held = cards_held - 1;

    // Returns the card that was removed
    return index_card;
	
}

void List_dynamic_array::expand()
{
    // STUDENT WRITTEN
	// five steps to expand list
	// 1. create new list with twice the capacity
	Card* new_list = new Card[hand_capacity * 2];

	// 2. copy all cards to the new list
	for (int i=0; i<cards_held; i++){
		new_list[i] = cards[i];
	}
	
	// 3. delete the old list
	delete[] cards;
	
	// 4. set cards variable to point to the new list
	cards = new_list;

	// 5. update hand_capacity
	hand_capacity = hand_capacity * 2;
}
