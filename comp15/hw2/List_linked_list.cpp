#include "List_linked_list.h"

#include <iostream>
#include <cassert>

using namespace std;

List_linked_list::List_linked_list() 
{
	head = NULL; // blank list initialized at NULL
}


// TO BE WRITTEN
List_linked_list::~List_linked_list()
{
	// delete list by looping through and deleting each node
	int total_cards = cards_in_hand();
	for (int i=0; i<total_cards; i++){
		remove_from_head();
	}
}

// copy constructor
List_linked_list::List_linked_list(const List_linked_list& source) {
	// explicit copy constructor necessary because of cards array
	if (source.head == NULL) return; // nothing to do

	head = new Card_Node;
	Card_Node *this_current = head;
	Card_Node *source_current = source.head;

	while (source_current != NULL) {
		// deep copy each Card_Node
		if (source_current->next != NULL) {
			Card_Node *new_node = new Card_Node();
			this_current->next = new_node;
			new_node->card = source_current->next->card;
		}
		else {
			this_current->next = NULL; // at tail
		}
		source_current = source_current->next;
		this_current = this_current->next;
	}
}

// operator= overload
List_linked_list List_linked_list::operator =(const List_linked_list&
		source) {
	// explicit operator= overload necessary because of cards array

	// check for self-assignment -- return without doing anything
	if (this == &source) {
		return *this;
	}
	// delete all current cards
	while (head != NULL) {
		Card_Node *next = head->next;
		delete head;
		head = next;
	}
	// copy over all cards from source list
	if (source.head == NULL) return *this; // nothing to do

	head = new Card_Node;
	Card_Node *this_current = head;
	Card_Node *source_current = source.head;

	while (source_current != NULL) {
		// deep copy each Card_Node
		this_current->card = source_current->card;
		if (source_current->next != NULL) {
			Card_Node *new_node = new Card_Node();
			this_current->next = new_node;
		}
		else {
			this_current->next = NULL; // at tail
		}
		source_current = source_current->next;
		this_current = this_current->next;
	}
	return *this;
}

void List_linked_list::print_list()
{
	Card_Node *current = head;
	while (current != NULL) {
		current->card.print_card();
		if (current->next != NULL) {
			cout << ",";
		}
		else {
			cout << "\n";
		}
		current = current->next;
	}
}

void List_linked_list::print_list_int()
{
	Card_Node *current = head;
	while (current != NULL) {
		current->card.print_card_int();
		if (current->next != NULL) {
			cout << ",";
		}
		else {
			cout << "\n";
		}
		current = current->next;
	}
}

// returns the number of cards in the hand
int List_linked_list::cards_in_hand()
{
	int count = 0;
	Card_Node *temp = head;
	while (temp != NULL){
		count++;
		temp = temp->next;
	}
	return count;
}

// empties the list; head should equal NULL
void List_linked_list::make_empty(){
	int total_cards = cards_in_hand();
	for (int i=0; i<total_cards; i++){
		remove_from_head();
	}

	head = NULL;
}

// inserts a card at the head
// Should allow insert into an empty list
void List_linked_list::insert_at_head(Card c)
{
	Card_Node *node = new Card_Node;
	node->card = c;
	node->next = head;
	head = node;

	return;
}

// inserts a card at the tail (final node)
// should allow insert into an empty list
void List_linked_list::insert_at_tail(Card c)
{

	if (cards_in_hand() == 0){
		insert_at_head(c);
		return;
	}
	
	Card_Node *node = new Card_Node;
	node->card = c;
	node->next = NULL;

	Card_Node *temp = head;
	while (temp->next != NULL){
		temp = temp->next;
	}
	temp->next = node;
	return;
}

void List_linked_list::insert_at_index(Card c, int index)
{
	if (index == 0){
		insert_at_head(c);
	} else if (index == cards_in_hand()) {
		insert_at_tail(c);
	} else if (index < cards_in_hand() && index > 0) {
		Card_Node *node = new Card_Node;
		node->card = c;

		Card_Node *temp = head;
		for (int i=0;i<index-1;i++){
			temp = temp->next;
		}
		node->next = temp->next;
		temp->next = node;
	} else {
		return;
	}
}

void List_linked_list::replace_at_index(Card c, int index)
{
	Card_Node *temp = head;
	for (int i=0;i<index;i++){
		temp = temp->next;
	}
	temp->card = c;

	return;
}

// returns the card at index.
// allowed to crash if index is not in the list
Card List_linked_list::card_at(int index)
{
	Card_Node *temp = head;
	for (int i=0;i<index;i++){
		temp = temp->next;
	}
	return temp->card;
}

// returns true if the card is in the list
// returns false if the card is not in the list
bool List_linked_list::has_card(Card c)
{
	Card_Node *temp = head;
	while (temp != NULL){
		if (temp->card.same_card(c)){
			return true;
		}
		temp = temp->next;
	}
	return false;
}

// removes the card from the list
// Returns true if the card was removed
// Returns false if the card was not in the list
bool List_linked_list::remove(Card c)
{
	// if the card doesn't exist, return false
	if (!has_card(c)){
		return false;
	}

	// set temp to head
	Card_Node *temp = head;

	// if the first card is the card you want, delete it
	if (temp->card.same_card(c)){
		head = temp->next;
		delete temp;
		return true;
	}

	// loop through all the cards until you find it
	while (!temp->next->card.same_card(c)){
		temp = temp->next;
	}

	Card_Node *delPtr = temp->next;
	temp->next = temp->next->next;
	delete delPtr;
	return true;
}

// Removes the card from the head, and assigns the head
// to head->next
// Returns the card that was removed
// Allowed to fail if list is empty
Card List_linked_list::remove_from_head()
{
	Card return_card = head->card;
	remove(return_card);
	return return_card;
}

// Removes the card from the tail
// Returns the card that was removed
// Allowed to fail if the list is empty
Card List_linked_list::remove_from_tail()
{
	Card_Node *temp = head;
	while (temp->next != NULL){
		temp = temp->next;
	}

	Card return_card = temp->card;
	remove(return_card);
	return return_card;
}

// Removes the card from index
// Returns the card that was removed
// Allowed to fail if index is beyond the end of the list
Card List_linked_list::remove_from_index(int index)
{
	Card_Node *temp = head;
	for (int i=0;i<index;i++){
		temp = temp->next;
	}

	Card return_card = temp->card;
	remove(return_card);
	return return_card;
}





