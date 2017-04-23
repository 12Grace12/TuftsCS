/*
 * Queue.cpp
 *
 *	    By: Ben Tanen
 *    Date: 9/28/14
 *   About: Queue Class Implementation for COMP-15 HW3. See ReadMe.md for more
 *  
 */

#include <iostream>
#include "Queue.h"

using namespace std;

// constructor
Queue::Queue() {
	// initalize all private variables
	capacity = QUEUE_INIT_CAPACITY; // QUEUE_INIT_CAPCITY = 2
	queue_array = new Student [capacity];

	size = 0;
	front = 0;
	back = 0;
}

// destructor
Queue::~Queue() {
	// delete allocated array
	delete [] queue_array;
}

// enqueue a student onto the back of the queue
void Queue::enqueue(Student c) {

	// checks if the array must be expanded
	if (size == capacity) {
		expand();
	}

	// stores new student at back
	queue_array[back] = c;

	// checks if back must be sent to front
	back = (back + 1) % capacity;

	// increase size
	size++;

	return;

}

// dequeue a student from the front of the queue
// and returns it
Student Queue::dequeue() {
	// get the student from the front
	Student s = queue_array[front];
	
	// increment up
	front = (front + 1) % capacity;
	size--;

	// return student
	return s;
}

// returns true if there are no elements in the
// queue, false if the queue has elements
bool Queue::is_empty() {
	return (size == 0);
}

// expand the circular queue
void Queue::expand() {
	// create new array (double size)
	Student *new_array = new Student [capacity * 2];

	// loop through and transfer elements to new_array
	for (int i=0;i<capacity;i++){
		new_array[i] = queue_array[(front + i) % capacity];
	}

	// delete old array, store new one
	delete [] queue_array;
	queue_array = new_array;

	// set back / front
	front = 0;
	back = size;
	capacity = capacity * 2;
	return;
}