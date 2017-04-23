/*
 * main_test.cpp
 *
 *  Created on: Sep 28, 2014
 *      Author: Ben Tanen
 *	 Used for Testing Purposes
 */
#include<iostream>
#include<string>

#include "Student.h"
#include "Set.h"
#include "Queue.h"
#include "IsisCourse.h"

using namespace std;

int main() {
	Student students[13] = {
			Student("Green,Alice",true), // enrolled
			Student("Orange,Friya",true),// enrolled
			Student("Pink,Julia",true),  // enrolled
			Student("Cyan,Barnaby",true),// enrolled
			Student("Red,Justin",true),  // enrolled
			Student("Blue,Misha",true), // major
			Student("Yellow,John",true),// major
			Student("Black,Henry",true),// major
			Student("Violet,Chester",false), // other
			Student("Fuchsia,Rebecca",false),// other
			Student("Beige,Barker",true),    // major
			Student("Teal,Jacob",true),      // major
			Student("Green,Fucker",true),    // major
	};

	IsisCourse test_course(5);

	for (int i=0;i<13;i++)
	 	 test_course.enroll_student(students[i]);

	test_course.print_list(IsisCourse::MAJOR_WAITLIST);
	test_course.drop_student(students[1]);
	test_course.print_list(IsisCourse::MAJOR_WAITLIST);

	// cout << students[3].name << " | " << test_course.waitlist_position(IsisCourse::OTHER_WAITLIST, students[3]) << endl;


}
