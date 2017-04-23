# ReadMe for COMP 15 HW1 (Fall 2014)
## Dynamic Arrays
### Written by Ben Tanen, 9/12/14

**Purpose**: The purpose of this program is to model a hand of cards. This hand has the ability shuffle, add or remove a card, deal, and other general abilities for hands of cards. The hand is composed of a list (constructed using a dynamic array) of cards, where both the list and the cards have their own class. To see further documentation on the implementation of the hand, card, or list, see the included .cpp files (`hand.cpp`, `card.cpp`, `List_dynamic_array.cpp` respectively)

**Included Files**:

- `main.cpp`: The included main file showcases some of the abilities of the hand of cards. Many different versions of the main.cpp file can be created to showcase all of the hand's capabilities.
- `hand.cpp`: This is the implementation of the `hand` class, describing how each of its functions work. This file was not edited or changed at all.
- `hand.h`: This is the interface of the `hand` class, giving an overview of the capabilities and functions of the class. This file was not edited or changed at all.
- `card.cpp`: This is the implementation of the `card` class, describing how each of its functions work. This file was not edited or changed at all.
- `card.h`: This is the interface of the `card` class, giving an overview of the capabilities and functions of the class. This file was not edited or changed at all.
- `ReadMe.md`: This is the README, which gives a brief description of the program and its structure. This is the file you are currently reading.
- `Makefile`: This is the Makefile used to compile the program using clang++. This file was not edited or changed at all (except for testing purposes).
- `List_dynamic_array.h`: This is the interface of the `List_dynamic_array` class, giving an overview of the capabilities and functions of the class. This file was not edited or changed at all.
- `List_dynamic_array.cpp`: This is the implementation of the `List_dynamic_array` class, describing how each of its functions work. This was the primary file that was changed for the assignment. 13 of the 17 functions were written by BT (changes can be seen under the `// STUDENT WRITTEN` line). Functions include constructor, destructor, the ability to add a card at a given index, remove a given card, etc.

**Compile Instructions**: To compile the program, use the included Makefile

**Data Structure(s)**: The `hand` class is composed of an list (`List_dynamic_array`) that holds cards (which are instances of the `card` class). The preliminary data structure in this case is the list, which is created using a dynamic array. Each card is stored in the array and cards can be added or removed. When the list must be expanded (the number of cards being stored exceeds the capacity), a new larger array is created and the old one is deleted.

**Algorithm(s)**: There are no underlying algorithms used in this assignment. All functions and operations are performed in a standard fashion (generally for-looping through array).

