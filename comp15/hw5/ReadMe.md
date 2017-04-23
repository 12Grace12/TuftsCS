# ReadMe for COMP 15 HW5
## Sort Assignment
### Written by Ben Tanen, 11/13/14

**Purpose**: The purpose of this project was understand and implement three
different types of sorting algorithms. For my particular instance of the
assignment, I implemented SelectionSort (required), QuickSort and RadixSort.
Once each of these were implemented, it was important to understand how each
algorithm's space & time complexity effected the overall sort. Notes on the
specific algorithms can be seen below and in the related .h/.cpp files.

* * *

**Included Files**:

`main1.cpp`: The main file that is used to test the SelectionSort class

`SelectionSort.cpp`: The implementation of the SelectionSort class (sort by BT)

`SelectionSort.h`: The interface of the SelectionSort class (no real changes)

`main2.cpp`: The main file that is used to test the sort2 (QuickSort) class

`sort2.cpp`: The implementation of the sort2 (QuickSort) class (sort by BT)

`sort2.h`: The interface of the sort2 (QuickSort) class (minor changes)

`main3.cpp`: The main file that is used to test the sort3 (RadixSort) class

`sort3.cpp`: The implementation of the sort3 (RadixSort) class (sort by BT).

`sort3.h`: The interface of the sort3 (RadixSort) class (minor changes).

`Queue.cpp`: The implementation of the Queue class used in RadixSort (from hw3)

`Queue.h`: The interface of the Queue class used in RadixSort (from hw3)

`ReadMe.md`: The README, which gives a brief description of the program.

`Makefile`: The Makefile used to compile the program using clang++.

* * *

**Compile Instructions**: To compile the program, use the included Makefile.

* * *

**Data Structure(s)**: The main data structure used in this assignment was a
struct which held a dynamic array (and the arrays length). This array held
integers and was used through the three sorts to sort the contents of the 
array.

The only other data structure that was primarily used in the sorting process
was the use of a Queue class in sort3 (RadixSort). This Queue was originally
built for Assignment #3 but was re-purposed (redefined for ints instead of 
Students) so they could be used. For more details, see related .cpp/.h files

* * *

**Algorithm(s)**: This assignment's purpose was to implement three different
sorting algorithms to sort an array of integers. The algorithms are as follows:

*SelectionSort*: The SelectionSort algorithm is a rather slow comparison sort. 
Starting from the beginning of the array, for each element, it compares all the 
values of every element to the right (unsorted). Once it combs through all of 
the elements, it swaps the comparing element with the smallest unsorted element.
This operation repeats for each element of the array, from left to right.

The implementation of SelectionSort is in-place. While it is rather space 
conservative, SelectionSort is a pretty terrible sort when it comes to speed. 
The best and worst time complexity are both O(n^2). This is because no matter 
the state of the array (already sorted, completely random, somewhat sorted, 
reversed, etc), the algorithm must loop through all the elements to the right of
the cursor / comparing element to find the smallest element. As can be seen in
the actual code, it's an easy sort to implement, but I would never recommend 
using a selectionSort as a legitimate choice in sorting algorithm.

*QuickSort (sort2)*: The QuickSort algorithm is based around using a pivot 
point. For each list (and sublist), numbers that are swapped and arranged so 
that the 'left' list is numbers less than the pivot and the 'right' list is 
numbers greater. This operation is repeated until there are sublists of size 1 
or 0 elements. From here, once this point has been reached, the array is sorted,
and the base case of the recursive function is met.

This particular implementation of QuickSort is in-place (space complexity of 
O(log n)) and runs quite quickly in comparison to SelectionSort. Overall, the 
best-case time complexity is O(n log n) while the worst-case complexity is 
O(n^2). The basis of this sort is based on sorting values either left or right
of a calculated pivot point. Because most of the sorting is based on this pivot,
the actual point chosen has a significant impact on the overall speed. In this 
instance, a "random" position was used as the pivot in order to minimize the 
chance that an inefficient pivot is chosen during a particular sort. Code for a 
front and middle pivot are also provided (but commented out). A instance that 
would likely result in a best-case time complexity would be one such that the 
pivot chosen is truly in the middle of the sublists being sorted (as would be 
true for an already sorted list). This makes it so that the problem is evenly 
divided each time, resulting in a faster sort. An example of an instance of 
worst-case would be when the pivot is either less than or greater than all of 
the values of the sublist. This would make it so each that each sublist is not 
divided evenly, making the operation very slow overall.

Overall, QuickSort is a consistently fast sort. So far the major limitation of 
the sort seems to be based on the pivot chosen, as this can hugely affect the 
sort, but using the "random" pivot in this implementation should help counter 
any adverse-pivot effects.

*RadixSort (sort3)*: The RadixSort algorithm is an algorithm that is based on 
the significant digits of the numbers being sorted. Instead of comparing the
every element, RadixSort assess the significant digits of each element and
places them into corresponding 'buckets'. Once each significant digit has been
accounted for (in this particular case, from smallest to largest), the array is
then in order. In this particular implementation, the buckets that are used are
built using a queue class to keep order in the buckets.

In this particular implementation, the time complexity of RadixSort is O(2d*n)
where `d` is the number of digits that much be assessed (maxDigit in sort3.cpp;
upper-bound of 10 if integers are all the size/length of MAX_INT). The best-case
time complexity would be when the user is sorting all integers that are single 
digit (0-9), resulting in O(2*(1)*n) behavior [which is roughly the same as 
QuickSort sorting 100 elements (100*log(100) = 100*2). The worst-case would be
when the user is sorting a list that contains at least one integer with 10 
significant digits. As can be seen, RadixSort has an interesting behavior
because it's efficiency is based more on the size of the integers being sorted, 
not the size of the list itself (obviously it included in the O(2d*n) complexity
but when comparing it to the O(n*log(n)) behavior of QuickSort, etc., it is much
less dependent on list size). Because of this behavior, RadixSort is a 
particularly useful sort when the user is trying to sort a lot of integers that 
are all smaller (1-5 significant digits).

* * * 

**Utilized Links**:

* [COMP-15 Notes, Day15](http://www.cs.tufts.edu/comp/15/lectures/Day_15/Day15.pdf)
* [COMP-15 Notes, Day16](http://www.cs.tufts.edu/comp/15/lectures/Day_16/Day16.pdf)
* [Sorting Algorithm Animations](http://www.sorting-algorithms.com/)
* [Further Radix Sort Reading](http://en.wikipedia.org/wiki/Radix_sort)

