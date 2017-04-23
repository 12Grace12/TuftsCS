/*
 * IsisCourse.cpp
 *
 */

#include <iostream>
#include "IsisCourse.h"

 using namespace std;

IsisCourse::IsisCourse() {
	class_capacity = 0; // no students allowed in yet
}

IsisCourse::IsisCourse(int init_capacity) {
	class_capacity = init_capacity; // capacity set to init value
}

IsisCourse::~IsisCourse() {
	// nothing to do
}

void IsisCourse::set_class_cap(int cap) {
	class_capacity = cap;
	if (roster.size() < class_capacity) {
		update_enrollments();
	}
}

// given a student, places them in the appropriate list (waitlist / roster)
IsisCourse::ENROLLMENT_STATUS IsisCourse::enroll_student(Student s) {

	// checks where they should go, places them there
	// returns where student was placed
	if (s.major) {
		if (roster.size()+1 > class_capacity) {
			major_waitlist.enqueue(s);
			return MAJOR_WAITLIST;
		} else {
			roster.add(s);
			return ENROLLED;
		}
	} else {
		other_waitlist.enqueue(s);
		return OTHER_WAITLIST;
	}
}

// given a student, attempts to drop them (says if it was successful)
bool IsisCourse::drop_student(Student s) {
	bool found_student = false; // if we find the student to drop
	Queue temp_list;
	// checks if on roster, and drops if necessary
	if (roster.is_enrolled(s)) {
		found_student = roster.drop(s);
	// checks if student would be on major or other waitlist
	} else if (s.major) {
		// loops through waitlist to find student
		while (!major_waitlist.is_empty()) {
			Student a = major_waitlist.dequeue();
			if (a.name == s.name)
				found_student = true;
			else
				temp_list.enqueue(a);
		}
		// re-enqueues waitlist from temp
		while(!temp_list.is_empty())
			major_waitlist.enqueue(temp_list.dequeue());
	} else {
		// loops through waitlist to find student
		while (!other_waitlist.is_empty()) {
			Student a = other_waitlist.dequeue();
			if (a.name == s.name)
				found_student = true;
			else
				temp_list.enqueue(a);
		}
		// re-enqueues waitlist from temp
		while(!temp_list.is_empty())
			other_waitlist.enqueue(temp_list.dequeue());
	}

	// if we dropped a student, there should be room on
	// the roster
	update_enrollments();
	return found_student;
}

// given a student / status, return their postion on their particular waitlist
int IsisCourse::waitlist_position(ENROLLMENT_STATUS status, Student s) {
	Queue temp_list;
	int i = 1;
	int found_student = -1;
	// checks if major or other
	if (status == MAJOR_WAITLIST) {
		// dequeues each element into temp (looking for target argument)
		while (!major_waitlist.is_empty()) {
			Student a = major_waitlist.dequeue();
			// if their names are equal, they're the same
			if (a.name == s.name)
				found_student = i;
			i++;
			temp_list.enqueue(a);
		}
		// re-enqueues the waitlist from the temp
		while (!temp_list.is_empty())
			major_waitlist.enqueue(temp_list.dequeue());
	} else if (status == OTHER_WAITLIST) {
		// same procedure as MAJOR_WAITLIST
		while (!other_waitlist.is_empty()) {
			Student a = other_waitlist.dequeue();
			if (a.name == s.name)
				found_student = i;
			i++;
			temp_list.enqueue(a);
		}
		while (!temp_list.is_empty())
			other_waitlist.enqueue(temp_list.dequeue());
	}
	// return the found_student's position
	return found_student;
}

// given a student, returns their current placement (which waitlist/on roster)
IsisCourse::ENROLLMENT_STATUS IsisCourse::status(Student s) {
	Queue temp_list;
	ENROLLMENT_STATUS curr_status = NONE;

	// if on roster, return ENROLLED
	if (roster.is_enrolled(s))
		return ENROLLED;

	// search through major_waitlist first
	while (!major_waitlist.is_empty()) {
		Student a = major_waitlist.dequeue();
		if (a.name == s.name) {
			curr_status = MAJOR_WAITLIST;
		}
		temp_list.enqueue(a);
	}
	// re-enqueue major_waitlist
	while (!temp_list.is_empty()) {
		major_waitlist.enqueue(temp_list.dequeue());
	}
	// return status (don't check other_waitlist)
	if (curr_status == MAJOR_WAITLIST)
		return curr_status;

	// same approach as before (look up)
	while (!other_waitlist.is_empty()) {
		Student a = other_waitlist.dequeue();
		if (a.name == s.name) {
			curr_status = OTHER_WAITLIST;
		}
		temp_list.enqueue(a);
	}
	while (!temp_list.is_empty()) {
		other_waitlist.enqueue(temp_list.dequeue());
	}
	return curr_status;
}

// given a waitlist status, print the list of particular students
void IsisCourse::print_list(ENROLLMENT_STATUS status) {
	// provided (up until "now handle print the queue")
	Queue *waitlist_queue;
	Queue temp_queue;
	if (status == ENROLLED) {
		roster.print_class();
		return;
	}
	if (status == MAJOR_WAITLIST) {
		waitlist_queue = &major_waitlist;
	}
	else {
		waitlist_queue = &other_waitlist;
	}

	// now handle printing the queue
	int count = 1;
	while (!waitlist_queue->is_empty()) {
		Student s = waitlist_queue->dequeue();

		// output their name
		std::cout << count << ". " << s.name << endl;

		// store them in a temp queue
		temp_queue.enqueue(s);
		count++;
	}
	// repopulate the normal queue
	while (!temp_queue.is_empty()) {
		Student s = temp_queue.dequeue();
		waitlist_queue->enqueue(s);
	}
}

// moves students from the waitlist to the class if theree is available space
void IsisCourse::update_enrollments() {
	// put students from the waitlists into the class
	// in priority (majors first, then others), up to
	// the class capacity.

	int curr_size = get_roster_size();

	for (int i=curr_size;i<class_capacity;i++){
		// check major_waitlist first
		if (!major_waitlist.is_empty()) {
			Student s = major_waitlist.dequeue();
			roster.add(s);
		// then other_waitlist
		} else if (!other_waitlist.is_empty()) {
			Student s = other_waitlist.dequeue();
			roster.add(s);
		// else, just stop
		} else {
			break;
		}
	}
}
