# ReadMe for COMP 15 HW3
## ISIS Course Roster and Waitlists
### Written by Ben Tanen, 10/09/14

**Purpose**: The purpose of this program is to model a class roster and 
associated waitlists. The roster was implemented using a set and the waitlists 
(major and non-major) were built using queues. The class (roster + waitlists)
had the capability to enroll, print waitlists, drop students, etc. For the sake
of the assignment, most of the work involved is done in the Queue.h, Queue.cpp, 
IsisCourse.cpp, and IsisCourse.h files.

* * *

**Included Files**:

`main.cpp`: The main file that runs the class simulation (adding students, etc)

`Queue.cpp`: The implementation of the `queue` class (largely student written).

`Queue.h`: The interface of the `hand` class (no real changes).

`IsisCourse.cpp`: The implementation of the `IsisCourse` class (many of these 
functions were created by the student, Ben Tanen)

`IsisCourse.h`: The interface of the `IsisCourse` class (no real changes)

`Set.cpp`: The implementaiton of the `Set` class (no student changes)

`Set.h`: The interface of the `Set` class (no student changes)

`Student.h`: This is the interface which describes the student Struct

`ReadMe.md`: The README, which gives a brief description of the program.

`Makefile`: The Makefile used to compile the program using clang++.

* * *

**Compile Instructions**: To compile the program, use the included Makefile.

* * *

**Data Structure(s)**: There were a few primary data structures used in this
program. For data types, there were sets, queues, and IsisCourses, which all
had slightly different implementation. However, both the sets and queues used
a dynamic array to store the data. Essentially all of the data was stored in 
the queue(s) or set (except for the Student struct) which was made up of a 
dynamic array

* * *

**Algorithm(s)**: There primary algorithm used in this program was the constant
use of dequeuing and re-enqueuing. Each time the user wants to go through the 
waitlist some how, they are actually dequeuing each student into a temp_queue, 
which then gets emptied back into the main queue after the search is done. 
This algorithm made the behavior of the program fairly slow (relatively), but
was necessary based on the constraints of the ADT.
