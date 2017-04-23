# ReadMe for COMP 15 HW1 (Fall 2014)
## Linked List
### Written by Ben Tanen, 9/24/14

**Purpose**: The purpose of this program is to model a hand of cards.
This hand has the ability shuffle, add or remove a card, deal, and other
general abilities for hands of cards. The hand is composed of a list
(constructed using a linked list) of cards, where both the list and the cards
have their own class. To see further documentation on the implementation of
the hand, card, or list, see the included .cpp files (`hand.cpp`, `card.cpp`,
`List_linked_list.cpp` respectively)

* * *

**Included Files**:

`main.cpp`: The main file that runs checks of the hand class

`hand.cpp`: The implementation of the `hand` class (no changes made).

`hand.h`: The interface of the `hand` class (no changes made).

`card.cpp`: The implementation of the `card` class (no changes made).

`card.h`: The interface of the `card` class (no changes made).

`ReadMe.md`: The README, which gives a brief description of the program.

`Makefile`: The Makefile used to compile the program using clang++.

`List_linked_list.h`: The interface of the `List_linked_list` (no changes).

`List_linked_list.cpp`: The implementation of the `List_linked_list` class. This was the primary file that was changed for the assignment.

* * *

**Compile Instructions**: To compile the program, use the included Makefile.

* * *

**Data Structure(s)**: The `hand` class is composed of an list 
(`List_linked_list`) that holds cards (which are instances of the `card` 
class). The preliminary data structure in this case is the list, which is
created using a linked list. Each card is stored in a node (with a card and a
pointer) and cards can be added or removed. When the list must be expanded, a
new node is simply added in the appropriate location.

* * *

**Algorithm(s)**: There are no underlying algorithms used in this assignment. 
All functions and operations are performed in a standard fashion (generally 
for-looping through list). The only real algorithm use is using the remove 
function in order to delete nodes and the list as a whole.