#ifndef QUEUE_H_
#define QUEUE_H_

class Queue {
public:
	// constructor
	Queue();

	// deconstructor
	~Queue();

	// enqueue an int onto at the back of the queue
	void enqueue(int x);

	// dequeue an int from the front of the queue
	int dequeue();

	// check if queue is empty
	bool isEmpty();

	// expands queue
	void expand();

private:
	int *queue_array; // the dynamic array for the queue 
	int cap;   // how many integers can be stored
	int size;  // how many integers there are in the queue
	int front; // the front of the queue
	int back;  // the back of the queue
};

#endif /* QUEUE_H_ */
