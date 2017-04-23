#include "Queue.h"
#include <iostream>

// constructor
Queue::Queue() {
	int init_size = 2;
	queue_array = new int [init_size];

	cap = init_size;
	size = 0;
	front = 0;
	back = 0;
}

// deconstructor
Queue::~Queue() {
	delete [] queue_array;
}

// enqueue an int onto the back of the queue
void Queue::enqueue(int x) {

	if (size == cap) {
		expand();
	}

	queue_array[back] = x;
	back = (back + 1) % cap;
	size++;
	return;
}

// dequeue an int from the front of the queue
// and returns it
int Queue::dequeue() {
	int return_elem = queue_array[front];
	front = (front + 1) % cap;
	size--;
	return return_elem;
}

// checks if the queue is empty
bool Queue::isEmpty() {
	return (size == 0);
}

// expand the circular queue
void Queue::expand() {
	// create new array (double size)
	int *new_array = new int [cap * 2];

	// loop through and transfer elements to new_array
	for (int i=0;i<cap;i++){
		new_array[i] = queue_array[(front + i) % cap];
	}

	// delete old array, store new one
	delete [] queue_array;
	queue_array = new_array;

	// set back / front
	front = 0;
	back = size;
	cap = cap * 2;
	return;
}